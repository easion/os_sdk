/* stats.c - malloc statistics */

/*  Copyright (C) 2001 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA. */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "imalloc.h"

#ifdef MALLOC_STATS

#include <stdio.h>
#include "mstats.h"

struct _malstats _mstats;

struct bucket_stats
malloc_bucket_stats (size)
     int size;
{
  struct bucket_stats v;

  v.nfree = 0;

  if (size < 0 || size >= NBUCKETS)
    {
      v.blocksize = 0;
      v.nused = v.nmal = v.nmorecore = v.nsplit = 0;
      return v;
    }

  v.blocksize = 1 << (size + 3);
  v.nused = _mstats.nmalloc[size];
  v.nmal = _mstats.tmalloc[size];
  v.nmorecore = _mstats.nmorecore[size];
  v.nsplit = _mstats.nsplit[size];

  v.nfree = malloc_free_blocks (size);	/* call back to malloc.c */

  return v;
}

/* Return a copy of _MSTATS, with two additional fields filled in:
   BYTESFREE is the total number of bytes on free lists.  BYTESUSED
   is the total number of bytes in use.  These two fields are fairly
   expensive to compute, so we do it only when asked to. */
struct _malstats
malloc_stats ()
{
  struct _malstats result;
  struct bucket_stats v;
  register int i;

  result = _mstats;
  result.bytesused = result.bytesfree = 0;
  for (i = 0; i < NBUCKETS; i++)
    {
      v = malloc_bucket_stats (i);
      result.bytesfree += v.nfree * v.blocksize;
      result.bytesused += v.nused * v.blocksize;
    }
  return (result);
}

static void
_print_malloc_stats (s, fp)
     char *s;
     FILE *fp;
{
  register int i;
  unsigned long totused, totfree;
  struct bucket_stats v;

  fprintf (fp, "Memory allocation statistics: %s\n\tsize\tfree\tin use\ttotal\tmorecore\tsplit\n", s ? s : "");
  for (i = totused = totfree = 0; i < NBUCKETS; i++)
    {
      v = malloc_bucket_stats (i);
      fprintf (fp, "%12lu\t%4d\t%6d\t%5d\t%8d\t%5d\n", (unsigned long)v.blocksize, v.nfree, v.nused, v.nmal, v.nmorecore, v.nsplit);
      totfree += v.nfree * v.blocksize;
      totused += v.nused * v.blocksize;
    }
  fprintf (fp, "\nTotal bytes in use: %lu, total bytes free: %lu\n",
	   totused, totfree);
  fprintf (fp, "Total mallocs: %d, total frees: %d, total reallocs: %d (%d copies)\n",
	   _mstats.nmal, _mstats.nfre, _mstats.nrealloc, _mstats.nrcopy);
  fprintf (fp, "Total sbrks: %d, total bytes via sbrk: %d\n",
  	   _mstats.nsbrk, _mstats.tsbrk);
  fprintf (fp, "Total blocks split: %d, total block coalesces: %d\n",
  	   _mstats.tbsplit, _mstats.tbcoalesce);
}

void
print_malloc_stats (s)
     char *s;
{
  _print_malloc_stats (s, stderr);
}

void
fprint_malloc_stats (s, fp)
     char *s;
     FILE *fp;
{
  _print_malloc_stats (s, fp);
}

#define TRACEROOT "/var/tmp/maltrace/trace."
extern char *inttostr ();

void
trace_malloc_stats (s)
     char *s;
{
  char ibuf[32], *ip;
  char fname[64];
  long p;
  FILE *fp;

  p = getpid();
  ip = inttostr(p, ibuf, sizeof(ibuf));
  strcpy (fname, TRACEROOT);
  strcat (fname, ip);
  fp = fopen(fname, "w");
  if (fp)
    {
      _print_malloc_stats (s, fp);
      fflush(fp);
      fclose(fp);
    }
}

#endif /* MALLOC_STATS */
