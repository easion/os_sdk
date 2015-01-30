/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <libc/dosio.h>

void _chdir(char * path);

int chdir (const char *dirname)
{
 _chdir((char *)dirname);
 return 0;
}
