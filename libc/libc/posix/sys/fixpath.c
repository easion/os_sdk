#include <stdio.h>		/* For FILENAME_MAX */
#include <errno.h>		/* For errno */
#include <string.h>		/* For strlen() */
#include <sys/stat.h>
#include <libc/dosio.h>

static inline int is_slash(char c)
{
 return c=='/' || c=='\\';
}

void fix_slashes(char * in,char * out)
{ 
 int slash_count;
 if(is_slash(in[0]) && in[1]=='\0')
 {
  strcpy(out,"/");
  return;
 }
 for(slash_count=1;in && out && *in;in++)
 {
  if(is_slash(*in))
  {
   slash_count++;
   continue;
  } else {
   if(slash_count)
   {
    slash_count=0;
    *out++='/';
   }
   *out++=*in;
  }
 }
 *out='\0';
}

char * __libc_combine_path(char * c)
{
// if(c[0]=='/') return c;
 //__cur.lvl=__cwd.lvl;
 //memcpy(&__cur.__dent,&__cwd.__dent,__cur.lvl*sizeof(__dentry_t));
 //strcpy(__copy_of_path,(const char *)c); 
 //___chdir(&__cur,__copy_of_path);
 return NULL;//getpwd(&__cur); 
}
void _fixpath(const char *in, char *out)
{
 char * combined=(char*)in;
 combined=__libc_combine_path((char *)in);
 fix_slashes(combined,out);
}
