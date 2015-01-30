#include <dirent.h>
#include <errno.h>
#include "dirstream.h"

int dirfd(DIR * dir)
{
	if (!dir || dir->d_fd == -1) {
		__set_errno(EBADF);
		return -1;
	}

	return dir->d_fd;
}
