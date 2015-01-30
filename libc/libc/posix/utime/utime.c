/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <utime.h>		/* For utime() */
#include <time.h>		/* For localtime() */
#include <fcntl.h>		/* For open() */
#include <unistd.h>
#include <errno.h>		/* For errno */
#include <sys/stat.h>

/* An implementation of utime() for DJGPP.  The utime() function
   specifies an access time and a modification time.  DOS has only one
   time, so we will (arbitrarily) use the modification time. */
int utime(const char *path, const struct utimbuf *times)
{
 int i;
 struct stat p;
 i=stat(path,&p);
 if(!i && times)
 {
  times->actime=p.st_atime;
  times->modtime=p.st_mtime;
 }
 return i;
}
