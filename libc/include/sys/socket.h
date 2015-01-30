
#ifndef SYS_SOCKET_H
#define SYS_SOCKET_H

#include <time.h>
#include <socketbits.h>

/*#define AF_INET		2
#define PF_INET		AF_INET

#define SOCK_STREAM	1
#define SOCK_DGRAM	2
#define SOCK_RAW	3
*/
/*#define INADDR_ANY       0
//#define INADDR_BROADCAST 0xffffffff
//#define INADDR_LOOPBACK  0x7f000001
//#define INADDR_NONE      0xffffffff

*/
struct in_addr
{
	unsigned s_addr;
};

struct sockaddr_in
{
  unsigned char sin_len;
  unsigned char sin_family;
  unsigned short sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

//typedef int socklen_t;

// Structure describing a generic socket address.  
/*struct sockaddr
  {
    unsigned short int sa_family; // Address family.  /
    char sa_data[14];		// Address data.  
  };*/
int socketStartup();
int socketCleanup();
int socket( int domain, int type, int protocol );
int closesocket( int fd );
int listen(int fd, int max);
int accept(int fd, struct sockaddr *addr, int *addrlen);
int bind( int fd, struct sockaddr *my_addr, socklen_t addrlen );

int send(int s, const void *dataptr, int size, unsigned int flags);
int recv(int s, void *mem, int len, unsigned int flags);
int connect(int s, const struct sockaddr *their_adr, int adr_len);
int closesocket(int s);

int sendto(int s, const char *buf, int buf_len, int flags,
		const struct sockaddr *their_adr, int adr_len);
int recvfrom(int s, char *buf, int max_buf_len, int flags,
		struct sockaddr *their_adr, int *adr_len);


unsigned short _devbase(int fd);
unsigned char _devfd(int fd);

//char *inet_ntoa(unsigned who);
#define	MAX_SOX		32

#if 0
/* for select(): */
struct timeval
{
	long tv_sec, tv_usec;
};

/* for select(). Do not change the layout of this structure,
because the WSOCK.VXD select() function depends on it . */
typedef struct
{
	uint32_t winsock_handle	;
/* see FD_... constants in WINSOCK.H */
	uint32_t event_mask	;
	uint32_t context	;
} fd_set[MAX_SOX];

void FD_ZERO(fd_set *arg);
void FD_SET(int s, fd_set *arg);
int select(int numfds, fd_set *read_fds, fd_set *write_fds,
		fd_set *except_fds, struct timeval *timeout);
#endif

  #endif

