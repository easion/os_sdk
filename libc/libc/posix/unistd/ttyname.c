/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>

static char dev_con[] = "con";

/* ARGSUSED */
char * ttyname(int fildes)
{
  if (__isatty(fildes))
    return dev_con;
  else
    return 0;
}    
