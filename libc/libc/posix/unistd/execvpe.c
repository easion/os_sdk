/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

int execvpe(const char *path, char * const argv[], char * const envp[])
{
 errno=EINVAL;
 return -1;
}
