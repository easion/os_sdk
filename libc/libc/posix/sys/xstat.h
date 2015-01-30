#ifndef __XSTAT_H
#define __XSTAT_H

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef EFAULT
#define EFAULT  14
#endif

extern ino_t            _invent_inode(const char *, unsigned, unsigned long);
extern long             __filelength(int);
time_t _file_time_stamp(unsigned int dos_ftime);

#endif
