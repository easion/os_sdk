/* Copyright (C) 1992,95,96,97,98,99,2000,2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _SYS_STAT_H
# error "Never include <bits/stat.h> directly; use <sys/stat.h> instead."
#endif

#ifndef _BITS_STAT_H
#define _BITS_STAT_H

/* Versions of the `struct stat' data structure.  */
#define _STAT_VER_LINUX_OLD	1
#define _STAT_VER_KERNEL	1
#define _STAT_VER_SVR4		2
#define _STAT_VER_LINUX		3
#define _STAT_VER		_STAT_VER_LINUX	/* The one defined below.  */

/* Versions of the `xmknod' interface.  */
#define _MKNOD_VER_LINUX	1
#define _MKNOD_VER_SVR4		2
#define _MKNOD_VER		_MKNOD_VER_LINUX /* The bits defined below.  */

struct  stat{ /* kernel stat */
	unsigned short st_dev;
	unsigned short st___pad1;
	unsigned long st_ino;
	unsigned short st_mode;
	unsigned short st_nlink;
	unsigned short st_uid;
	unsigned short st_gid;
	unsigned short st_rdev;
	unsigned short st___pad2;
	unsigned long  st_size;
	unsigned long  st_blksize;
	unsigned long  st_blocks;
	unsigned long  st_atime;
	unsigned long  st___unused1;
	unsigned long  st_mtime;
	unsigned long  st___unused2;
	unsigned long  st_ctime;
	unsigned long  st___unused3;
	unsigned long  st___unused4;
	unsigned long  st___unused5;
};


struct stat1
{
    __dev_t st_dev;			/* Device.  */
    unsigned short int __pad1;
#ifndef __USE_FILE_OFFSET64
    __ino_t st_ino;			/* File serial number.	*/
#else
    __ino_t __st_ino;			/* 32bit file serial number.	*/
#endif
    __mode_t st_mode;			/* File mode.  */
    __nlink_t st_nlink;			/* Link count.  */
    __uid_t st_uid;			/* User ID of the file's owner.	*/
    __gid_t st_gid;			/* Group ID of the file's group.*/
    __dev_t st_rdev;			/* Device number, if device.  */
    unsigned short int __pad2;
#ifndef __USE_FILE_OFFSET64
    __off_t st_size;			/* Size of file, in bytes.  */
#else
    __off64_t st_size;			/* Size of file, in bytes.  */
#endif
    __blksize_t st_blksize;		/* Optimal block size for I/O.  */

#ifndef __USE_FILE_OFFSET64
    __blkcnt_t st_blocks;		/* Number 512-byte blocks allocated. */
#else
    __blkcnt64_t st_blocks;		/* Number 512-byte blocks allocated. */
#endif
    __time_t st_atime;			/* Time of last access.  */
    unsigned long int __unused1;
    __time_t st_mtime;			/* Time of last modification.  */
    unsigned long int __unused2;
    __time_t st_ctime;			/* Time of last status change.  */
    unsigned long int __unused3;
#ifndef __USE_FILE_OFFSET64
    unsigned long int __unused4;
    unsigned long int __unused5;
#else
    __ino64_t st_ino;			/* File serial number.	*/
#endif
};

#ifdef __USE_LARGEFILE64
struct stat64
{
    __dev_t st_dev;			/* Device.  */
    unsigned int __pad1;

    __ino_t __st_ino;			/* 32bit file serial number.	*/
    __mode_t st_mode;			/* File mode.  */
    __nlink_t st_nlink;			/* Link count.  */
    __uid_t st_uid;			/* User ID of the file's owner.	*/
    __gid_t st_gid;			/* Group ID of the file's group.*/
    __dev_t st_rdev;			/* Device number, if device.  */
    unsigned int __pad2;
    __off64_t st_size;			/* Size of file, in bytes.  */
    __blksize_t st_blksize;		/* Optimal block size for I/O.  */

    __blkcnt64_t st_blocks;		/* Number 512-byte blocks allocated. */
    __time_t st_atime;			/* Time of last access.  */
    unsigned long int __unused1;
    __time_t st_mtime;			/* Time of last modification.  */
    unsigned long int __unused2;
    __time_t st_ctime;			/* Time of last status change.  */
    unsigned long int __unused3;
    __ino64_t st_ino;			/* File serial number.		*/
};
#endif


/* Tell code we have these members.  */
#define	_STATBUF_ST_BLKSIZE
#define _STATBUF_ST_RDEV

/* Encoding of the file mode.  */

#define	__S_IFMT	0170000	/* These bits determine file type.  */

/* File types.  */
#define	__S_IFDIR	0040000	/* Directory.  */
#define	__S_IFCHR	0020000	/* Character device.  */
#define	__S_IFBLK	0060000	/* Block device.  */
#define	__S_IFREG	0100000	/* Regular file.  */
#define	__S_IFIFO	0010000	/* FIFO.  */
#define	__S_IFLNK	0120000	/* Symbolic link.  */
#define	__S_IFSOCK	0140000	/* Socket.  */

/* POSIX.1b objects.  Note that these macros always evaluate to zero.  But
   they do it by enforcing the correct use of the macros.  */
#define __S_TYPEISMQ(buf)  ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSEM(buf) ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSHM(buf) ((buf)->st_mode - (buf)->st_mode)

/* Protection bits.  */

#define	__S_ISUID	04000	/* Set user ID on execution.  */
#define	__S_ISGID	02000	/* Set group ID on execution.  */
#define	__S_ISVTX	01000	/* Save swapped text after use (sticky).  */
#define	__S_IREAD	0400	/* Read by owner.  */
#define	__S_IWRITE	0200	/* Write by owner.  */
#define	__S_IEXEC	0100	/* Execute by owner.  */

#endif	/* _BITS_STAT_H */
