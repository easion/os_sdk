#define JICAMA

#include	<stdio.h>
#include <netbas/netbas.h>
#include <netbas/jthread.h>

enum{
	MSGPORT_CREATE_NO=1,
	MSGPORT_CONNECT_NO=2,
	MSGPORT_DESTROY_NO=3,
	MSGPORT_WAT_NO=4,
	MSGPORT_PEND_NO=5,
	MSGPORT_SEND_NO=6,
	MSGPORT_MDELAY=7,
	MSGPORT_SLEEP=8,
	MSGPORT_WAKEUP=9,
	MSGPORT_NOTIFY_SEND_NO=10,
	MSGPORT_SET_PUBLIC,
	MSGPORT_GET_PUBLIC,
};
#define MSGPORT_NR (93)

inline  int netbas_system_call(int function_number,int p1,int p2,
                  int p3,int p4,int p5)
{
     int return_value;

  
    asm volatile ("int $0x60" \
        : "=a" (return_value) \
        : "0" ((long)(function_number)),"b" ((long)(p1)),"c" ((long)(p2)), \
          "d" ((long)(p3)),"S" ((long)(p4)),"D" ((long)(p5)) ); \
		  
    return return_value;
};

/*
**
*/
int msgport_create(const char *pname)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )pname, (unsigned )0, (unsigned )0,0,MSGPORT_CREATE_NO);	
}

/*
**
*/
int msgport_connect(const char *pname)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )pname, (unsigned )0, (unsigned )0,0,MSGPORT_CONNECT_NO);	
}

/*
**
*/
int msgport_destroy(int port)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )port, (unsigned )0, (unsigned )0,0,MSGPORT_DESTROY_NO);	
}


/*
**
*/
int msgport_wait(int port,  int tmout)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )port, 
		(unsigned )0, (unsigned )tmout,(unsigned )0,MSGPORT_WAT_NO);	
}
/*
**
*/
int msgport_pend(int port, void *buf, int len, int timeout)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )port, 
		(unsigned )buf, (unsigned )len,(unsigned )timeout,MSGPORT_PEND_NO);	
}

int get_public_port( int idx, int wait,time_t waitsecs ) {
  int nPort;

 	nPort = netbas_system_call(MSGPORT_NR, (unsigned )idx, 
		(unsigned )wait, (unsigned )waitsecs,(unsigned )0,MSGPORT_GET_PUBLIC);	 

  return nPort;
}

int set_public_port( int idx, int port ) {
  int nError;

 	nError = netbas_system_call(MSGPORT_NR, (unsigned )idx, 
		(unsigned )port, (unsigned )0,(unsigned )0,MSGPORT_SET_PUBLIC);	 

  
  return nError;
}
#include <stdint.h>
int get_msg_x( int port, uint32_t* code, void* buf, int len, time_t timeout ) {
  int nError;

	nError = netbas_system_call(92, (unsigned )port, 
		(unsigned )buf, (unsigned )len,(unsigned )timeout,code);	

  return nError;
}

int send_msg_x( int port, uint32_t code, const void* buf, int len, time_t timeout ) {
  int nError;

	nError = netbas_system_call(91, (unsigned )port, 
		(unsigned )buf, (unsigned )len,(unsigned )timeout,code);	

  return nError;
}


/*
**
*/
int msgport_send(int port, void *buf, int len)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )port, 
		(unsigned )buf, (unsigned )len,0,MSGPORT_SEND_NO);	
}

int msgport_notify_send(int port, void *buf, int len, int max)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )port, 
		(unsigned )buf, (unsigned )len,max,MSGPORT_NOTIFY_SEND_NO);	
}


inline int 
do_get_thread_message(tid_t thread, void* buf,	size_t len, unsigned long timeout)
{
	return netbas_system_call(94, (unsigned )thread, 
		(unsigned )buf, (unsigned )len,(unsigned )timeout,0);	
}

int 
get_thread_message(void* buf,	size_t len, time_t timeout)
{
	return do_get_thread_message(0,buf,len,timeout);	
}


int 
post_thread_message(tid_t thread, const void* buf, size_t len)
{
	return netbas_system_call(95, (unsigned )thread, 
		(unsigned )buf, (unsigned )len,0,0);	
}

/*
**
*/
int thread_sleep_on(struct thread_queue* pq, unsigned *timeout)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )pq, 
		(unsigned )timeout, (unsigned )0,0,MSGPORT_MDELAY);	
}


/*
**
*/
int thread_wakeup(struct thread_queue *pq)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )pq, 
		(unsigned )0, (unsigned )0,0,MSGPORT_WAKEUP);	
}
