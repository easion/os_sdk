/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <errno.h>
#include <sys/times.h>
#include <time.h>

clock_t
times(struct tms *buffer)
{
  if (buffer == 0)
  {
    errno = EINVAL;
    return (clock_t)(-1);
  }
  return _times(buffer);
}

clock_t clock()
{
	return _times((struct tms *)0);
}

