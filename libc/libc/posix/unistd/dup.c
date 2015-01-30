/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>
#include <io.h>
#include <libc/dosio.h>

int _dup(int fd);

int dup(int fd)
{
 return _dup( fd);
}

