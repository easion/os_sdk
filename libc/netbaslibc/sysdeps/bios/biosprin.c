/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define JICAMA
#include <stdio.h>
#include <int86.h>
#include <bios.h>

int
biosprint(int cmd, int byte, int port)
{
  vm86regs_t r;
  r.h.ah = cmd;
  r.h.al = byte;
  r.x.dx = port;
  realint(0x17, &r);
  return r.h.ah;
}
