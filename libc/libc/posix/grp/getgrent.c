/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <grp.h>
#include <unistd.h>
#include <stdio.h>

static int tag = 0;

struct group * getgrent(void)
{
  if (tag == 0)
  {
    tag = 1;
    return getgrgid(getgid());
  }
  return 0;
}

/* ARGSUSED */
struct group *
fgetgrent(FILE *f)
{
  return getgrent();
}

void
setgrent(void)
{
  tag = 0;
}

void
endgrent(void)
{
  tag = 0;
}
