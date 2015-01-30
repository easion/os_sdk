#define JICAMA
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <servers.h>

int _uname(struct utsname * space )
{
	return  netbas_system_call(NR_UNAME,space,0,0,0,0);
}


char *brksize;

 int brk(char *addr)
{
  register int m;

	m=do_system_call(NR_BRK,(int)addr,0,0,0,0);
	 if (m < 0) return(-1);

  brksize = m;
  return(0);
}

char *sbrk(int incr)
{
  char *newsize, *oldsize;

  oldsize = brksize;
  newsize = brksize + incr;

  if (incr > 0 && newsize < oldsize || incr < 0 && newsize > oldsize)
	return( (char *) -1);

  if (brk(newsize) == 0)
	return(oldsize);
  else
	return( (char *) -1);
}


unsigned int	_alarm(unsigned int _seconds)
{
 	return  do_system_call(NR_ALARM,_seconds,0,0,0,0);
}

int reboot(int mode)
{
	return netbas_system_call(76,(int)mode,0,0,0,0);
}

int _getppid()
{
	return do_system_call(NR_GETPPID,0,0,0,0,0);
}

int gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	return do_system_call(NR_GETTIMEOFDAY,(int)tp,(int)tzp,0,0,0);
}

int stat(const char *path, struct stat *statbuf)
{
  int return_value;
   /* __asm__ volatile ("int $0x80" \
        : "=a" (return_value) \
        : "0" ((long)(106)),"b" ((long)(path)),"c" ((long)(statbuf)) ); \*/
	return_value = do_system_call(NR_STAT,(int)path,statbuf,0,0,0);
    return return_value;
}

int _setup()
{
  int return_value;
    __asm__ volatile ("int $0x80" \
        : "=a" (return_value) \
        : "0" ((long)(0)) ); \
    return return_value;
}

int _fork(void)
{
    int return_value;
    
	return do_system_call(NR_FORK,(int)0,0,0,0,0);
}

int ptrace(int req, char * buf, void* size, void *args)
{
	return do_system_call(NR_PTRACE,(int)req,(int)buf,(int)size,(int)args,0);
}

int _setuid (uid_t uid)
{
	return do_system_call(NR_SETUID,(int)uid,0,0,0,0);
}


int nice (int val)
{
     int return_value=_nice(val);
	 return  do_system_call(NR_NICE,return_value,0,0,0,0);	
}

time_t  pcruntimes(const time_t * const timep, struct tm * const tmp)
{
	/*返回机器启动时间， timep是从1970.1.1开始的*/
  return do_system_call(NR_TIME, (int)timep,0,(int)tmp,0,0);
}

void
localsub(const time_t * const _timep, const long offset, struct tm * const _tmp)
{
  (void)pcruntimes( (int)_timep,_tmp);
}

void mouse_stat(int *x, int *y, int *btt)
{
	netbas_system_call(81, (int)x, (int)y, (int)btt,0,0);
}

void video_stat(int *w, int *h, int *bpp, unsigned long *ptr)
{
	netbas_system_call(80, (int)w, (int)h, (int)bpp,(int)ptr,0);
}

void _exit(int val)
 {
   do_system_call(NR_EXIT,val,0,0,0,0);
 }



pid_t _waitpid(pid_t pid, int *stat_loc, int options)
{
   return do_system_call(NR_WAITPID,pid,(int)stat_loc,options,0,0);
}

pid_t _wait(int *val)
 {
   return _waitpid(-1,val,0);
 }

 int _pause()
{
  return do_system_call( NR_PAUSE, 0, 0, 0,0,0);
}


int _getpid()
{
   return (off_t)do_system_call(NR_GETPID,0, 0, 0,0,0);
};

clock_t _times(struct tms *buffer)
{   
   return do_system_call(NR_TIMES,buffer,(int)0,0,0,0);
}

int stime (time_t * tptr)
{
   return do_system_call(NR_STIME,tptr,(int)0,0,0,0);
}


uid_t		_getuid(void)
{
  return (uid_t)do_system_call(NR_GETUID,0, 0, 0,0,0);
}

uid_t		_geteuid(void)
{
  return (uid_t)do_system_call(NR_GETUID,0, 0, 0,0,0);
}


int _open(const char * filename, int mode, int flag)
{
	register int res;

	if(O_CREAT&mode)
	{
		//printf("create new file\n");
		res=_creat(filename, mode);
	}
	else
	{
		res=do_system_call(NR_OPEN, (unsigned )filename, (unsigned )mode, (unsigned )flag,0,0);
	}

	return res;
}


int _close(int fd)
 {
	register int res;

	res=do_system_call(NR_CLOSE, (unsigned )fd, (unsigned )0, (unsigned )0,0,0);
	return res;
	}

int		_chdir(const char *_path)
 {
	register int res;	
	res=do_system_call(NR_CHDIR, (unsigned )_path, (unsigned )0, (unsigned )0,0,0);
	return res;
 }

ssize_t	 _read(int fd,  void *buf, size_t s)
{
	register int res;	
	res=do_system_call(NR_READ, (unsigned )fd, (unsigned )buf, (unsigned )s,0,0);
	return res;
}

ssize_t	 _readdir(int fd,  void *buf, size_t s)
{
	register int res;	
	res=netbas_system_call(52, (unsigned )fd, (unsigned )buf, (unsigned )s,0,0);
	return res;
}

ssize_t	 _write(int fd, const void *buf, size_t s)
{
	register int res;	
	res=do_system_call(NR_WRITE, (unsigned )fd, (unsigned )buf, (unsigned )s,0,0);
	return res;
}

off_t _lseek(int fildes, off_t offset, int whence)
{
	register int res;	
	res=do_system_call(NR_LSEEK, (unsigned )fildes, (unsigned )offset, (unsigned )whence,0,0);
	return res;
};

int _dup(int fd)
{
	register int res;	
	res=do_system_call(NR_DUP, (unsigned )fd, (unsigned )0, (unsigned )0,0,0);
	return res;
}

int _pipe(int _fildes[2])
{
	register int res;	
	res=do_system_call(NR_PIPE, (unsigned )_fildes, (unsigned )0, (unsigned )0,0,0);
	return res;
}

int _dup2(int fd, int fd2)
{
	register int res;	
	res=do_system_call(NR_DUP2, (unsigned )fd, (unsigned )fd2, (unsigned )0,0,0);
	return res;
}

char* getpwd(unsigned char *stream, int sz)
{
	register int res;	
	res=do_system_call(183, (unsigned )stream, (unsigned )sz, (unsigned )0,0,0);
	return res;
}

char *curdirname(char *nBuf, int sz)
{
	int len,i=0;
	char dir_path[512];

	memset(dir_path,0,sizeof(dir_path));
	getpwd(dir_path, sizeof(dir_path));
	len = strlen(dir_path);

	while (dir_path[len] == '/'&& len>=0)
	{
		dir_path[len]='\0';
		len--;
	}

	while (dir_path[len] != '/'&& len>=0)
	{
		len--;
	}

	if (dir_path[len+1] && len>=0)
	{
		strncpy(nBuf, &dir_path[len+1], sz);
	}
	else{
		strncpy(nBuf, "/", sz);
	}

	return nBuf;
}

//#define NR_CREAT 8


//用 法: int creat (const char *filename, int permiss); 
//_fmode = O_BINARY; 
//int handle = creat("DUMMY.FIL", S_IREAD | S_IWRITE); 
//write(handle, buf, strlen(buf)); 
//close(handle); 

int _creat(const char *f, mode_t permiss)
 {
	register int res;	
	res=do_system_call(NR_CREAT, (unsigned )f, (unsigned )permiss, (unsigned )0,0,0);
	return res;
 }


int _rename(const char *n1, const char *n2)
{
	register int res;	
	res=do_system_call(NR_RENAME, (unsigned )n1, (unsigned )n2, (unsigned )0,0,0);
	return res;	
}

int _mkdir(const char *n1, mode_t mode)
 {
	int res;

	res=do_system_call(NR_MKDIR, (unsigned )n1, (unsigned )mode, (unsigned )0,0,0);
	return res;
 }

int ioctl( int fd, int cmd, ...)
{
	va_list arg;

	va_start(arg,cmd);
	arg=va_arg(arg,int);
	return do_system_call(NR_IOCTL, fd, cmd, (int)arg,0,0);
}


int sys_select( int fd, int cmd, ...)
{
	va_list arg;

	va_start(arg,cmd);
	arg=va_arg(arg,int);
	return netbas_system_call(50, fd, cmd, (int)arg,0,0);
}

int _rmdir(const char *filename)
{
	int res;

	res=do_system_call(NR_RMDIR, (unsigned )filename, (unsigned )0, (unsigned )0,0,0);
	return res;
}


int _unlink(const char *path)
{

	int res;

	res=do_system_call(NR_UNLINK, (unsigned )path, (unsigned )0, (unsigned )0,0,0);

	return res;
}

