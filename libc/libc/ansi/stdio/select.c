/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* An implementation of select()

   Copyright 1995 by Morten Welinder
   This file maybe freely distributed and modified as long as the
   copyright notice remains.

   Notes: In a single process system as Dos this really boils down to
   something that can check whether a character from standard input
   is ready.  However, the code is organised in a way to make it easy
   to extend to multi process systems like WinNT and OS/2.  */

#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <libc/file.h>
#include <libc/local.h>
#include <libc/dosio.h>
