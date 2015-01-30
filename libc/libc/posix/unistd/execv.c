/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

extern char * const *environ;

int		execv(const char *name, char *const argv[])
{
  return(execve(name, argv, environ));
}

