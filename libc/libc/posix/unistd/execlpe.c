/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

int execlpe(const char *path, const char *argv0, ... /*, const char **envp */)
{
 errno=EINVAL;
 return -1;
}
