#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int fat_convert_name_to_fat(char *dst, char *src)
{
 unsigned len;
 char *dot;
 memset(dst, ' ', 11);
 dot = strchr(src, '.');
 if(dot != NULL)
 {
  len = dot - src;
  if(len > 8) return -1;
  memcpy(dst, src, len);
  len = strlen(dot) - 1;
  if(len > 3)
   return -1;
  memcpy(dst + 8, dot + 1, len);
 } else {
  len = strlen(src);
  if(len > 8) return -1;
  memcpy(dst, src, len);
 }
 dst[11]=0;
 strupr(dst);
 return 0;
}

void fat_convert_name_from_fat(char *dst, char *src)
{
 unsigned char i;
 char *d = dst;
 for(i = 0; i < 8; i++)
 {
  if(src[i] == ' ') break;
  *d = src[i];
  d++;
 }
 if(src[8] != ' ')
 {
  *d = '.';
  d++;
  for(i = 8; i < 11; i++)
  {
   if(src[i] == ' ') break;
   *d = src[i];
   d++;
  }
 }
 *d = '\0';
 strlwr(dst);
}

typedef struct {
 char name[14];
} __dentry_t;

#define MAX_DENT_PER_PATH	32

typedef struct {
 int lvl;
 __dentry_t __dent[MAX_DENT_PER_PATH];
} dirdesc_t;

void add_to_dir(dirdesc_t * dd,char * name)
{
 __dentry_t * d;
 int i;
 i=dd->lvl++;
 d=&dd->__dent[i];
 fat_convert_name_to_fat(d->name,name); /* Fix the name to FAT format */
}

int get_from_dir(dirdesc_t * dd,char * name)
{
 __dentry_t * d;
 if(!dd->lvl) return 0;
 dd->lvl--;
 d=&dd->__dent[dd->lvl];
 if(name)
  fat_convert_name_from_fat(name,d->name); /* Get name in normal format */
 return 0;
}
 
static dirdesc_t __cwd;
static dirdesc_t __cur;
static char __curdir_buf[1024],__copy_of_path[1024];

void init_dir_stack(void)
{
 __cwd.lvl=0;
 __cur.lvl=0;
 add_to_dir(&__cwd,"RD");
 add_to_dir(&__cwd,"1");
}

static void empty_dir_stack(dirdesc_t * dd)
{
 dd->lvl=0;
}

static char * ___get_curdir(dirdesc_t * dir)
{
 char * b=__curdir_buf;
 char q[14];
 int i,j;
 if(!dir->lvl) return "/";
 for(i=0;i<dir->lvl;i++)
 {
  fat_convert_name_from_fat(q,dir->__dent[i].name);
  j=sprintf(b,"/%s",q);
  b+=j;
 }
 return __curdir_buf;
}

char * __get_curdir(void ) { return ___get_curdir(&__cwd); }

static void ___chdir(dirdesc_t * dir,char * path)
{
 char * slash;
 int done;
 if(path[0]=='/')
 {
  empty_dir_stack(dir);
  path++;
 }
 done=0;
 do {
  slash=strchr(path,'/');
  if(!slash)
  {
   slash=path+strlen(path);
   done=1;
  }
  *slash='\x0';
  if(!strcmp(path,".."))
  {
   get_from_dir(dir,NULL);
  } else if(!strcmp(path,"."))
  {
  } else add_to_dir(dir,path);
  *slash='/';
  path=slash+1;
 } while(!done);
}

void __chdir(char * path)
{
 strcpy(__copy_of_path,(const char *)path); 
 ___chdir(&__cwd,__copy_of_path);
}

char * __libc_combine_path(char * c)
{
 if(c[0]=='/') return c;
 __cur.lvl=__cwd.lvl;
 memcpy(&__cur.__dent,&__cwd.__dent,__cur.lvl*sizeof(__dentry_t));
 strcpy(__copy_of_path,(const char *)c); 
 ___chdir(&__cur,__copy_of_path);
 return ___get_curdir(&__cur); 
}

#ifdef __TEST_IN_DOS__

int main(void)
{
 init_dir_stack();
 printf("|%s|\n",__get_curdir());
 __chdir("jp/1/2/3");
 printf("|%s|\n",__get_curdir());
 __chdir("/jp/1/2/3");
 printf("|%s|\n",__get_curdir());
 __chdir("../4");
 printf("|%s|\n",__get_curdir());
 __chdir("./../..");
 printf("|%s|\n",__get_curdir());
 printf("Combined=|%s|\n",combine_path("./abc/def/../../../rd/2"));
 return 0;
}
#endif
