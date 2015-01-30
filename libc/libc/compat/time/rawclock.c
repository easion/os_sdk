/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <time.h>

unsigned long rawclock(void)
{
 static unsigned long base = 0;
 unsigned long rv;
 rv=clock();
 if (base == 0) base = rv;
 return rv - base;
}
