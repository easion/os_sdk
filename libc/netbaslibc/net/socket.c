#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#if 0

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
#define API_IOCTL	19		/* 		*/


static int socket_fd;


int socketStartup()
{
	int fd = open("/dev/socket", 2);
	socket_fd = fd;
	return fd;
}

int socketCleanup()
{
	close(socket_fd);
}

int socket( int domain, int type, int protocol )
	{
    int retval;
    unsigned long m_buf[4];

    m_buf[0] = domain;
    m_buf[1] = type;
    m_buf[2] = protocol;
    m_buf[3] = NULL;

    retval = ioctl( socket_fd, API_SOCKET, m_buf);

	if (retval<0)
	{
		return retval;
	}
    return retval + socket_fd;
}

int closesocket( int fd )
{
	close(fd);
    return 0;
}

int listen(int fd, int max)
{
    int retval;

	retval = ioctl( fd, API_LISTEN, &max);
    return retval;	
}

int connect(int fd, const struct sockaddr *their_adr, int adr_len)
{
    int retval;
    void *m_buf[3];

    m_buf[0] = their_adr;
    m_buf[1] = adr_len;
    m_buf[2] = NULL;

    retval = ioctl( fd, API_CONNECT, m_buf);

	if (retval<0)
	{
		return retval;
	}

    return retval;	
}

int accept(int fd, struct sockaddr *addr, int *addrlen)
{
    int retval;
    void *m_buf[3];

    m_buf[0] = addr;
    m_buf[1] = addrlen;
    m_buf[2] = NULL;

    retval = ioctl( fd, API_ACCEPT, m_buf);

	if (retval<0)
	{
		return retval;
	}

    return retval+socket_fd;	
}

int bind( int fd, struct sockaddr *my_addr, socklen_t addrlen )
{
    int retval;
    unsigned long m_buf[3];
    m_buf[0] = (unsigned long)my_addr;
    m_buf[1] = addrlen;
    m_buf[2] = 0;

   retval = ioctl( fd, API_BIND, m_buf);
    return retval;
}


int sendto(int fd, const char *buf, int buf_len, int flags,
		const struct sockaddr *their_adr, int adr_len)
{
	int retval;
	unsigned long m_buf[6];
	m_buf[0] = (unsigned long)buf;
	m_buf[1] = (unsigned long)buf_len;
	m_buf[2] = (unsigned long)flags;
	m_buf[3] = (unsigned long)their_adr;
	m_buf[4] = adr_len;
	m_buf[5] = 0;

	retval = ioctl( fd, API_SENDTO, m_buf);
	return retval;
}

int recvfrom(int fd, char *userbuf, int max_buf_len, int flags,
		struct sockaddr *their_adr, int *adr_len)
{
	int retval;
	unsigned long m_buf[6];
	m_buf[0] = (unsigned long)userbuf;
	m_buf[1] = (unsigned long)max_buf_len;
	m_buf[2] = (unsigned long)flags;
	m_buf[3] = (unsigned long)their_adr;
	m_buf[4] = (unsigned long)adr_len;
	m_buf[5] = 0;

	retval = ioctl( fd, API_RECVFROM, m_buf);
	return retval;
}



int shutdown(int fd, int how)
{
    int retval;
    unsigned long m_buf[3];
    m_buf[0] = (unsigned long)how;
    m_buf[1] = 0;

   retval = ioctl( fd, API_SHUTDOWN, m_buf);
    return retval;
}

int getpeername (int fd, struct sockaddr *name, socklen_t *namelen)
{
	int retval;
	unsigned long m_buf[3];

	m_buf[0] = (unsigned long)name;
	m_buf[1] = (unsigned long)namelen;
	m_buf[2] = 0;	

	retval = ioctl( fd, API_GETPEERNAME, m_buf);
	return retval;
}

int getsockname (int fd, struct sockaddr *name, socklen_t *namelen)
{
	int retval;
	unsigned long m_buf[3];

	m_buf[0] = (unsigned long)name;
	m_buf[1] = (unsigned long)namelen;
	m_buf[2] = 0;	

	retval = ioctl( fd, API_GETSOCKNAME, m_buf);
	return retval;
}

int getsockopt (int fd, int level, int optname, 
void *optval, socklen_t *optlen)
{
	int retval;
	unsigned long m_buf[5];
	m_buf[0] = (unsigned long)level;
	m_buf[1] = (unsigned long)optname;
	m_buf[2] = (unsigned long)optval;
	m_buf[3] = (unsigned long)optlen;
	m_buf[4] = 0;

	retval = ioctl( fd, API_GETSOCKOPT, m_buf);
	return retval;
}

int setsockopt (int fd, int level, int optname, 
const void *optval, socklen_t optlen)
{ 
	int retval;
	unsigned long m_buf[5];
	m_buf[0] = (unsigned long)level;
	m_buf[1] = (unsigned long)optname;
	m_buf[2] = (unsigned long)optval;
	m_buf[3] = (unsigned long)optlen;
	m_buf[4] = 0;

	retval = ioctl( fd, API_SETSOCKOPT, m_buf);
	return retval;
}

int recv(int fd, void *mem, int len, unsigned int flags)
{ 
	int retval;
	unsigned long m_buf[4];
	m_buf[0] = (unsigned long)mem;
	m_buf[1] = (unsigned long)len;
	m_buf[2] = (unsigned long)flags;
	m_buf[3] = 0;

	retval = ioctl( fd, API_RECV, m_buf);
	return retval;
}


int send(int fd, const void *dataptr, int size, unsigned int flags)
{ 
	int retval;
	unsigned long m_buf[4];
	m_buf[0] = (unsigned long)dataptr;
	m_buf[1] = size;
	m_buf[2] = flags;
	m_buf[3] = 0;

	retval = ioctl( fd, API_SEND, m_buf);
	return retval;
}

int socket_select(int maxfdp1, fd_set *readset, fd_set *writeset,
fd_set *exceptset, struct timeval *_timeout)
{ 
	int retval;
	unsigned long m_buf[6];
	int sys_select( int fd, int cmd, ...);

	m_buf[0] = (unsigned long)maxfdp1;
	m_buf[1] = (unsigned long)readset;
	m_buf[2] = (unsigned long)writeset;
	m_buf[3] = (unsigned long)exceptset;
	m_buf[4] = (unsigned long)_timeout;
	m_buf[5] = 0;

	//printf("maxfdp1 is %d\n", maxfdp1);

	retval = sys_select( maxfdp1, API_SELECT, m_buf);
	return retval;
}



unsigned char _devfd(int fd)
{
	int ret = fd & 0x000000ff;
	return (unsigned char)ret;
}

unsigned short _devbase(int fd)
{
	int ret = fd & 0x0000ff00;
	return (unsigned short)ret;
}
#endif
