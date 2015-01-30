/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
int		__execve(const char *_path, char *const _argv[], char *const _envp[], int,int);

 int execve(path, argv, envp)
 const  char *path;			/* pointer to name of file to be executed */
 char * const argv[];			/* pointer to argument array */
 char * const envp[];			/* pointer to environment */
{
  register char **argtop;
  register char **envtop;

  /* Count the argument pointers and environment pointers. */
  for (argtop = argv; *argtop != (char *) NULL; ) argtop++;
  for (envtop = envp; *envtop != (char *) NULL; ) envtop++;
  return(__execve(path, argv, envp, argtop - argv, envtop - envp));
}
