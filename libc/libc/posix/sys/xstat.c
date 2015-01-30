/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/*
 * This is file XSTAT.C
 *
 * Internal assist functions which are common to stat() and fstat().
 *
 *
 * Copyright (c) 1994-96 Eli Zaretskii <eliz@is.elta.co.il>
 *
 * This software may be used freely as long as the above copyright
 * notice is left intact.  There is no warranty on this software.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <time.h>
#include <errno.h>
#include <libc/bss.h>
#include "xstat.h"

static int xstat_count=-1;

time_t _file_time_stamp(unsigned int dos_ftime)
{
 struct tm file_tm;
 memset(&file_tm, 0, sizeof(struct tm));
 file_tm.tm_isdst = -1;    /* let mktime() determine if DST is in effect */
 file_tm.tm_sec  = (dos_ftime & 0x1f) * 2;
 file_tm.tm_min  = (dos_ftime >>  5) & 0x3f;
 file_tm.tm_hour = (dos_ftime >> 11) & 0x1f;
 file_tm.tm_mday = (dos_ftime >> 16) & 0x1f;
 file_tm.tm_mon  = ((dos_ftime >> 21) & 0x0f) - 1; /* 0 = January */
 file_tm.tm_year = (dos_ftime >> 25) + 80;
 return mktime(&file_tm);
}

/*
  (c) Copyright 1992 Eric Backus

  This software may be used freely so long as this copyright notice is
  left intact.  There is no warranty on this software.
*/

struct name_list
{
  struct name_list *next;
  char             *name;
  unsigned          mtime;
  unsigned long     size;
  long              inode;
};

ino_t _invent_inode(const char *name, unsigned time_stamp, unsigned long fsize)
{
 static struct name_list  *name_list[256];
 static int dir = (sizeof(ino_t) > 2 ? 1 : -1);
 static long inode_count = (sizeof(ino_t) > 2
                            ? (long)USHRT_MAX + 1L
                            : USHRT_MAX);
 struct name_list  *name_ptr, *prev_ptr;
 const char        *p;
 int                hash;
 if (xstat_count != __bss_count)
 {
  xstat_count = __bss_count;
  inode_count = (sizeof(ino_t) > 2 ? (long)USHRT_MAX + 1L : USHRT_MAX);
  memset (name_list, 0, sizeof name_list);
 }
 if (!name) return 0;
 if (*name && name[1] == ':' && (name[2] == '\\' || name[2] == '/'))
 {
  /* If this is a root directory, return inode = 1.  This is compatible
    with the code on stat.c which deals with root directories. */
  if (name[3] == 0) return (ino_t)1;
  name += 3;
 }
  /* If the passed name is empty, invent a new inode unconditionally.
   * This is for those unfortunate circumstances where we couldn't
   * get a name (e.g., fstat() under Novell).  For these we want at
   * least to ensure that no two calls will get the same inode number.
   * The lossage here is that you get different inodes even if you call
   * twice with the same file.  Sigh...
   */
 if (!*name)
 {
  ino_t retval = inode_count;
  inode_count += dir;
  return retval;
 }
 /* We could probably use a better hash than this */
 p = name;
 hash = 0;
 while (*p != '\0')
  hash += *p++;
 hash &= 0xff;
 /* Have we seen this string? */
 name_ptr = name_list[hash];
 prev_ptr = name_ptr;
 while (name_ptr)
 {
  if (strcmp(name, name_ptr->name) == 0 &&
      name_ptr->mtime == time_stamp &&
      name_ptr->size  == fsize) break;
  prev_ptr = name_ptr;
  name_ptr = name_ptr->next;
 }
 if (name_ptr)
 /* Same string, time stamp, and size, so same inode */
 return name_ptr->inode;
 else {
  ino_t retval;
  /* New string with same hash code */
  name_ptr = (struct name_list *)malloc(sizeof *name_ptr);
  if (name_ptr == 0) return 0;
  name_ptr->next = (struct name_list *)0;
  name_ptr->name = (char *)malloc(strlen(name)+1);
  if (name_ptr->name == 0)
  {
   free(name_ptr);
   return 0;
  }
  strcpy(name_ptr->name, name);
  name_ptr->mtime = time_stamp;
  name_ptr->size = fsize;
  name_ptr->inode = inode_count;
  if (prev_ptr)
   prev_ptr->next = name_ptr;
  else
   name_list[hash] = name_ptr;
  retval = inode_count;
  inode_count += dir; /* increment or decrement as appropriate */
  return retval;
 }
}
