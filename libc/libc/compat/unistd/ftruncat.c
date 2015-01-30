/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <io.h>
#include <errno.h>

int ftruncate(int fd, off_t where)
{
 errno=EPERM;
 return -1;
}
