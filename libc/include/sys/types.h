/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_types_h_
#define __dj_include_sys_types_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/djtypes.h>
#include <inttypes.h>

typedef unsigned long u_long;
typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned char u_char;
  
typedef int		dev_t;
typedef int		ino_t;
typedef int		mode_t;
typedef int		nlink_t;

/* Allow including program to override.  */
#ifndef FD_SETSIZE
#define FD_SETSIZE 256
#endif

typedef struct fd_set {
  unsigned char fd_bits [((FD_SETSIZE) + 7) / 8];
} fd_set;

#define FD_SET_TMP(n, p)    ((p)->fd_bits[(n) / 8] |= (1 << ((n) & 7)))
#define FD_SET(n, p)   FD_SET_TMP(_devfd(n), p)
#define FD_CLR(n, p)	((p)->fd_bits[(n) / 8] &= ~(1 << ((n) & 7)))
#define FD_ISSET(n, p)	((p)->fd_bits[(n) / 8] & (1 << ((n) & 7)))
#define FD_ZERO(p)	memset ((void *)(p), 0, sizeof (*(p)))

#define __socklen_t_defined
typedef unsigned int socklen_t;
//typedef unsigned short sa_family_t;

typedef unsigned long u_int32_t;
typedef unsigned short u_int16_t;
typedef unsigned char u_int8_t;

typedef unsigned long caddr_t;

typedef void * __ptr_t;

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_types_h_ */
