#ifndef __DJ_jthread_h_
#define __DJ_jthread_h_

#ifdef __cplusplus
extern "C" {
#endif
typedef int tid_t;
#if 0
enum{
 SPINLOCK_LOCKED=		0,
 SPINLOCK_UNLOCKED=	1,
};

typedef struct 
{
	volatile unsigned char lock;
	//volatile unsigned  flags;
} spinlock_t;

typedef struct{
	int count;
	spinlock_t spin;
	long* wait_head,wait_tail;
}semaphore_t;

struct  lock 
{
	int cnt;
};


struct thread_queue
{
	void *head;
	void *tail;
};

static inline void init_thread_queue(struct thread_queue *threadq)
{
	threadq->head = NULL;
	threadq->tail = NULL;
}



int thread_sleep_on(struct thread_queue* pq, unsigned *timeout);
int thread_wakeup(struct thread_queue *pq);
int thread_mutex_init(semaphore_t **sem, char *name);
int thread_mutex_destroy(semaphore_t *sem);
int thread_mutex_lock(semaphore_t *sem,int msec);
int thread_mutex_unlock(semaphore_t *sem);

#endif
int get_thread_message(void* buf,	size_t len, time_t timeout);
int post_thread_message(tid_t thread, const void* buf, size_t len);


void idle_thread(void *arg) __attribute__ ((noreturn));
int thread_set_priority(tid_t id, int prio);
int thread_set_name(tid_t t,char *name);

tid_t thread_create(void (*fn)(void *), void *arg,unsigned long );
void thread_exit(tid_t t, void *para);
void thread_yield(tid_t t);
int thread_wait(tid_t t, void *l);

//msgport function
int msgport_create(const char *pname);
int msgport_connect(const char *pname);
int msgport_destroy(int port);
int msgport_wait(int port, int timeout);
int msgport_pend(int port, void *buf, int len, int timeout);
int msgport_send(int port, void *buf, int len);
int thread_msleep(time_t msec);
int thread_suspend(tid_t t);
int thread_resume(tid_t t);

#define MSG_ALWAYS_WAIT (unsigned long)-1
#define MSG_NO_WAIT (unsigned long)0

/*
 * thread states
 */
#define TS_READY     (0x01)
#define TS_WAITING   (0x02)
#define TS_DEAD      (0x04)
#define TS_IOPENDING (0xF0)


typedef	struct
{
    int 	ti_thread_id,ti_parent_id;   
    char	ti_thread_name[ 32 ];		/* Thread name				*/

    int  	ti_state;		/* Current task state.			*/
    unsigned int	ti_flags;
	int ti_msgport;
   

    int		ti_priority;
    int		ti_dynamic_pri;

    void*	ti_stack;
    unsigned	ti_stack_size;
    void*	ti_kernel_stack;		/* Top of kernel stack						*/
    unsigned int	ti_kernel_stack_size;		/* Size (in bytes) of kernel stack	*/		
     time_t	ti_sys_time;		/*	Micros in user mode		*/
    //bigtime_t	ti_user_time;		/*	Micros in kernal mode		*/
   // bigtime_t	ti_real_time;		/*	Total micros of execution	*/
     time_t	ti_quantum;		/*	Maximum allowed micros of execution before preemption	*/

} thread_info;


enum{
	SEM_WARN_DBL_LOCK,SEM_WARN_DBL_UNLOCK,SEM_RECURSIVE,SEM_GLOBAL
};

typedef struct 
{
	int counter;
} atomic_t;
typedef tid_t pthread_t;
typedef int sem_id;
/* Thread attribute object. */
typedef struct __pthread_attr_s
{
  size_t __stacksize;
  void *__stackaddr;
  size_t __guardsize;
  int __schedpriority;
  char *__name;
  int __detachstate;
  struct sched_param *__sched_param;
} pthread_attr_t;

/* Condition variable attribute object. */
typedef struct
{
  int __pshared;
} pthread_condattr_t;

/* The following is used internally by pthread_cond_t */
typedef struct __pt_thread_list_s
{
	pthread_t __thread_id;
	struct __pt_thread_list_s* __prev;
	struct __pt_thread_list_s* __next;
} __pt_thread_list_t;

/* Condition variable. */
typedef struct __pthread_cond_s
{
  pthread_t __owner;
  unsigned long __count;
  pthread_condattr_t* __attr;
  pthread_condattr_t __def_attr;
  __pt_thread_list_t* __head;
  sem_id __lock;
} pthread_cond_t;

/* Thread-specific data keys. */
typedef int pthread_key_t;

/* Mutex attribute object. */
typedef struct
{
  int __mutexkind;
  int __pshared;
} pthread_mutexattr_t;

/* Mutexes. */
typedef struct __pthread_mutex_s
{
  sem_id __mutex;
  pthread_t __owner;
  unsigned long __count;
  pthread_mutexattr_t *__attr;
  pthread_mutexattr_t __def_attr;
} pthread_mutex_t;

/* Dynamic package initialisation. */
typedef int pthread_once_t;

/* Read/Write locks. */
typedef int pthread_rwlock_t;

/* Read/Write lock attributes. */
typedef struct
{
  int __lockkind;
  int __pshared;
} pthread_rwlockattr_t;



#ifdef __cplusplus
}
#endif
#endif


