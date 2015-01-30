#include <stdio.h>
#include <stdlib.h>
#include <netbas/netbas.h>
#include <sys/socket.h>



#define API_SOCKET	1		/* sock(2)		*/
#define API_BIND		2		/* bind(2)			*/
#define API_CONNECT	3		/* connect(2)		*/
#define API_LISTEN	4		/* listen(2)		*/
#define API_ACCEPT	5		/* accept(2)		*/
#define API_GETSOCKNAME	6		/* getsockname(2)		*/
#define API_GETPEERNAME	7		/* getpeername(2)		*/
#define API_SOCKETPAIR	8		/* sockpair(2)		*/
#define API_SEND		9		/* send(2)			*/
#define API_RECV		10		/* recv(2)			*/
#define API_SENDTO	11		/* sendto(2)		*/
#define API_RECVFROM	12		/* recvfrom(2)		*/
#define API_SHUTDOWN	13		/* shutdown(2)		*/
#define API_SETSOCKOPT	14		/* setsockopt(2)		*/
#define API_GETSOCKOPT	15		/* getsockopt(2)		*/
#define API_SENDMSG	16		/* sendmsg(2)		*/
#define API_RECVMSG	17		/* recvmsg(2)		*/
#define API_SELECT	18		/* 		*/
#define API_netbas_ioctl	19		/* 		*/
