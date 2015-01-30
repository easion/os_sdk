/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <sys/stat.h>
#include <errno.h>
 
int chmod(const char *filename, int pmode)
{
 errno=EPERM;
 return -1;
}
