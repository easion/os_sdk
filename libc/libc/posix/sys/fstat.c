#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "xstat.h"

int fstat(int handle, struct stat *statbuf)
{
 //_io_struct * qay=dosemu_getiostruct(handle);
/* if(!qay)
 {
  errno=EINVAL;
  return -1;
 }*/
 return -1;//stat(qay->filename,statbuf);
}
