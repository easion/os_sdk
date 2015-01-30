#include <unistd.h>
#include <errno.h>

#include <libc/dosio.h>

off_t lseek(int handle, off_t offset, int whence)
{
 return _lseek(handle,offset,whence);
}
