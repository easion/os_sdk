#include<assert.h>
#include<unistd.h>

void __dj_unimp(const char *fn)
{
 __libclog_printf(fn);
 _exit(1); 
}
