/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <errno.h>

int uname(struct utsname *u)
{
 return _uname(u);
}
