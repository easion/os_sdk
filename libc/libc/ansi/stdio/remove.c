/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <io.h>
#include <stdio.h>
#include <errno.h>
#include <libc/dosio.h>
 
int remove(const char *fn)
{
 errno=EACCES;
 return -1;
}
