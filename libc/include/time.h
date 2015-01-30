/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_time_h_
#define __dj_include_time_h_

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCKS_PER_SEC	100

#include <sys/djtypes.h>
  
/* Some programs think they know better... */
#undef NULL

#define NULL 0

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  char *__tm_zone;
  int __tm_gmtoff;
};

char *		asctime(const struct tm *_tptr);
clock_t		clock(void);
char *		ctime(const time_t *_cal);
double		difftime(time_t _t1, time_t _t0);
struct tm *	gmtime(const time_t *_tod);
struct tm *	localtime(const time_t *_tod);
time_t		mktime(struct tm *_tptr);
size_t		strftime(char *_s, size_t _n, const char *_format, const struct tm *_tptr);
time_t		time(time_t *_tod);

#define CLK_TCK	CLOCKS_PER_SEC

extern char *tzname[2];

void	tzset(void);

#define tm_zone __tm_zone
#define tm_gmtoff __tm_gmtoff

struct timeval {
  time_t tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

#include <sys/types.h>

struct timespec {
 time_t tv_sec;
 long tv_nsec;
};

typedef long long uclock_t;
#define UCLOCKS_PER_SEC 1193180

int		gettimeofday(struct timeval *_tp, struct timezone *_tzp);
unsigned long	rawclock(void);

int socket_select(int maxfdp1, fd_set *readset, fd_set *writeset,
fd_set *exceptset, struct timeval *_timeout);
#define select socket_select 

int		settimeofday(struct timeval *_tp, ...);
void		tzsetwall(void);
uclock_t	uclock(void);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_time_h_ */
