/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

extern char *const *environ;

int		__execve(const char *_path, char *const _argv[], char *const _envp[], int,int);



int		execl(const char *_path, const char *_arg, ...)
{
  return(execve(_path, &_arg, environ));
}
