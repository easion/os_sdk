/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_times_h_
#define __dj_include_sys_times_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/djtypes.h>

struct tms {
  clock_t tms_utime;
  clock_t tms_cstime;
  clock_t tms_cutime;
  clock_t tms_stime;
};

clock_t	times(struct tms *buffer);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_times_h_ */
