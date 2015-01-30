/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define JICAMA
#include <stdio.h>
#include <int86.h>
#include <bios.h>

long
biostime(int cmd, long newtime)
{
  vm86regs_t r;
  r.h.ah = cmd;
  r.x.cx = newtime >> 16;
  r.x.dx = newtime & 0xffff;
  realint(0x1a, &r);
  return (r.x.cx << 16) | r.x.dx;
}
