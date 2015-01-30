/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/*
 * This is implementation of getmntent() and friends for DJGPP v2.x.
 *
 * Copyright (c) 1995-98 Eli Zaretskii <eliz@is.elta.co.il>
 *
 * This software may be used freely so long as this copyright notice is
 * left intact.  There is no warranty on this software.
 *
 * ---------------------------------------------------------------------
 *
 * The primary motivation for these functions was the GNU df program,
 * which lists all the mounted filesystems with a summary of the disk
 * space available on each one of them.  However, they are also useful
 * on their own right.
 *
 * Unlike Unix, where all mountable filesystems can be found on special
 * file (and thus implementing these function boils down to reading that
 * file), with MS-DOS it's a mess.  Every type of drive has its own
 * interface; there are JOINed and SUBSTed pseudo-drives and RAM disks;
 * different network redirectors hook DOS in a plethora of incompatible
 * ways; a single drive A: can be mapped to either A: or B:, etc.  That
 * is why this implementation uses almost every trick in the book to get
 * at the intimate details of every drive.  Some places where you might
 * find these tricks are: ``Undocumented DOS, 2nd ed.'' by Schulman et al
 * and Ralf Brown's Interrupt List.
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <mntent.h>
#include <dir.h>
#include <libc/dosio.h>

struct mntent * getmntent(FILE *filep)
{
 return NULL;
}

int addmntent(FILE *filep, struct mntent *mnt)
{
 return 1;
}

char * hasmntopt(struct mntent *mnt,char *opt)
{
 return strstr(mnt->mnt_opts, opt);
}

int endmntent(FILE *filep)
{
 if (filep != (FILE *)1)
 {
  errno = EBADF;    /* fake errno for invalid handle */
  return NULL;
 }
 return 1;
}
