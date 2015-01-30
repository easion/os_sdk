#include <fcntl.h>

int creat(const char *path, mode_t mode)
{
 return _creat(path,  mode);
}
