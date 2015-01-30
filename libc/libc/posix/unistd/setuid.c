/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

int setuid(uid_t uid)
{
 return _setuid(uid);
}
