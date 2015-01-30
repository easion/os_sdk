/*****************************************************************************
Socket library for Turbo C and 16-bit Watcom C that calls WSOCK[2].VXD

This code must be run inside a Windows 9x DOS box, preferably Win95
(WinSock version 1). It will not work in a Windows NT/2k/XP DOS box.

Copyright (C) 2003 by Chris Giese
<geezer@execpc.com>, http://my.execpc.com/~geezer

Based on Berci Gabor's Turbo Pascal code for accessing WSOCK2.VXD
http://www.phekda.freeserve.co.uk/gabor/ws2dos/

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.



struct  hostent {
	char	*h_name;
	char	**h_aliases;
	short	h_addrtype;
	short	h_length;
	char	**h_addr_list;
#define h_addr h_addr_list[0]
};

struct hostent *gethostbyname(const char *name);
*****************************************************************************/
#ifndef __SOCKET_H
#define	__SOCKET_H

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__GNUC__)
#define	__PACKED__	__attribute__((packed))
#else
#define	__PACKED__	/* nothing */
#endif

/* for little-endian CPU like x86 */
#define	htons(X)	bswap16(X)
#define	ntohs(X)	bswap16(X)
#define	htonl(X)	bswap32(X)
#define	ntohl(X)	bswap32(X)


/* address families */
#define	AF_UNSPEC	0
#define	AF_UNIX		1	/* for inter-process communication (IPC) */
#define	AF_INET		2	/* The Internet(TM) */

/* socket types */
#define	SOCK_STREAM	1	/* for TCP/IP, this is TCP */
#define	SOCK_DGRAM	2	/* for TCP/IP, this is UDP */
#define	SOCK_RAW	3

#define	INADDR_ANY	0uL	/* specific to TCP/IP */

/* these should be correct for most compilers... */
typedef unsigned short	uint16_t;
typedef unsigned long	uint32_t;



struct sockaddr_in		/* specific to TCP/IP */
{/* MUST BE 16 BYTES */
	uint16_t sin_family	__PACKED__;
	uint16_t sin_port	__PACKED__;
	struct in_addr sin_addr	__PACKED__;
	char sin_zero[8]	__PACKED__;
};

struct sockaddr
{/* MUST BE 16 BYTES */
	uint16_t sa_family	__PACKED__;
	char sa_data[14]	__PACKED__;
};



unsigned bswap16(unsigned arg);
unsigned long bswap32(unsigned long arg);

int socket(int family, int type, int protocol);
int bind(int s, const struct sockaddr *my_adr, int adr_len);
int listen(int s, int backlog);
int accept(int s, struct sockaddr *their_adr, int *adr_len);
int connect(int s, const struct sockaddr *their_adr, int adr_len);
int closesocket(int s);

int sendto(int s, const char *buf, int buf_len, int flags,
		const struct sockaddr *their_adr, int adr_len);
int recvfrom(int s, char *buf, int max_buf_len, int flags,
		struct sockaddr *their_adr, int *adr_len);

char *inet_ntoa(struct in_addr who);


int shutdown(int s, int how);
int getpeername (int s, struct sockaddr *name, socklen_t *namelen);
int getsockname (int s, struct sockaddr *name, socklen_t *namelen);
int getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen);
int setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen);
int recvfrom(int s, void *mem, int len, unsigned int flags,
      struct sockaddr *from, socklen_t *fromlen);

//int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
 //               struct timeval *timeout);
int ioctl(int s, long cmd, void *argp);


#ifdef __cplusplus
}
#endif

#endif

