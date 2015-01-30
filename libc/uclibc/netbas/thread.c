#define JICAMA



#include <stdio.h>
#include <string.h>
#include <netbas/netbas.h>
#include <errno.h>
#include <netbas/jthread.h>


static int exit_handler();


/*
 * thread_create()
 */
tid_t thread_create(void (*fn)(void *), void *arg, unsigned long stack_sz)
{
	struct thread *new_thread;
	void *stack;
	
	stack = (void*)malloc(stack_sz +4096);
		
     //return thread_build(new_thread, fn, arg, (unsigned )stack);

	return netbas_system_call(108, (unsigned )arg, 
		(unsigned )stack, (unsigned )fn,(unsigned )stack_sz,(unsigned)&exit_handler);
}



void thread_exit(tid_t t, void *para)
{
	 netbas_system_call(109, (unsigned )t, (unsigned )para, (unsigned )0,0,0);	
}



void snooze(time_t tim)
{
	usleep(tim);
}




int thread_set_name(tid_t tid,char *name)
{
	return netbas_system_call(107, (unsigned )name, (unsigned )tid, (unsigned )0,0,0);	
}




int thread_set_priority(tid_t id, int prio)
{
	return netbas_system_call(114, (unsigned )id, (unsigned )prio, (unsigned )0,0,0);	
}


static int exit_handler()
{
	int tid = getpid();

	//printf("thread id %d exit ...\n", tid);
	thread_exit(tid,NULL);
	return 0;
}



int thread_resume(tid_t t)
{
	return netbas_system_call(112, (unsigned )t, (unsigned )0, (unsigned )0,0,0);		
}



int thread_suspend(tid_t t)
{
	return netbas_system_call(113, (unsigned )t, (unsigned )MSG_ALWAYS_WAIT, (unsigned )0,0,0);		
}

int thread_msleep( time_t timeout)
{
	tid_t t=getpid();
	return netbas_system_call(113, (unsigned )t, (unsigned )timeout, (unsigned )0,0,0);		
}

int thread_create_semaphore(const char *name, int flags, int init_val)
{
	return netbas_system_call(96, (unsigned )name, (unsigned )flags, (unsigned )init_val,0,0);		
}

int thread_delete_semaphore(int semid)
{
	return netbas_system_call(97, (unsigned )semid, (unsigned )0, (unsigned )0,0,0);		
}

int thread_lock_semaphore_x(int semid,time_t timeout)
{
	return netbas_system_call(98, (unsigned )semid, (unsigned )timeout, (unsigned )0,0,0);		
}

int thread_unlock_semaphore_x(int semid)
{
	return netbas_system_call(99, (unsigned )semid, (unsigned )0, (unsigned )0,0,0);		
}



int thread_get_info(tid_t t,thread_info*info)
{
	//fixme
	return netbas_system_call(106, (unsigned )t, (unsigned )info, (unsigned )0,0,0);		
}

/*
 * thread_yield()
 *	Release the current timeslice to another thread that may be ready to run.
 */
void thread_yield(tid_t t)
{
	return netbas_system_call(110, (unsigned )t, (unsigned )0, (unsigned )0,0,0);		
}


int thread_wait(tid_t t, void *ret)
{
	return netbas_system_call(111, (unsigned )t, (unsigned )ret, (unsigned )0,0,0);		
}




