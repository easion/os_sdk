#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdio.h>

int vdprintf_help(char c)
{ 
 int d0,d1,d2;
 if(c=='\n')
 {
  c='\r';
  //__asm__ __volatile__("int $0x40":"=a"(d0),"=b"(d1),"=c"(d2):"0"(63),"1"(1),"2"(c));
  c='\n';
  //__asm__ __volatile__("int $0x40":"=a"(d0),"=b"(d1),"=c"(d2):"0"(63),"1"(1),"2"(c));
  return 0;
 }
 //__asm__ __volatile__("int $0x40":"=a"(d0),"=b"(d1),"=c"(d2):"0"(63),"1"(1),"2"(c));
 return 0 ;
}

static inline char xputs(char * s)
{
 for(;*s;s++) vdprintf_help(*s);
}

int __libclog_vprintf(const char *fmt, va_list args)
{
 int ret_val;
 char log_buf[1024];
 ret_val = vsprintf(log_buf,fmt,args);
 xputs(log_buf);
 return ret_val;
}

int __libclog_printf(const char * fmt,...)
{
 int v;
 va_list ap;
 va_start(ap,fmt);
 v=__libclog_vprintf(fmt,ap);
 return v;
}
