/*
 * This file is complete hack.
 */

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dir.h>
#include <libc/bss.h>
#include "xstat.h"
#include <dirent.h>

static int day_n[] = { 0,31,59,90,120,151,181,212,243,273,304,334,0,0,0,0 };
		  /* JanFebMarApr May Jun Jul Aug Sep Oct Nov Dec */

/* Convert a MS-DOS time/date pair to a UNIX date (seconds since 1 1 70). */

static inline int date_dos2unix(unsigned short time,unsigned short date)
{
 int month,year,secs;
 /* first subtract and mask after that... Otherwise, if
    date == 0, bad things happen */
 month = ((date >> 5) - 1) & 15;
 year = date >> 9;
 secs = (time & 31)*2+60*((time >> 5) & 63)+(time >> 11)*3600+86400*
     ((date & 31)-1+day_n[month]+(year/4)+year*365-((year & 3) == 0 &&
     month < 2 ? 1 : 0)+3653);
 return secs;
}

#define FAKE_DIR_SIZE	(1<<20)
#define DIRENT_SIZE	(sizeof(struct msdos_dir_entry))

static unsigned char fixed_stat_path[PATH_MAX];

int stat(const char *path, struct stat *statbuf);


int lstat(const char *path, struct stat *statbuf)
{
 return stat(path,statbuf);
}
