/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define JICAMA
#include <stdio.h>
#include <int86.h>
#include <bios.h>

int
biosmemory(void)
{
  vm86regs_t r;
  realint(0x12, &r);
  return r.x.ax;
}
