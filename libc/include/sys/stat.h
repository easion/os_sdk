/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_stat_h_
#define __dj_include_sys_stat_h_

#ifdef __cplusplus
extern "C" {
#endif


#include <sys/types.h>
#include <sys/djtypes.h>

struct  stat{ /* kernel stat */
	unsigned short st_dev;
	unsigned short __pad1;
	unsigned long st_ino;
	unsigned short st_mode;
	unsigned short st_nlink;
	unsigned short st_uid;
	unsigned short st_gid;
	unsigned short st_rdev;
	unsigned short __pad2;
	unsigned long  st_size;
	unsigned long  st_blksize;
	unsigned long  st_blocks;
	unsigned long  st_atime;
	unsigned long  __unused1;
	unsigned long  st_mtime;
	unsigned long  __unused2;
	unsigned long  st_ctime;
	unsigned long  __unused3;
	unsigned long  __unused4;
	unsigned long  __unused5;
};


int	chmod(const char *_path, mode_t _mode);
int	fstat(int _fildes, struct stat *_buf);
int	mkdir(const char *_path, mode_t _mode);
int	mkfifo(const char *_path, mode_t _mode);
int	stat(const char *_path, struct stat *_buf);
mode_t	umask(mode_t _cmask);

/* POSIX.1 doesn't mention these at all */

#define S_IFMT  00170000
#define S_IFLNK	 0120000
#define S_IFREG  0100000
#define S_IFBLK  0060000
#define S_IFDIR  0040000
#define S_IFCHR  0020000
#define S_IFIFO  0010000
#define S_ISUID  0004000
#define S_ISGID  0002000
#define S_ISVTX  0001000

#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)

#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100

#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010

#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001


#define S_IFLABEL	0x5000
#define S_ISLABEL(m)	(((m) & 0xf000) == 0x5000)

void	        _fixpath(const char *, char *);
unsigned short  _get_magic(const char *, int);
int             _is_executable(const char *, int, const char *);
int		mknod(const char *_path, mode_t _mode, dev_t _dev);
char          * _truename(const char *, char *);

/* Bit-mapped variable _djstat_flags describes what expensive
   f?stat() features our application needs.  If you don't need a
   feature, set its bit in the variable.  By default, all the
   bits are cleared (i.e., you get the most expensive code).  */
#define _STAT_INODE         1   /* should we bother getting inode numbers? */
#define _STAT_EXEC_EXT      2   /* get execute bits from file extension? */
#define _STAT_EXEC_MAGIC    4   /* get execute bits from magic signature? */
#define _STAT_DIRSIZE       8   /* compute directory size? */
#define _STAT_ROOT_TIME  0x10   /* try to get root dir time stamp? */
#define _STAT_WRITEBIT   0x20   /* fstat() needs write bit? */

extern unsigned short   _djstat_flags;

/* Bit-mapped variable _djstat_fail_bits describes which individual
   undocumented features f?stat() failed to use.  To get a human-
   readable description of the bits, call _djstat_describe_lossage(). */
#define _STFAIL_SDA         1   /* Get SDA call failed */
#define _STFAIL_OSVER       2   /* Unsupported DOS version */
#define _STFAIL_BADSDA      4   /* Bad pointer to SDA */
#define _STFAIL_TRUENAME    8   /* _truename() failed */
#define _STFAIL_HASH     0x10   /* inode defaults to hashing */
#define _STFAIL_LABEL    0x20   /* Root dir, but no volume label */
#define _STFAIL_DCOUNT   0x40   /* dirent_count ridiculously large */
#define _STFAIL_WRITEBIT 0x80   /* fstat() failed to get write access bit */
#define _STFAIL_DEVNO   0x100   /* fstat() failed to get device number */
#define _STFAIL_BADSFT  0x200   /* SFT entry found, but can't be trusted */
#define _STFAIL_SFTIDX  0x400   /* bad SFT index in JFT */
#define _STFAIL_SFTNF   0x800   /* file entry not found in SFT array */

extern unsigned short   _djstat_fail_bits;

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_stat_h_ */
