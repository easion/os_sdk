/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <errno.h>
#include <sys/vfs.h>
#include <ctype.h>

int statfs(const char *path, struct statfs *buf)
{
 __libclog_printf("WARNING: statfs won't give correct result\n");
 buf->f_bavail = (512*1024*1024); /* make 512MB available */
 buf->f_bfree = (511*1024*1024); /* make 511MB free */
 buf->f_blocks = 0xFFFF;
 buf->f_bsize = 512;
 buf->f_ffree = 0xFFFF;
 buf->f_files = 0xFFFF;
 buf->f_type = 0;
 buf->f_fsid[0] = 0;
 buf->f_fsid[1] = MOUNT_UFS;
 buf->f_magic = FS_MAGIC;
 return 0;
}
