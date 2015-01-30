/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#undef P_tmpdir
#define P_tmpdir "/HD/1/MENUETOS/"

static const char *tdirs[] = {"TMPDIR", "TEMP", "TMP", 0};
static const char x8[] = "XXXXXXXX";
static const size_t x8len = sizeof (x8) - 1;

char *
tempnam(const char *tmpdir, const char *pfx)
{
  char template[FILENAME_MAX];
  size_t lastc;
  char *s, *fname;
  const char **p = tdirs;

  /* Supply a default directory, if they didn't.  */
  while (!tmpdir || !*tmpdir || access (tmpdir, D_OK))
    {
      if (!*p)
	{
	  tmpdir = P_tmpdir;
	  if (access (tmpdir, D_OK))
	    return (char *)0;	/* can this ever happen? */
	  break;
	}
      tmpdir = getenv (*p++);
    }

  /* Append a slash, if needed.  */
  lastc = strlen (strcpy (template, tmpdir)) - 1;
  if (template[lastc] != '/' && template[lastc] != '\\')
    template[++lastc] = '/';

  /* Append the prefix.  */
  if (!pfx || !*pfx)
    pfx = "tm";
  strcpy (template + lastc + 1, pfx);

  /* Create the template.  */
  strncat (template, x8, 8 - strlen (pfx));

  s = mktemp (template);
  if (s)
    {
      fname = (char *)malloc (strlen (s) + 1);

      if (fname)
	return strcpy (fname, s);
    }
  return (char *)0;
}
