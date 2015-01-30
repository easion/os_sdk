#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "dirstream.h"


int readdir_r(DIR *dir, struct dirent *entry, struct dirent **result)
{
	int ret;
	ssize_t bytes;
	struct dirent *de;

	if (!dir) {
	    __set_errno(EBADF);
	    return(EBADF);
	}
	de = NULL;

#ifdef __UCLIBC_HAS_THREADS__
	__pthread_mutex_lock(&(dir->dd_lock));
#endif

	
all_done:

#ifdef __UCLIBC_HAS_THREADS__
	__pthread_mutex_unlock(&(dir->dd_lock));
#endif
        return((de != NULL)? 0 : ret);
}
