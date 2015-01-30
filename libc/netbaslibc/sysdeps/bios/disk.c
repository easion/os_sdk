#define JICAMA
#include <stdio.h>
#include <string.h>
#include <sys/farptr.h>
#include <int86.h>
#include <bios.h>
#include <errno.h>
#include "diskio.h"

#define _DISK_RESET     0   /* controller hard reset */
#define _DISK_STATUS    1   /* status of last operation */
#define _DISK_READ      2   /* read sectors */
#define _DISK_WRITE     3   /* write sectors */
#define _DISK_VERIFY    4   /* verify sectors */
#define _DISK_FORMAT    5   /* format track */

struct disk_info_t
{
	unsigned drive, head, track, sector, nsectors;
	void *buffer;
};

struct wini {		/* main drive struct, one entry per drive */
  unsigned cylinders;		/* number of cylinders */
  unsigned heads;		/* number of heads */
  unsigned sectors;		/* number of sectors per track */
  unsigned open_ct;		/* in-use count */
  int int13ext;			/* IBM/MS INT 13 extensions supported? */
  //struct device part[DEV_PER_DRIVE];	/* disks and partitions */
  //struct device subpart[SUB_PER_DRIVE]; /* subpartitions */
} ;



static struct wini winidrv;
static int w_drive=0;			/* selected drive */
char *w_name()
{
/* Return a name for the current device. */
  static char name[] = "bios-d0";

  name[6] = '0' + w_drive;
  return name;
}

int disk_ext_install_check(int drive)
{
	int nr_drives;
	struct wini *wn=&winidrv;
  unsigned long capacity;
	u32_t a=0;
   int sz;
    vm86regs_t reg86;

  static struct int13ext_params {
	u16_t	len;
	u16_t	flags;
	u32_t	cylinders;
	u32_t	heads;
	u32_t	sectors;
	u32_t	capacity[2];
	u16_t	bts_per_sec;
	u16_t	config[2];
  } i13e_par;

   real_address(&a, &sz);

	reg86.h.ah = 0x08;	/* Get drive parameters. */
	reg86.h.dl = 0x80 + drive;
	realint( 0x13, &reg86 );
	nr_drives = !(reg86.x.flags & 0x0001) ? reg86.h.dl : drive;

	wn->heads = reg86.h.dh + 1;
	wn->sectors = reg86.h.cl & 0x3F;
	wn->cylinders = (reg86.h.ch | ((reg86.h.cl & 0xC0) << 2)) + 1;
	capacity = (unsigned long) wn->cylinders * wn->heads * wn->sectors;

	reg86.h.ah = 0x41;	/* INT 13 Extensions - Installation check */
	reg86.x.bx = 0x55AA;
	reg86.h.dl =  drive;
	realint( 0x13, &reg86 );

	if (!(reg86.x.flags & 0x0001) && reg86.x.bx == 0xAA55
				&& (reg86.x.cx & 0x0001)){
		/* INT 13 Extensions available. */
		reg86.h.ah = 0x48;	/* Ext. Get drive parameters. */
		reg86.h.dl = 0x80 + drive;

	  reg86.x.di = FP_OFF(a);
	  reg86.x.es = FP_SEG(a);
		i13e_par.len = 0x001E;	/* Input size of parameter packet */
		real_fill((char *)&i13e_par, sizeof(struct int13ext_params));

		realint( 0x13, &reg86 );
		real_read((char *)&i13e_par, sizeof(struct int13ext_params));

		if (!(reg86.x.flags & 0x0001)) {
			wn->int13ext = 1;	/* Extensions can be used. */
			capacity = i13e_par.capacity[0];
			if (i13e_par.capacity[1] != 0) capacity = 0xFFFFFFFF;
		}
	}

	if (wn->int13ext) {
		printf("%s: %lu sectors\n", w_name(), capacity);
		return 1;
	} else {
		printf("%s: %d cylinders, %d heads, %d sectors per track\n",
			w_name(), wn->cylinders, wn->heads, wn->sectors);
	}

	return 0;
}

static void fp1440_block2hts(unsigned long block, struct disk_pos *d)
{
    d->head = ( block % ( 18 * 2 ) ) /	18;
    d->track = block / ( 18 * 2 );
    d->sector = block % 18 + 1;
    //printk("Head: %d, Track: %d, Sector: %d\n", *head, *track, *sector );
}



int disk_op(int w_drive, struct disk_pos *d, int opcode, char *buf)
{
	u32_t a=0;
   int sz;
   vm86regs_t reg86;

   real_address(&a, &sz);

		reg86.h.ah = opcode == 1 ? 0x03 : 0x02;
		reg86.h.al = 512 >> SECTOR_SHIFT;
		reg86.h.ch = d->track & 0xFF;
		reg86.h.cl = d->sector | ((d->track & 0x300) >> 2);
		reg86.h.dh = d->head;
		reg86.h.dl = 0x80 + w_drive;

     reg86.x.bx = FP_OFF(a);
	 reg86.x.es = FP_SEG(a);

	realint( 0x13, &reg86 );
	real_read((char *)buf, 512);

	return 0;
}


int floppy_read_sector(int sec, char *buf)
{
	struct disk_pos d;
    fp1440_block2hts( sec, &d );
    disk_op(0, &d, 0,  buf);
	return 0;
}




unsigned _bios_diskx(unsigned cmd, struct disk_info_t *info)
{
	union REGS regs;

/* biosdisk() returns the 8-bit error code left in register AH by
the call to INT 13h. It does NOT return a combined, 16-bit error
code + number of sectors transferred, as described in the online help.

	return biosdisk(cmd, info->drive, info->head, info->track,
		info->sector, info->nsectors, info->buffer);
*/
	regs.h.ah = cmd;
	regs.h.al = info->nsectors;
	regs.x.bx = FP_OFF(info->buffer);
	regs.h.ch = info->track;
	regs.h.cl = (info->track / 256) * 64 + (info->sector & 0x3F);
	regs.h.dh = info->head;
	regs.h.dl = info->drive;
	regs.x.es = FP_SEG(info->buffer);
	realint(0x13, &regs);
	return regs.x.ax;
}

/*
biosdisk()调用BIOS磁盘驱动程序函数
原形:char biosdisk(int cmd,int drive,int head,int track,int sector,int nsects,void *buffer)
功能：使用中断0x13，直接调用BIOS进行磁盘操作
参数：(1)cmd:
　　　　2-数据以每扇区512字节的格式读入buffer，起始扇区由head、track和sector定，扇区数由nsects定。
　　　　3-将buffer中的数据按每扇区512字节写入磁盘。
　　　　4-对扇区进行数据校验。
　　　　6-格式化一个磁盘并对化扇区设置化标志。
　　　　8-返回当前驱动器参数在buffer的前4个字节中。
　　　　10-长读，每扇区读入512字节加上额外的4个字节。
　　　　11-长写，每扇区写入512字节加上额外的4个字节。
　　　(2)drive:0-第一个软驱；1-第二个软驱；0x80-第一个硬驱
　　　(3)head:磁头
　　　(4)track:磁道
　　　(5)sector:扇区
　　　(6)nsects:扇区数
　　　(7)buffer:数据缓冲区，定义为unsigned char buffer[];
返回值：0x00-操作成功
　　　　0x01-错误命令
　　　　0x03-企图写具有写保护的磁盘
　　　　0x07-驱动器参数设置错误
　　　　0x10-磁盘读/CRC/ECC错误
头文件：bios.h
注：对于硬盘主引导记录扇区head=0,track=0,sector=1
  static struct int13ext_params {
	u16_t	len;
	u16_t	flags;
	u32_t	cylinders;
	u32_t	heads;
	u32_t	sectors;
	u32_t	capacity[2];
	u16_t	bts_per_sec;
	u16_t	config[2];
  } i13e_par;
*/
 #ifdef disk_f
static void demo7(void)
{
	unsigned i, j;
	uregs_t regs;

	printf("Demo 7: INT 13h AH=02h floppy disk read\n");
#if 1
/* enable IRQ 6 (floppy) interrupt -- this works for me */
	outportb(0x21, ~0x40);
#else
/* enable IRQ 6 (floppy) and IRQ 0 (timer) interrupts */
	outportb(0x21, ~0x41);
#endif
	regs.ecx = 0x0001; /* cylinder 0, sector 1 */
	regs.edx = 0x0000; /* head 0, drive 0 */
/* this loads sector 0 of the floppy to 9000:0000
xxx - allocate proper conventional memory buffer here
(maybe this is why the 486 system hangs?) */
	regs.ebx = 0;
	regs.v_es = 0x9000;
	regs.eflags |= 0x200;	/* enable interrupts */
/* make 3 attempts */
	for(i = 2; /*i != 0*/; i--)
	{
		regs.eax = 0x0201; /* read; 1 sector */
		do_v86_int(&regs, 0x13);
		j = (regs.eax >> 8) & 0xFF;
		if(j == 0 || i == 0)
			break;
		regs.eax = 0x0000; /* AH=0: reset drive */
		do_v86_int(&regs, 0x13);
	}
/* if success, dump buffer, else display INT 13h error number */
	if(j == 0)
	{
		printf("\tDump of floppy bootsector:\n");
		dump((char *)(0x90000L), 64);
	}
	else
		printf("\t*** Error 0x%02X from INT 13h ***\n", j);
}

#endif



static void probe_floppy_geometry(disk_t *disk)
{
	unsigned sectors, heads;
	unsigned char buf[BPS];

/* scan upwards for sector number where read fails */
	disk->sectors = 64 + 1;
	for(sectors = 1; sectors <= 64; sectors++)
	{
		if(read_sector(disk, sectors - 1, buf) != 0)
			break;
	}
	disk->sectors = sectors - 1;
#if 1
disk->heads = 2;
#else
/* scan upwards for head number where read fails
xxx - this probing for number of heads doesn't work */
	disk->heads = 16 + 1;
	for(heads = 1; heads < 16; heads++)
	{
		if(read_sector(disk, heads * disk->sectors, buf) != 0)
			break;
	}
	disk->heads = heads;
#endif
/* reset drive by reading sector 0 */
	(void)read_sector(disk, 0, buf);
	DEBUG(printf("probe_floppy_geometry() for fd 0x%02X: "
		"CHS=?:%u:%u\n", disk->drive_num,
		disk->heads, disk->sectors);)
}


/*****************************************************************************
*****************************************************************************/
int open_disk(disk_t *disk, unsigned drive_num)
{
	unsigned char buf[BPS];
	unsigned num_fds;
	int err;

	disk->drive_num = drive_num;
	disk->partition_start = 0; /* assume floppy */
	disk->use_lba = 0;	/* assume CHS */
/* hard disk */
	if(disk->drive_num >= 0x80)
		return get_hd_geometry(disk);
/* make sure floppy drive exists */
	num_fds = peekw(0x40, 0x10);
	if(num_fds & 0x0001)
		num_fds = ((num_fds / 64) & 3) + 1;
	else
		num_fds = 0;
	if(disk->drive_num >= num_fds)
	{
		printf("open_disk(): fd 0x%02X does not exist\n",
			disk->drive_num);
		return -1;
	}
/* temporary values to make read_sector(0) work */
	disk->heads = disk->sectors = 1;
	err = read_sector(disk, 0, buf);
	if(err != 0)
		return err;
/* if it's a FAT (DOS) disk, we get can reliable geometry info
from the BIOS parameter block (BPB) in the bootsector */
	if(is_fat_bootsector(buf))
	{
		disk->heads =0;// LE16(buf + 26);
		disk->sectors =0;// LE16(buf + 24);
		DEBUG(printf("open_disk() for fd 0x%02X: "
			"CHS=?:%u:%u (from BPB)\n",
			disk->drive_num,
			disk->heads, disk->sectors);)
		return 0;
	}
#if 1
/* ...otherwise, do slow probe */
	probe_floppy_geometry(disk);
#else
/* ...or just assume some values */
	disk->heads = 2;
	disk->sectors = 18;
	DEBUG(printf("open_disk() for fd 0x%02X: "
		"assuming CHS=?:2:18\n", disk->drive_num);)
#endif
	return 0;
}


