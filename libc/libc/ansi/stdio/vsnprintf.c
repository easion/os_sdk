/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <libc/file.h>

int vsnprintf(char *str,int maxlen,const char *fmt, va_list ap)
{
  FILE f;
  int len;

  f._flag = _IOWRT|_IOSTRG;
  f._ptr = str;
  f._cnt = maxlen;
  len = _doprnt(fmt, ap, &f);
  *f._ptr = 0;
  return len;
}
