
#define JICAMA
#include <stdio.h>
#include <int86.h>
#include <bios.h>

int
bios_cdrom_exist(void)
{
  vm86regs_t r;
  r.x.ax=0x1500;
  r.x.bx=0;
  realint(0x2f, &r);
  printf("FIRST CDROM(%d): %c \n", r.x.bx, r.x.cx+'A');
  return r.x.bx;
}
