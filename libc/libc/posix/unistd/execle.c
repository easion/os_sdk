/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>
int		__execve(const char *_path, char *const _argv[], char *const _envp[], int,int);

extern char **environ;		/* environment pointer */

#define	PTRSIZE	(sizeof(char *))


int		execle(const char *_path, const char *_arg, ...)
{
  char **p;
  p = (char **) &_arg;
  while (*p++)			/* null statement */
	;
  return(execve(_path, &_arg, (char **) *p));
}

