/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_timeb_h_
#define __dj_include_sys_timeb_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/djtypes.h>

struct timeb
{
    time_t		time;		/* Seconds since the epoch	*/
    unsigned short	millitm;
    short		timezone;
    short		dstflag;
};

extern int	ftime(struct timeb *);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_timeb_h_ */
