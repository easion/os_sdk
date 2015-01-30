#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "dirstream.h"


int closedir(DIR * dir)
{
	int fd;

	if (!dir) {
		__set_errno(EBADF);
		return -1;
	}

	/* We need to check d_fd. */
	if (dir->d_fd == -1) {
		__set_errno(EBADF);
		return -1;
	}
#ifdef __UCLIBC_HAS_THREADS__
	__pthread_mutex_lock(&(dir->dd_lock));
#endif
	fd = dir->d_fd;
	dir->d_fd = -1;
#ifdef __UCLIBC_HAS_THREADS__
	__pthread_mutex_unlock(&(dir->dd_lock));
#endif
	free(dir->dd_buf);
	free(dir);
	return close(fd);
}
