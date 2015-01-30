/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>


unsigned int
usleep(unsigned int _useconds)
{
  unsigned int cl_time;
  unsigned int start_time = clock();

  /* 977 * 1024 is about 1e6.  The funny logic keeps the math from
     overflowing for large _useconds */
  _useconds >>= 10;
  cl_time = _useconds * 91 / 977;

  while (1)
  {
    unsigned int elapsed = clock() - start_time;
    if (elapsed >= cl_time)
      break;
   // __dpmi_yield();
  }
  return 0;
}


