/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libc/dosio.h>
 
int mkdir(const char *dirname, mode_t mode)
{
 errno=_mkdir(dirname,mode);
 return errno;
}
