#ifndef __DJ_jthread_h_
#define __DJ_jthread_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef int tid_t;

typedef struct{
	int count;
	int spinlock;
	void* unused;
	void* unused1[5];
}semaphore_t;

struct  lock 
{
	int cnt;
};
struct thread
{
	int foo;
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

void idle_thread(void *arg) __attribute__ ((noreturn));
tid_t thread_gettid();
int thread_set_priority(tid_t id, int prio);
int thread_set_name(char *name);

tid_t thread_create(void (*fn)(void *), void *arg,unsigned long );
void thread_exit(tid_t t);
void thread_yield(tid_t t);
int thread_wait(tid_t t, void *l);
int thread_mutex_init(semaphore_t **sem, char *name);
int thread_mutex_destroy(semaphore_t *sem);
int thread_mutex_lock(semaphore_t *sem);
int thread_mutex_unlock(semaphore_t *sem);

//msgport function
int msgport_create(const char *pname);
int msgport_connect(const char *pname);
int msgport_destroy(int port);
int msgport_wait(int port, int timeout);
int msgport_pend(int port, void *buf, int len, int timeout);
int msgport_send(int port, void *buf, int len, int timeout);
int thread_msleep(int msec);
#ifdef __cplusplus
}
#endif
#endif


