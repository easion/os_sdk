/*****************************************************************************
Sector-level disk I/O code for DOS.
This code is public domain (no copyright).
You can do whatever you want with it.

EXPORTS:
peekb(), peekw()
*****************************************************************************/
#ifndef __DISKIO_DOS_H
#define	__DISKIO_DOS_H

#ifdef __cplusplus
extern "C"
{
#endif

#define DJGPP
/********************************* TURBO C **********************************/
#if defined(__TURBOC__)
#include <dos.h> /* peekb(), peek() */

#define	peekw(S,O)	peek(S,O)

/* xxx - I'm not sure of the Turbo C version where these were
introduced. They are present in Turbo C++ 3.0 (__TURBOC__ == 0x401)
but not in Turbo C++ 1.0 (__TURBOC__ == 0x296) */
#if __TURBOC__<0x300
#define _DISK_RESET     0   /* controller hard reset */
#define _DISK_STATUS    1   /* status of last operation */
#define _DISK_READ      2   /* read sectors */
#define _DISK_WRITE     3   /* write sectors */
#define _DISK_VERIFY    4   /* verify sectors */
#define _DISK_FORMAT    5   /* format track */
#endif

/********************************* DJGPP ************************************/
#elif defined(__DJGPP__)
#include <sys/farptr.h> /* _farpeek[b|w]() */
#include <int86.h> /* _dos_ds */

#define	peekb(S,O)	_farpeekb(_dos_ds, 16uL * (S) + (O))
#define	peekw(S,O)	_farpeekw(_dos_ds, 16uL * (S) + (O))

/******************************** WATCOM C **********************************/
#elif defined(__WATCOMC__)

#if defined(__386__)
/* CauseWay DOS extender only */
#define	peekb(S,O)	*(unsigned char *)(16uL * (S) + (O))
#define	peekw(S,O)	*(unsigned short *)(16uL * (S) + (O))
#else
#include <dos.h> /* MK_FP() */
#define	peekb(S,O)	*(unsigned char far *)MK_FP(S,O)
#define	peekw(S,O)	*(unsigned short far *)MK_FP(S,O)
#endif

/****************************************************************************/
#else
//#error Not Turbo C, not DJGPP, not Watcom C. Sorry.
#endif

#ifdef __cplusplus
}
#endif

#endif
