/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdlib.h>

int
mbtowc(wchar_t *pwc, const char *s, size_t n)
{
  int x = 0;
  if (s == 0)
    return 0;
  if (*s)
    x = 1;

  if (pwc)
    *pwc = *s;

  return x;
}


size_t
mbstowcs(wchar_t *wcs, const char *s, size_t n)
{
  int i;
  for (i=0; s[i] && (i<n-1); i++)
    wcs[i] = s[i];
  wcs[i] = 0;
  return i;
}


int
mblen(const char *s, size_t n)
{
  if (s)
  {
    if (n == 0 || *s == 0)
      return 0;
    return 1;
  }
  else
    return 1;
}
