/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/*
 * BIOSDISK.C.
 *
 * Modified by Peter Sulyok 1995 <sulyok@math.klte.hu>.
 *
 * This file is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#define JICAMA
#include <stdio.h>
#include <string.h>
#include <sys/farptr.h>
#include <int86.h>
#include <bios.h>

#define MAX_SECTOR 8


int
biosdisk(int cmd, int drive, int head, int track,
	 int sector, int nsects, void *buffer)
{
  int seg=0, ofs=0, xfer=0, before=0;
  vm86regs_t r;
  u32_t __tb;
  int sz;

  real_address(&__tb, &sz);

  switch (cmd)
  {
  case _DISK_READ:
    xfer = 512 * nsects;
    before = 0;
    break;
  case _DISK_WRITE:
    xfer = 512 * nsects;
    before = 1;
    break;
  case _DISK_FORMAT:
    xfer = 2 * 256;
    before = 1;
    break;
  case 0x0a:
    xfer = (512+7) * nsects;
    before = 0;
    break;
  case 0x0b:
    xfer = (512+7) * nsects;
    before = 1;
    break;
  case 0x0e:
    xfer = 512;
    before = 0;
    break;
  case 0x0f:
    xfer = 512;
    before = 1;
    break;
  }
  if (xfer)
  {
    if (xfer > MAX_SECTOR*512){
      return 1;			/* bad command */
	}
    else
    {
      seg = __tb >> 4;
      ofs = __tb & 15;
    }
  }
  r.h.ah = cmd;
  r.h.al = nsects;
  r.x.es = seg;
  r.x.bx = ofs;
  r.h.ch = track & 0xff;
  r.h.cl = sector | ((track >> 2) & 0xc0);
  r.h.dh = head;
  r.h.dl = drive;

  if (xfer && before)
		real_fill((char *)buffer, xfer);

  realint(0x13, &r);

  if (xfer && !before)
		real_read((char *)buffer, xfer);

  if (cmd == 0x08)
  {
    ((short *)buffer)[0] = r.x.cx;
    ((short *)buffer)[1] = r.x.dx;
  }
  return r.h.ah;
}

unsigned 
_bios_disk(unsigned _cmd, struct diskinfo_t *_di)
{
  int seg=0, ofs=0, xfer=0, before=0;
  vm86regs_t r;
  u32_t __tb;
  int sz;

  real_address(&__tb, &sz);

  switch( _cmd )
  {
  case _DISK_READ:
    xfer = 512 * _di->nsectors;
    before = 0;
    break;
  case _DISK_WRITE:
    xfer = 512 * _di->nsectors;
    before = 1;
    break;
  case _DISK_FORMAT:
    xfer = 2 * 256;
    before = 1;
    break;
  }
  if (xfer)
  {
    if (xfer > MAX_SECTOR*512){
      return 1;			/* bad command */
	}
    else
    {
      seg = __tb >> 4;
      ofs = __tb & 15;
    }
  }

  r.h.ah = _cmd;
  r.h.al = _di->nsectors;
  r.x.es = seg;
  r.x.bx = ofs;
  r.h.ch = _di->track & 0xff;
  r.h.cl = _di->sector | ((_di->track >> 2) & 0xc0);
  r.h.dh = _di->head;
  r.h.dl = _di->drive;

  if (xfer && before)
		real_fill((char *)_di->buffer, xfer);

  realint(0x13, &r);
  if (xfer && !before)
		real_read((char *)_di->buffer, xfer);
  return r.x.ax;
}
