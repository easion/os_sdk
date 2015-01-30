/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <io.h>
#include <dir.h>
#include <errno.h>

int access(const char *fn, int flags)
{
 struct stat st;
 int i;
// printf("access %s- %x\n", fn, flags);
 i=stat(fn,&st);
 if(i) return i;

 if(flags & D_OK)
 {
  if(S_ISDIR(st.st_mode)) return 0;
  errno=EACCES;
 //printf("access %s- %x not dir\n", fn, flags);
  return -1;
 }
// printf("access %s- %x ok\n", fn, flags);
 return 0;
}


