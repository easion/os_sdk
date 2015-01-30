/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_vfs_h_
#define __dj_include_sys_vfs_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef long	fsid_t[2];

#define	MOUNT_UFS	0
#define	MOUNT_NFS	1	/* Not possible on DOS */
#define	MOUNT_CDFS	2	/* Not possible on DOS */

#define	FS_MAGIC	0x11954	/* Taken from HP-UX */

struct statfs
{
    long	f_type;
    long	f_bsize;
    long	f_blocks;
    long	f_bfree;
    long	f_bavail;
    long	f_files;
    long	f_ffree;
    fsid_t	f_fsid;
    long	f_magic;
};

extern int	statfs(const char *, struct statfs *);
extern int	fstatfs(int, struct statfs *);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_vfs_h_ */
