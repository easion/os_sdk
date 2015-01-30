#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
 
int chown(const char *path, uid_t owner, gid_t group)
{
 int i;
 i=open(path,O_RDONLY);
 if(i<0)
 {
  errno = ENOENT;
  return -1;
 }
 close(i);
 return 0;
}
