#define JICAMA



#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <jthread.h>

enum{
	MSGPORT_CREATE_NO=1,
	MSGPORT_CONNECT_NO=2,
	MSGPORT_DESTROY_NO=3,
	MSGPORT_WAT_NO=4,
	MSGPORT_PEND_NO=5,
	MSGPORT_SEND_NO=6,
	MSGPORT_MDELAY=7,
	MSGPORT_SLEEP=8,
	MSGPORT_WAKEUP=9
};


#define MSGPORT_NR (93)

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

/*
**
*/
int msgport_send(int port, void *buf, int len, int timeout)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )port, 
		(unsigned )buf, (unsigned )len,timeout,MSGPORT_SEND_NO);	
}

/*
**
*/
int thread_msleep(int msec)
{
	return netbas_system_call(MSGPORT_NR, (unsigned )msec, 
		(unsigned )0, (unsigned )0,0,MSGPORT_MDELAY);	
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
