/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>
#include <io.h>
#include <libc/dosio.h>

int _dup2(int fd, int fd2);

int dup2(int fd, int newfd)
{
 return _dup2( fd,  newfd);
}
