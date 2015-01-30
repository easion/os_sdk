
#define JICAMA
#include <stdio.h>
#include <string.h>
#include <sys/farptr.h>
#include <int86.h>
#include <bios.h>
#include <errno.h>
#include "diskio.h"

/* these assume little endian CPU like x86 */
#define	LE16(X)		*(unsigned short *)(X)
#define	LE32(X)		*(unsigned long *)(X)

/* IMPORTS
from _16BIT.C, DJGPP, or ??? */
int lba_biosdisk(int cmd, int drive, unsigned long lba, int nsects, void *buf);
int get_hd_geometry(disk_t *disk);

static char *d_name();

/* These lengths are in bytes, optimized for speed */
void dosmemget(unsigned long _offset, size_t _length, void *_buffer)
{
	int c;
	char *ptr=_buffer;

	 for (c = 0; c < _length; c++)
		 ptr[c] =_farpeekb(USER_GLOBAL_DATA, _offset+c);
}

void dosmemput(const void *_buffer, size_t _length, unsigned long _offset)
{
	int c;
	char *ptr=_buffer;

	 for (c = 0; c < _length; c++)
		  _farpokeb(USER_GLOBAL_DATA, _offset+c,  ptr[c]);
}


int set_attrib(char *fnmae)
{
	int a, sz;
	vm86regs_t inregs;

	real_address(&a, &sz);

	inregs.h.ah=0x43;
	inregs.h.al=0;
	inregs.x.di = FP_OFF(a);
	inregs.x.es = FP_SEG(a);

	real_fill((char *)fnmae, strlen(fnmae));
	realint(0x21,&inregs);
	printf("File attribute:%x\n",inregs.x.cx);
	return( ( inregs.x.flags & 0x01 ) ? -1 : 0 );
}

int dos_mkdir(char *fnmae)
{
	int a, sz;
    vm86regs_t inregs;

   real_address(&a, &sz);

		inregs.x.ax=0x3900;
	  inregs.x.di = FP_OFF(a);
	  inregs.x.es = FP_SEG(a);

	real_fill((char *)fnmae, strlen(fnmae)+1);
	realint(0x21,&inregs);
	return( ( inregs.x.flags & 0x01 ) ? -1 : 0 );
}

int dos_mkfile(char *fnmae)
{
	int a, sz;
	vm86regs_t inregs;

	real_address(&a, &sz);

	inregs.x.ax=0x3c00;
	inregs.x.di = FP_OFF(a);
	inregs.x.es = FP_SEG(a);

	real_fill((char *)fnmae, strlen(fnmae));
	realint(0x21,&inregs);
	return( ( inregs.x.flags & 0x01 ) ? -1 : 0 );
}

/*code from minix*/
void dosclose(handle)
int handle;				/* file handle */
{
    vm86regs_t reg86;

/* Close a DOS file. */
  reg86.h.ah = 0x3E;	/* CLOSE */
  reg86.x.bx = handle;

	realint( 0x21, &reg86 );
}

int check_dos30()
{
    vm86regs_t reg86;

	printf("check_dos30\n");
	/* Check if DOS 3.0 or better present. */
	reg86.x.ax = 0x3000;	/* GET DOS VERSION */
	realint( 0x21, &reg86 );

	if (reg86.h.al < 3) {
		printf("%s: No DOS 3.0+ running(Ver:%d.%d)\n", d_name(), reg86.h.al, reg86.h.ah);
		return(EIO);
	}
	return 0;
}

char *doserror(err)
unsigned err;
{
/* Translate some DOS error codes to text. */
  static struct errlist {
	int	err;
	char	*what;
  } errlist[] = {
	{  0, "No error" },
	{  1, "Function number invalid" },
	{  2, "File not found" },
	{  3, "Path not found" },
	{  4, "Too many open files" },
	{  5, "Access denied" },
	{  6, "Invalid handle" },
	{ 12, "Access code invalid" },
  };
  struct errlist *ep;
  static char unknown[]= "Error 65535";
  char *p;

  for (ep = errlist; ep < errlist + sizeof(errlist)/sizeof(errlist[0]); ep++) {
	if (ep->err == err) return ep->what;
  }
  p = unknown + sizeof(unknown) - 1;
  do *--p = '0' + (err % 10); while ((err /= 10) > 0);
  strcpy(unknown + 6, p);
  return unknown;
}


static int d_drive=0;

static char *d_name()
{
/* Return a name for the current device. */
  static char name[] = "dosfile-d0";

  name[9] = '0' + d_drive;
  return name;
}

void dos_getdrive(unsigned *drive)
{
	vm86regs_t regs;

	regs.x.ax = 0x1900; /* AH=19h */
	realint(0x21, &regs);
	*drive = (regs.x.ax & 0xFF) + 1;
}


int read_sector(disk_t *disk, unsigned long lba, unsigned char *buf)
{
	struct diskinfo_t cmd;
	unsigned tries, err;

	lba += disk->partition_start;
	cmd.drive = disk->drive_num;
/* use LBA if available */
	if(disk->use_lba)
	{
		return lba_biosdisk(_DISK_READ,
			disk->drive_num, lba, 1, buf);
	}
/* use CHS _bios_disk() */
	cmd.sector = (unsigned)(lba % disk->sectors + 1);
	cmd.head = (unsigned)((lba / disk->sectors) % disk->heads);
	cmd.track = (unsigned)((lba / disk->sectors) / disk->heads);
	cmd.nsectors = 1;
	cmd.buffer = buf;
/* make 3 attempts */
	for(tries = 3; tries != 0; tries--)
	{
		err = _bios_disk(_DISK_READ, &cmd);
		err >>= 8;
/* 0x11=="CRC/ECC corrected data error" */
		if(err == 0 || err == 0x11)
			return 0;
/* reset disk */
		_bios_disk(_DISK_RESET, &cmd);
	}
	DEBUG(printf("read_sector(): error 0x%02X\n", err);)
	return err;
}
/*****************************************************************************
*****************************************************************************/
int write_sector(disk_t *disk, unsigned long lba, unsigned char *buf)
{
	struct diskinfo_t cmd;
	unsigned tries, err;

	lba += disk->partition_start;
	cmd.drive = disk->drive_num;
/* use LBA if available */
	if(disk->use_lba)
	{
		return lba_biosdisk(_DISK_WRITE,
			disk->drive_num, lba, 1, buf);
	}
/* use CHS _bios_disk() */
	cmd.sector = (unsigned)(lba % disk->sectors + 1);
	cmd.head = (unsigned)((lba / disk->sectors) % disk->heads);
	cmd.track = (unsigned)((lba / disk->sectors) / disk->heads);
	cmd.nsectors = 1;
	cmd.buffer = buf;
/* make 3 attempts */
	for(tries = 3; tries != 0; tries--)
	{
		err = _bios_disk(_DISK_WRITE, &cmd);
		err >>= 8;
/* 0x11=="CRC/ECC corrected data error" */
		if(err == 0 || err == 0x11)
			return 0;
/* reset disk */
		_bios_disk(_DISK_RESET, &cmd);
	}
	DEBUG(printf("write_sector(): error 0x%02X\n", err);)
	return err;
}
/*****************************************************************************
*****************************************************************************/
int is_fat_bootsector(unsigned char *buf)
{
	int temp, ok = 1;

	DEBUG(printf("check_if_fat_bootsector:\n");)
/* must start with 16-bit JMP or 8-bit JMP plus NOP */
	if(buf[0] == 0xE9)
		/* OK */;
	else if(buf[0] == 0xEB && buf[2] == 0x90)
		/* OK */;
	else
	{
		DEBUG(printf("\tMissing JMP/NOP\n");)
		ok = 0;
	}
	temp = buf[13];
	if(temp == 0 || ((temp - 1) & temp) != 0)
	{
		DEBUG(printf("\tSectors per cluster (%u) "
			"is not a power of 2\n", temp);)
		ok = 0;
	}
	temp = buf[16];
	temp = LE16(buf + 24);
	if(temp == 0 || temp > 63)
	{
		DEBUG(printf("\tInvalid number of sectors (%u)\n", temp);)
		ok = 0;
	}
	temp = LE16(buf + 26);
	if(temp == 0 || temp > 255)
	{
		DEBUG(printf("\tInvalid number of heads (%u)\n", temp);)
		ok = 0;
	}
	return ok;
}
/*****************************************************************************
*****************************************************************************/
