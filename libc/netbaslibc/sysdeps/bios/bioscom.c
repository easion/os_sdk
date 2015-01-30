/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define JICAMA
#include <stdio.h>
#include <int86.h>
#include <bios.h>

int bioscom(int cmd, char data, int port)
{
  vm86regs_t r;
  r.h.ah = cmd;
  r.h.al = data;
  r.x.dx = port;
  realint(0x14, &r);
  return r.x.ax;
}


long	GetMouseButtons()
{
    vm86regs_t	rm;

    //memset( &rm, 0, sizeof( vm86regs_t ) );

    rm.x.ax	= 0x0003;
    realint( 0x33, &rm );

    return( rm.x.bx & 0x07 );
}

long	ReadMouseTicks()
{
    vm86regs_t	rm;

    //memset( &rm, 0, sizeof( vm86regs_t ) );

    rm.x.ax	= 0x000B;
    realint( 0x33, &rm );

    return( (rm.x.cx << 16) | (rm.x.dx & 0xffff) );
}

int rmmouse_init()
{
    vm86regs_t rm;

	//memset( &rm, 0, sizeof(vm86regs_t) );

	rm.x.ax	= 0x00;
	rm.x.bx	= 0x00;
	rm.x.cx	= 3;

	realint( 0x33, &rm );
    return( rm.x.ax & 0xFFFF );
}


#if 0
/* Check bootable CD-ROM emulation status.  */
static int
get_cdinfo (int drive, struct geometry *geometry)
{
  int err;
  struct iso_spec_packet
  {
    unsigned char size;
    unsigned char media_type;
    unsigned char drive_no;
    unsigned char controller_no;
    unsigned long image_lba;
    unsigned short device_spec;
    unsigned short cache_seg;
    unsigned short load_seg;
    unsigned short length_sec512;
    unsigned char cylinders;
    unsigned char sectors;
    unsigned char heads;
    
    unsigned char dummy[16];
  } __attribute__ ((packed)) cdrp;
  
  grub_memset (&cdrp, 0, sizeof (cdrp));
  cdrp.size = sizeof (cdrp) - sizeof (cdrp.dummy);
  err = biosdisk_int13_extensions (0x4B01, drive, &cdrp);

  if (! err && cdrp.drive_no == drive)
    {
      if ((cdrp.media_type & 0x0F) == 0)
        {
          /* No emulation bootable CD-ROM */
          geometry->flags = BIOSDISK_FLAG_LBA_EXTENSION | BIOSDISK_FLAG_CDROM;
          geometry->cylinders = 0;
          geometry->heads = 1;
          geometry->sectors = 15;
          geometry->sector_size = 2048;
          geometry->total_sectors = MAXINT;
          return 1;
        }
      else
        {
	  /* Floppy or hard-disk emulation */
          geometry->cylinders
	    = ((unsigned int) cdrp.cylinders
	       + (((unsigned int) (cdrp.sectors & 0xC0)) << 2));
          geometry->heads = cdrp.heads;
          geometry->sectors = cdrp.sectors & 0x3F;
          geometry->sector_size = SECTOR_SIZE;
          geometry->total_sectors = (geometry->cylinders
				     * geometry->heads
				     * geometry->sectors);
          return -1;
        }
    }
  return 0;
}
#endif

