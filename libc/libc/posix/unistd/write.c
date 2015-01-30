#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<io.h>
#include<errno.h>

ssize_t write(int handle, const void* buffer, size_t count)
{
 return _write(handle,buffer,count);
}
