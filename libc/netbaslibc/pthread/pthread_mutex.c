#include <pthread.h>
#include <sys/types.h>
#include <stddef.h>

/* For printf. REMOVE WHEN ALL IMPLEMENTED */
#include <stdio.h>

/* Move to Whitix-specific API. */

#define UNIMPL printf(__func__)

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* mutexattr)
{
	if (!mutexattr)
		mutex->_lock=0;

	return 0;
}



int pthread_mutex_lock(pthread_mutex_t* mutex)
{
	//if (mutex->_lock == 0 && _CompareAndSwap(&mutex->_lock, 0, 1))
	//	return 0;

	if (mutex->_lock == 0)
		mutex->_lock=1;
	else{
		while (mutex->_lock == 1)
			usleep(500);

		mutex->_lock=1;
	}

	return 0;
}

int pthread_mutex_trylock(pthread_mutex_t* mutex)
{
	UNIMPL;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	mutex->_lock=0;
	/* Wake queue. */
	return 0;
}

int pthread_mutex_destroy(pthread_mutex_t* mutex)
{
	if (mutex->_lock == 1)
	{
		printf("mutex_destroy: mutex is locked!\n");
	}

	return 0;
}
