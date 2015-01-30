/*****************************************************************************
Sector-level disk I/O code for various OSes
This code is public domain (no copyright).
You can do whatever you want with it.

EXPORTS (API):
DEBUG(), BPS, LE16(), LE32(), disk_t,
int read_sector(disk_t *disk, unsigned long lba, unsigned char *buf);
int write_sector(disk_t *disk, unsigned long lba, unsigned char *buf);
int is_fat_bootsector(unsigned char *buf);
int open_disk(disk_t *disk, unsigned drive_num);
*****************************************************************************/
#ifndef __DISKIO_H
#define	__DISKIO_H

#ifdef __cplusplus
extern "C"
{
#endif

#if 1
#define	DEBUG(X)	X
#else
#define	DEBUG(X)	/* nothing */
#endif

#define	peekb(S,O)	_farpeekb(USER_GLOBAL_DATA, 16uL * (S) + (O))
#define	peekw(S,O)	_farpeekw(USER_GLOBAL_DATA, 16uL * (S) + (O))

#ifdef __cplusplus
}
#endif

#endif
