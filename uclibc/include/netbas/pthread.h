#ifndef PTHREAD_H
#define PTHREAD_H

#include <stdlib.h>
#include <netbas/jthread.h>

/* CHECK */
typedef tid_t pthread_t;

struct pthread_mutex
{
	volatile long int _lock;
};


typedef struct pthread_mutex pthread_mutex_t;

typedef int pthread_mutexattr_t;
typedef int pthread_attr_t;
typedef unsigned int pthread_key_t;
typedef volatile unsigned int pthread_cond_t;

typedef unsigned int pthread_condattr_t;

#define PTHREAD_MUTEX_INITIALIZER	{0}
#define PTHREAD_MUTEX_RECURSIVE		{2}

#define PTHREAD_CREATE_JOINABLE		0x1
#define PTHREAD_CREATE_DETACHED		0x2

#define PTHREAD_COND_INITIALIZER	0x1

#define PTHREAD_COND_SIGNALLED		0x2

#define PTHREAD_STACK_MIN	8192


#define PTHREAD_SCOPE_SYSTEM	0x00000001

/* Functions */

int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
void pthread_cleanup_push(void (*routine)(void*),void* arg);
void pthread_cleanup_pop(int execute);
int pthread_cond_signal(pthread_cond_t* cond);
int pthread_cond_broadcast(pthread_cond_t* cond);
int pthread_cond_wait(pthread_cond_t* cond,pthread_mutex_t* mutex);

/* Attributes */
int pthread_attr_init(pthread_attr_t* attr);
int pthread_attr_destroy(pthread_attr_t* attr);
int pthread_attr_setscope(pthread_attr_t* attr, int scope);
int pthread_attr_getstack(const pthread_attr_t* attr,void** stackAddr,size_t* stackSize);
int pthread_create(pthread_t *thread,const pthread_attr_t* attr,void* (*startRoutine)(void*),void* args);
#endif
