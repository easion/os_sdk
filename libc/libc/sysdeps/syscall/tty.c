
#include <sys/types.h>
#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <servers.h>


int	 _chmod(const char *_path, int _func, ...)
{
	errno=ENOENT;
	return -1;
}


