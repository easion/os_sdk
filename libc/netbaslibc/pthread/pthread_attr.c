#include <pthread.h>
#include <sys/types.h>
#include <stddef.h>

/* For printf. REMOVE WHEN ALL IMPLEMENTED */
#include <stdio.h>

#define UNIMPL printf(__func__)

int pthread_attr_init(pthread_attr_t* attr)
{
	UNIMPL;
}

int pthread_attr_destroy(pthread_attr_t* attr)
{
	UNIMPL;
}

int pthread_attr_setscope(pthread_attr_t* attr, int scope)
{
	UNIMPL;
}

int pthread_attr_getstack(const pthread_attr_t* attr,void** stackAddr,size_t* stackSize)
{
	UNIMPL;
}

int pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate)
{
	UNIMPL;
}
