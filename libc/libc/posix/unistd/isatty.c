/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>

int isatty(int fd)
{
 return __isatty(fd);
}
