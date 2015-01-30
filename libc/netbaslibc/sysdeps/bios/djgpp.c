/*****************************************************************************
Sector-level disk I/O code for DOS, using DJGPP.
This code is public domain (no copyright).
You can do whatever you want with it.

EXPORTS:
int lba_biosdisk(int cmd, int drive, unsigned long lba,
		int nsects, void *buf);
int get_hd_geometry(disk_t *disk);
*****************************************************************************/
#define JICAMA
#include <string.h> /* memset() */
#include <stdio.h> /* printf() */
#include <bios.h> /* _DISK_... */
#include <int86.h> /* __dpmi_regs, __dpmi_int() */
#include <sys/movedata.h> /* dosmemget(), dosmemput() */
#include "diskio.h"
#include "dos.h" /* peekb() */

#define BIOSDISKBUFSZ 4096
#define __tb 0x9000
/*****************************************************************************
*****************************************************************************/
int lba_biosdisk(int cmd, int drive, unsigned long lba, int nsects, void *buf)
{
	struct
	{
		unsigned char pkt_len	__attribute__((packed));
		unsigned char res0	__attribute__((packed));
		unsigned char nsects	__attribute__((packed));
		unsigned char res1	__attribute__((packed));
		unsigned short buf_off	__attribute__((packed));
		unsigned short buf_seg	__attribute__((packed));
		unsigned long lba31_0	__attribute__((packed));
		unsigned long lba63_32	__attribute__((packed));
	} lba_cmd_pkt;
	unsigned tries, err = 0;
	__dpmi_regs regs;

	if(cmd != _DISK_READ && cmd != _DISK_WRITE)
		return 0x100;
/* make sure the DJGPP transfer buffer (in conventional memory)
is big enough */
	if(BPS * nsects + sizeof(lba_cmd_pkt) >
		BIOSDISKBUFSZ)
			return 0x100;
/* make sure drive and BIOS support LBA */
	regs.x.bx = 0x55AA;
	regs.h.dl = drive;
	regs.h.ah = 0x41;
	__dpmi_int(0x13, &regs);
	if(regs.x.flags & 0x0001) /* carry bit (CY) is set */
		return 0x100;
/* fill out the INT 13h AH=4xh command packet */
	memset(&lba_cmd_pkt, 0, sizeof(lba_cmd_pkt));
	lba_cmd_pkt.pkt_len = sizeof(lba_cmd_pkt);
	lba_cmd_pkt.nsects = nsects;
/* use start of transfer buffer for data transferred by BIOS disk I/O... */
	lba_cmd_pkt.buf_off = 0;
	lba_cmd_pkt.buf_seg = __tb >> 4;
	lba_cmd_pkt.lba31_0 = lba;
/* ...use end of transfer buffer for the command packet itself */
	dosmemput(&lba_cmd_pkt, sizeof(lba_cmd_pkt),
		__tb + BPS * nsects);
/* fill out registers for INT 13h AH=4xh */
	regs.x.ds = (__tb + BPS * nsects) >> 4;
	regs.x.si = (__tb + BPS * nsects) & 0x0F;
	regs.h.dl = drive;
/* if writing, store the data */
	if(cmd == _DISK_WRITE)
		dosmemput(buf, BPS * nsects, __tb);
/* make 3 attempts */
	for(tries = 3; tries != 0; tries--)
	{
		regs.h.ah = (cmd == _DISK_READ) ? 0x42 : 0x43;
		__dpmi_int(0x13, &regs);
		err = regs.h.ah;
		if((regs.x.flags & 0x0001) == 0)
		{
/* if reading, load the data */
			if(cmd == _DISK_READ)
				dosmemget(__tb, BPS * nsects, buf);
			return 0;
		}
/* reset disk */
		regs.h.ah = _DISK_RESET;
		__dpmi_int(0x13, &regs);
	}
	DEBUG(printf("lba_biosdisk(): error 0x%02X\n", err);)
	return err;
}
/*****************************************************************************
*****************************************************************************/
int get_hd_geometry(disk_t *disk)
{
	__dpmi_regs regs;

/* make sure hard drive exists */
	if(disk->drive_num - 0x80 >= peekb(0x40, 0x75))
	{
		printf("get_hd_geometry(): hd 0x%02X does not exist\n",
			disk->drive_num);
		return -1;
	}
/* use LBA if drive and BIOS support it */
	regs.h.ah = 0x41;
	regs.x.bx = 0x55AA;
	regs.h.dl = disk->drive_num;
	__dpmi_int(0x13, &regs);
	if((regs.x.flags & 0x0001) == 0 && regs.x.bx == 0xAA55)
	{
		disk->use_lba = 1;
		DEBUG(printf("get_hd_geometry(): using LBA for hd 0x%02X\n",
			disk->drive_num);)
		return 0;
	}
/* get geometry from BIOS */
	regs.h.ah = 0x08;
	regs.h.dl = disk->drive_num;
	__dpmi_int(0x13, &regs);
	if(regs.x.flags & 0x0001)
	{
		printf("get_hd_geometry(): error getting geometry "
			"for hard drive 0x%02X\n", disk->drive_num);
		return -1;
	}
	disk->heads = regs.h.dh + 1;
	disk->sectors = regs.h.cl & 0x3F;
	DEBUG(printf("get_hd_geometry() for hd 0x%02X: "
		"CHS=?:%u:%u (from INT 13h AH=08h)\n",
		disk->drive_num,
		disk->heads, disk->sectors);)
	return 0;
}
