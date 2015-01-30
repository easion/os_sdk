/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

int _pipe(int _fildes[2]);

int pipe(int _fildes[2])
{	
  return _pipe(_fildes);
}
