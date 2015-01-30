#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dirstruc.h"


#if 0
DIR * opendir(const char *name)
{
 int length;
 char * dn_buf=malloc(512);
 if(!dn_buf) return 0;
 DIR *dir = (DIR *)malloc(sizeof(DIR));
 if (dir == 0)
 {
  free(dn_buf);
  return 0;
 }
 dir->cur_ent = 0;
 _fixpath (name, dn_buf);
 __libc_init_readdir(dn_buf,&dir->ri);
 free(dn_buf);
 return dir;
}
#endif
