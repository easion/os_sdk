#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<menuet/os.h>
#include<menuet/dosemu.h>
#include<menuet/sem.h>

extern char * __stdin_redirect;
extern char * __stdout_redirect;
extern char * __stderr_redirect;

DECLARE_STATIC_SEM(dosemu_lock);

#define _MAX_HANDLES		64

#define _IO_READ		1
#define _IO_WRITE		2
#define _IO_BUFDIRTY		4

#define IODEBUG(x...)		/* */

_io_struct __libc_io_handles[_MAX_HANDLES];
static char _io_filename[256];
static char _io_workarea[OS_WORK_AREA_SIZE];

/*
58 = SYSTEM TREE ACCESS

     ebx    pointer to fileinfo block

     path examples:

     ''/RAMDISK/FIRST/KERNEL.ASM'',0
     ''/RD/1/KERNEL.ASM'',0

     ''/HARDDISK/FIRST/KERNEL.ASM'',0
     ''/HD/1/KERNEL.ASM'',0
     ''/HARDDISK/FIRST/MENUET/PICS/TANZANIA.BMP'',0

     fileinfo:

     dd   0                    ; 0=READ    (delete/append)
     dd   0x0                  ; 512 block to read 0+
     dd   0x1                  ; blocks to read (/bytes to write/append)
     dd   0x20000              ; return data pointer
     dd   0x10000              ; work area for os - 16384 bytes
     db   ''/RAMDISK/FIRST/KERNEL.ASM'',0  ; ASCIIZ dir & filename

     ret: eax = 0 - success, other - error code
          ebx = size of file

     or

     fileinfo:

     dd   1                    ; 1=WRITE
     dd   0x0                  ; not used
     dd   10000                ; bytes to write
     dd   0x20000              ; source data pointer
     dd   0x10000              ; work area for os - 16384 bytes
     db   ''/RAMDISK/FIRST/KERNEL.ASM'',0  ; ASCIIZ dir & filename

     ret: eax = 0 - success, other - error code

     or

     ; LBA

     fileinfo:

     dd   8                    ; 8=LBA read (/9=LBA write)
     dd   0x0                  ; 512 block to read (write)
     dd   0x1                  ; set to 1
     dd   0x20000              ; return data pointer
     dd   0x10000              ; work area for os (16384 bytes)
     dd   ''/HARDDISK/SECOND'',0 ; physical device ; ASCIIZ

          ( or /rd/1/ )

          LBA read must be enabled with setup

     NOTE: The asciiz in this context refers to the physical device and
           not to logical one.
           For hd: first=pri.master, second=pri.slave
                   third=sec.master, fourth=sec.slave

     or

     fileinfo:

     dd   16                   ; 16=START APPLICATION
     dd   0x0                  ; nop
     dd   param                ; 0 or parameter area ( ASCIIZ )
                               ; receiving application must
                               ; reserve a 256 byte area
     dd   0x0                  ; nop
     dd   0x10000              ; work area for os - 16384 bytes
     db   ''/HD/1/MENUET/APPS/FIRE'',0  ; ASCIIZ dir & filename

     ret: eax = pid or 0xfffffff0+ for error
*/
static inline int sys_systree(struct systree_info * i,int * EBX)
{
 int d0,d1;
 __asm__ __volatile__("int $0x60"
     :"=a"(d0),"=b"(d1)
     :"0"(58),"1"((unsigned long)i)
     :"memory");
 if(EBX) *EBX=d1;
 return d0;
}

int dosemu_file_exists(char * filename,char * buf)
{
 struct systree_info finf;
 static char data[512];
 int EBX;
 finf.work_area_for_os=(__u32)&_io_workarea;
 finf.return_data_pointer=(__u32)&data;
 if(buf) finf.return_data_pointer=(__u32)buf;
 finf.blocks_to_read=1;
 finf.start_block_to_read=0;
 finf.command=0;
 strcpy(finf.name_asciiz,filename);
 if(sys_systree(&finf,&EBX)!=0)
 {
  return -1;
 }
 return EBX;
}

int dosemu_createtrunc(char * filename)
{
 struct systree_info finf;
 static char one=0;
 finf.work_area_for_os=(__u32)&_io_workarea;
 finf.return_data_pointer=(__u32)&one;
 finf.blocks_to_read=1;
 finf.start_block_to_read=0;
 finf.command=1;
 strcpy(finf.name_asciiz,filename);
 if(sys_systree(&finf,NULL)!=0)
 {
  return -1;
 }
 return 0;
}

_io_struct * dosemu_getiostruct(int handle)
{
 if(handle<0 || handle>=_MAX_HANDLES) return NULL;
 if(__libc_io_handles[handle].oflags==-1) return NULL;
 return __libc_io_handles+handle;
}

int dosemu_fillbuf(_io_struct * s)
{
 struct systree_info finf;
 finf.work_area_for_os=(__u32)&_io_workarea;
 finf.return_data_pointer=(__u32)&s->buf;
 finf.blocks_to_read=1;
 finf.start_block_to_read=s->bufsector;
 finf.command=STC_READ;
 strcpy(finf.name_asciiz,s->filename);
 if(sys_systree(&finf,NULL)!=0)
 {
  IODEBUG("dosemu_fillbuf: systree failed\n");
  return -1;
 }
 return 0;
}

int dosemu_loadall(_io_struct * s)
{
 struct systree_info finf;
 finf.work_area_for_os=(__u32)&_io_workarea;
 if(s->wbufsize<s->size)
 {
  s->wbufsize=(s->size+511)&(~511);
  s->wbuf=realloc(s->wbuf,s->wbufsize);
 }
 finf.return_data_pointer=(__u32)s->wbuf;
 finf.blocks_to_read=(s->size>>9)+1;
 finf.start_block_to_read=0;
 finf.command=STC_READ;
 strcpy(finf.name_asciiz,s->filename);
 if(sys_systree(&finf,NULL)!=0)
 {
  IODEBUG("dosemu_loadall: systree failed\n");
  return -1;
 }
 return 0;
}

void dosemu_inithandles(void)
{
 int i;
 for(i=0;i<_MAX_HANDLES;i++)
  __libc_io_handles[i].oflags=-1;
 __libc_io_handles[0].oflags=1;
 __libc_io_handles[1].oflags=1;
 __libc_io_handles[2].oflags=1;
 __libc_io_handles[3].oflags=1;
}

int dosemu_allochandle(void)
{
 int i;
 sem_lock(&dosemu_lock);
 for(i=0;i<_MAX_HANDLES;i++)
 {
  if(__libc_io_handles[i].oflags==-1)
  {
   __libc_io_handles[i].oflags=-2;
   sem_unlock(&dosemu_lock);
   return i;
  }
 }
 sem_unlock(&dosemu_lock);
 return -1;
}
 
int dosemu_freehandle(int i)
{
 if(i<0) return -1;
 sem_lock(&dosemu_lock);
 __libc_io_handles[i].oflags=-1;
 sem_unlock(&dosemu_lock);
 return 0;
}

int dosemu_flush(_io_struct * sh)
{
 struct systree_info finf;
 if(sh->file_type!=DOSEMU_FILE_NORMAL) return 0;
 if(!(sh->flags&_IO_BUFDIRTY)) return 0;
 if(!sh->size) return 0;
 finf.work_area_for_os=(__u32)&_io_workarea;
 finf.return_data_pointer=(__u32)sh->wbuf;
 finf.blocks_to_read=sh->size;
 finf.start_block_to_read=0;
 finf.command=STC_WRITE;
 strcpy(finf.name_asciiz,sh->filename);
 if(sys_systree(&finf,NULL)!=0)
 {
  return -1;
 }
 sh->flags&=~_IO_BUFDIRTY;
 return 0;
}
 
int dosemu_loadcurrsector(_io_struct * sh)
{
 sh->bufsector=sh->pointer>>9;
 return dosemu_fillbuf(sh);
}

int dosemu_fileread(_io_struct * sh,char * buffer,int count)
{ 
 int icount,curr_sector,curr_sector_ofs,n;
 int nbufbytes,totalremaining;
 if(sh->pointer+count>sh->size)
  count=sh->size-sh->pointer;
 if(sh->flags&_IO_WRITE)
 {
  memcpy(buffer,sh->wbuf+sh->pointer,count);
  sh->pointer+=count;
  return count;
 }
 icount=count;
 while(count>0)
 {
  if(sh->pointer>=sh->size) return icount=count;
  curr_sector=sh->pointer>>9;
  curr_sector_ofs=sh->pointer&511;
  n=count;
  if(sh->bufsector==-1 || curr_sector!=sh->bufsector)
  {
   if(dosemu_loadcurrsector(sh)==-1)
   {
    return -1;
   }
  }
  nbufbytes=512-curr_sector_ofs;
  totalremaining=sh->size-sh->pointer;
  if(nbufbytes>totalremaining) nbufbytes=totalremaining;
  if(n>nbufbytes) n=nbufbytes;
  memcpy(buffer,&sh->buf[curr_sector_ofs],n);
  buffer+=n;
  count-=n;
  sh->pointer+=n;
 }
 return icount;
}

int dosemu_filewrite(_io_struct * sh,char * buffer,int count)
{
 int newpointer;
 char * xbuf;
 newpointer=sh->pointer+count;
 if(!count)
 {
  return 0;
 }
 if(newpointer>sh->wbufsize)
 {
  xbuf=realloc(sh->wbuf,sh->wbufsize+512);
  if(!xbuf)
  {
   __libclog_printf("dosemu_filewrite: unable to reallocate I/O buffer to %u bytes\n",sh->wbufsize+512);
   return -1;
  }
  sh->wbufsize+=512;  
  sh->wbuf=xbuf;
 }
 if(sh->size<newpointer) sh->size=newpointer;
 memcpy(sh->wbuf+sh->pointer,buffer,count);
 sh->pointer=newpointer;
 sh->flags|=_IO_BUFDIRTY;
 return count;
}

int dosemu_iosize(int handle)
{
 _io_struct * sh=dosemu_getiostruct(handle);
 if(!sh) return -1;
 return sh->size;
}

int dosemu_filesize(char * filename)
{
 return dosemu_file_exists(filename,NULL);
}

static char fn_buf[256];

int dosemu_open(char * filename,int oflags)
{
 struct systree_info finf;
 int baseflags,h,fsize;
 finf.work_area_for_os=(__u32)&_io_workarea;
 _fixpath(filename,_io_filename);
 strupr(_io_filename);
 baseflags=oflags&(O_RDONLY|O_WRONLY|O_RDWR);
 h=dosemu_allochandle();
 if(h<0)
 {
  return -1;
 }
 __libc_io_handles[h].file_type=DOSEMU_FILE_NORMAL;
 fsize=dosemu_file_exists(_io_filename,(char *)&__libc_io_handles[h].buf);
 if(oflags & O_CREAT)
 {
  int creatflags=oflags & (O_EXCL|O_TRUNC);
  if(creatflags & O_EXCL)
  {
   if(fsize>=0)
   {
    dosemu_freehandle(h);
    return -1;
   }
  }
  if(fsize<0 || creatflags&O_TRUNC)
  {
   if(dosemu_createtrunc(_io_filename)<0)
   {
    dosemu_freehandle(h);
    return -1;
   }
   fsize=0;
  }
 }
 if(baseflags==O_RDONLY)
 {
  if(fsize<0) return fsize;
  __libc_io_handles[h].oflags=oflags;
  __libc_io_handles[h].size=fsize;
  __libc_io_handles[h].pointer=0;
  __libc_io_handles[h].bufsector=0;
  __libc_io_handles[h].flags=_IO_READ;
  __libc_io_handles[h].wbufsize=0;
  __libc_io_handles[h].wbuf=NULL;
  strcpy(__libc_io_handles[h].filename,_io_filename);
  return h;
 }
 if(baseflags==O_WRONLY)
 {
  __libc_io_handles[h].oflags=oflags;
  __libc_io_handles[h].size=0;
  __libc_io_handles[h].pointer=0;
  __libc_io_handles[h].bufsector=1;
  __libc_io_handles[h].flags=_IO_WRITE|_IO_BUFDIRTY;
  __libc_io_handles[h].wbufsize=0;
  __libc_io_handles[h].wbuf=NULL;
  strcpy(__libc_io_handles[h].filename,_io_filename);
  if(dosemu_flush(&__libc_io_handles[h])<0)
  {
   dosemu_freehandle(h);
   return -1;
  }
  return h;
 }
 if(baseflags==O_RDWR)
 {
  __libc_io_handles[h].oflags=oflags;
  __libc_io_handles[h].size=fsize;
  __libc_io_handles[h].pointer=0;
  __libc_io_handles[h].bufsector=0;
  __libc_io_handles[h].wbufsize=0;
  __libc_io_handles[h].wbuf=NULL;
  __libc_io_handles[h].flags=_IO_WRITE|_IO_READ;
  strcpy(__libc_io_handles[h].filename,_io_filename);
  if(dosemu_loadall(&__libc_io_handles[h])<0)
  {
   dosemu_freehandle(h);
   return -1;
  }
  return h;
 }
 return -1;
}

int dosemu_tell(int handle)
{
 _io_struct * sh=dosemu_getiostruct(handle);
 if(!sh) return -1;
 if(sh->file_type!=DOSEMU_FILE_NORMAL) return -1;
 return sh->pointer;
}
  
int dosemu_lseek(int handle,long offset,int origin)
{
 int newpointer=0;
 _io_struct *sh=dosemu_getiostruct(handle);
 if(!sh)return -1;
 if(sh->file_type!=DOSEMU_FILE_NORMAL) return -1;
 if(handle==0 || handle==1 || handle==2 || handle==3) return -1;
 switch(origin)
 {
  case SEEK_SET: newpointer=offset;break;
  case SEEK_CUR: newpointer=sh->pointer+offset;break;
  case SEEK_END: newpointer=sh->size+offset;break;
 }
 if(newpointer<0)return -1;
 sh->pointer=newpointer;
 return newpointer;
}

int dosemu_read( int handle, void *buffer, unsigned int count )
{
 _io_struct *sh=dosemu_getiostruct(handle);
 switch(sh->file_type)
 {
  case DOSEMU_FILE_NORMAL:
   if(handle==1 || handle==2) return count;
   if(handle==0)
   {
    if(!__stdin_redirect)
    {
     return -1;
    }
    return dosemu_read(stdin->_file,buffer,count);
   }
   if(!sh)return -1;
   if(!(sh->flags&_IO_READ)) return -1;
   return dosemu_fileread(sh,buffer,count);  
  case DOSEMU_FILE_SOCKET:
   return bsd_sock_read(sh->sock,count,(char *)buffer);
  case DOSEMU_FILE_PIPE:
   return _libc_pipe_read(sh->pdesc,(char *)buffer,count);
 }
 return -1;
}

int dosemu_write( int handle, void *buffer, unsigned int count )
{
 _io_struct *sh=dosemu_getiostruct(handle);
 int k;
 switch(sh->file_type)
 {
  case DOSEMU_FILE_NORMAL:
   if(handle==1 || handle==0)
   {
    __libc_write_stdout(buffer,count);
    return count;
   } else if(handle==2) {
    __libc_write_stderr(buffer,count);
    return count;
   }
   if(!sh)return -1;
   if(!(sh->flags&_IO_WRITE)) return -1;
   return dosemu_filewrite(sh,buffer,count);  
  case DOSEMU_FILE_SOCKET:
   return bsd_sock_write(sh->sock,count,(char *)buffer);
  case DOSEMU_FILE_PIPE:
   return _libc_pipe_write(sh->pdesc,(char *)buffer,count);
 }
 return -1;
}

int dosemu_close( int handle )
{
 int i;
 _io_struct *sh=dosemu_getiostruct(handle);
 if(!sh)return -1;
 switch(sh->file_type)
 {
  case DOSEMU_FILE_NORMAL:
   dosemu_flush(sh);
   break;
  case DOSEMU_FILE_SOCKET:
   if((i=bsd_sock_close(sh->sock))!=0) return i;
   break;
  case DOSEMU_FILE_PIPE:
   _libc_pipe_close(sh->pdesc);
   break;
 }
 dosemu_freehandle(handle);
 return 0; 
}

void _dosemu_flush(int handle)
{
 _io_struct *sh=dosemu_getiostruct(handle);
 if(!sh) return;
 if(sh->file_type!=DOSEMU_FILE_NORMAL) return;
 dosemu_flush(sh);
}

void dosemu_atexit(void)
{
 int i;
 for(i=0;i<_MAX_HANDLES;i++)
  if(__libc_io_handles[i].oflags!=-1) dosemu_close(i);
}
