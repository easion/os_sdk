#include<assert.h>
#include<unistd.h>

void __dj_assert(const char *msg, const char *file, int line)
{
 __libclog_printf("Assertion failed at line %u in file %s\n",
   line,file);
 __libclog_printf("Assertion: '%s'\n",msg);
 abort();
}
