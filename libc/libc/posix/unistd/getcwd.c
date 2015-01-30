/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

char *getcwd(char *buf, size_t size)
{
  return getpwd(buf,size);
}

