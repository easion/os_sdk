
#include <features.h>
//#include <netdb.h>
#include <stdlib.h>
#include <string.h>

//#ifndef FD_SET
  #undef  FD_SETSIZE
  #undef  FD_SET
  #undef  FD_CLR
  #undef  FD_ISSET
  #undef  FD_ZERO
  #define FD_SETSIZE    16
  #define FD_SET(n, p)  ((p)->fd_bits[(n)/8] |=  (1 << ((n) & 7)))
  #define FD_CLR(n, p)  ((p)->fd_bits[(n)/8] &= ~(1 << ((n) & 7)))
  #define FD_ISSET(n,p) ((p)->fd_bits[(n)/8] &   (1 << ((n) & 7)))
  #define FD_ZERO(p)    memset((void*)(p),0,sizeof(*(p)))

  typedef struct lwip_fd_set {
          unsigned char fd_bits [(FD_SETSIZE+7)/8];
        } lwip_fd_set;


  struct timeval_lwip {
    long    tv_sec;         /* seconds */
    long    tv_usec;        /* and microseconds */
  };

int socket_poll(int fd, int timeout)
{
	int error;
	lwip_fd_set fds;
	struct timeval_lwip tv;

	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	tv.tv_sec = timeout;
	tv.tv_usec = 0;

	error=select(fd + 1, &fds, NULL, NULL, &tv);

	if (error <= 0) {
		//DPRINTF("Timeout\n");

		/* timed out, so retry send and receive, 
		 * to next nameserver on queue */
		//goto again;
	}

	return error;
}

//#endif

