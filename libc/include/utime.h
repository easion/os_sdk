/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_utime_h_
#define __dj_include_utime_h_

#ifdef __cplusplus
extern "C" {
#endif



#include <sys/types.h>

struct utimbuf {
  time_t actime;
  time_t modtime;
};

int	utime(const char *_path, const struct utimbuf *_times);



#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_utime_h_ */
