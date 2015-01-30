/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <errno.h>
#include <unistd.h>
#include <libc/dosio.h>

int rmdir(const char *dirname)
{
 return _rmdir(dirname);
}
