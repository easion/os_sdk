/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <limits.h>
#include <libc/file.h>

int snprintf(char *str,int maxlen,const char *fmt, ...)
{
 FILE _strbuf;
 int len;
 _strbuf._flag = _IOWRT|_IOSTRG;
 _strbuf._ptr = str;
 _strbuf._cnt = maxlen;
 len = _doprnt(fmt, &(fmt)+1, &_strbuf);
 *_strbuf._ptr = 0;
 return len;
}
