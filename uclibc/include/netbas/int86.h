#ifndef vm86_H
#define vm86_H
#ifdef __cplusplus
extern "C" {
#endif
typedef union REGS{
  struct {
    unsigned long edi;
    unsigned long esi;
    unsigned long ebp;
    unsigned long res;
    unsigned long ebx;
    unsigned long edx;
    unsigned long ecx;
    unsigned long eax;
  } d;
  struct {
    unsigned short di, di_hi;
    unsigned short si, si_hi;
    unsigned short bp, bp_hi;
    unsigned short res, res_hi;
    unsigned short bx, bx_hi;
    unsigned short dx, dx_hi;
    unsigned short cx, cx_hi;
    unsigned short ax, ax_hi;
    unsigned short flags;
    unsigned short es;
    unsigned short ds;
    unsigned short fs;
    unsigned short gs;
    unsigned short ip;
    unsigned short cs;
    unsigned short sp;
    unsigned short ss;
  } x;
  struct {
    unsigned char edi[4];
    unsigned char esi[4];
    unsigned char ebp[4];
    unsigned char res[4];
    unsigned char bl, bh, ebx_b2, ebx_b3;
    unsigned char dl, dh, edx_b2, edx_b3;
    unsigned char cl, ch, ecx_b2, ecx_b3;
    unsigned char al, ah, eax_b2, eax_b3;
  } h;
} vm86regs_t;

#define __dpmi_regs vm86regs_t
#define __dpmi_int  realint
#define	_dos_ds USER_GLOBAL_DATA

typedef struct VESA_INFO {
	 unsigned char VESASignature[4] __attribute__ ((packed));
	 unsigned short VESAVersion __attribute__ ((packed));
	 unsigned long OEMStringPtr __attribute__ ((packed));
	 unsigned char Capabilities[4] __attribute__ ((packed));
	 unsigned long VideoModePtr __attribute__ ((packed));
	 unsigned short TotalMemory __attribute__ ((packed));
	 unsigned short OemSoftwareRev __attribute__ ((packed));
	 unsigned long OemVendorNamePtr __attribute__ ((packed));
	 unsigned long OemProductNamePtr __attribute__ ((packed));
	 unsigned long OemProductRevPtr __attribute__ ((packed));
	 unsigned char Reserved[222] __attribute__ ((packed));
	 unsigned char OemData[256] __attribute__ ((packed));
} VESA_INFO;

typedef struct MODE_INFO {
	 unsigned short ModeAttributes __attribute__ ((packed));
	 unsigned char WinAAttributes __attribute__ ((packed));
	 unsigned char WinBAttributes __attribute__ ((packed));
	 unsigned short WinGranularity __attribute__ ((packed));
	 unsigned short WinSize __attribute__ ((packed));
	 unsigned short WinASegment __attribute__ ((packed));
	 unsigned short WinBSegment __attribute__ ((packed));
	 unsigned long WinFuncPtr __attribute__ ((packed));
	 unsigned short BytesPerScanLine __attribute__ ((packed));

	 unsigned short XResolution __attribute__ ((packed));
	 unsigned short YResolution __attribute__ ((packed));
	 unsigned char XCharSize __attribute__ ((packed));
	 unsigned char YCharSize __attribute__ ((packed));
	 unsigned char NumberOfPlanes __attribute__ ((packed));
	 unsigned char BitsPerPixel __attribute__ ((packed));

	 unsigned char NumberOfBanks __attribute__ ((packed));
	 unsigned char MemoryModel __attribute__ ((packed));
	 unsigned char BankSize __attribute__ ((packed));
	 unsigned char NumberOfImagePages __attribute__ ((packed));
	 unsigned char Reserved_page __attribute__ ((packed));
	 unsigned char RedMaskSize __attribute__ ((packed));
	 unsigned char RedMaskPos __attribute__ ((packed));
	 unsigned char GreenMaskSize __attribute__ ((packed));
	 unsigned char GreenMaskPos __attribute__ ((packed));
	 unsigned char BlueMaskSize __attribute__ ((packed));
	 unsigned char BlueMaskPos __attribute__ ((packed));
	 unsigned char ReservedMaskSize __attribute__ ((packed));
	 unsigned char ReservedMaskPos __attribute__ ((packed));
	 unsigned char DirectColorModeInfo __attribute__ ((packed));
	 unsigned long PhysBasePtr __attribute__ ((packed));
	 unsigned long OffScreenMemOffset __attribute__ ((packed));
	 unsigned short OffScreenMemSize __attribute__ ((packed));
	 unsigned char Reserved[206] __attribute__ ((packed));
} MODE_INFO;

#define FP_OFF(x)      ((unsigned long)(x) & 0x000F)
#define FP_SEG(x)      (((unsigned long)(x) & 0xFFFF0) >> 4)

#define DOS_DS 48
struct msdos_super 
{
	signed char	jmp_boot[3];	// Boot strap short or near jump 
	signed char	oem[8];	// Name - can be used to special casepartition manager volumes 
	unsigned char	sector_size[2];	// u8_ts per logical sector 
	unsigned char	cluster_size;	// sectors/cluster 
	unsigned short	reserved;	// reserved sectors 
	unsigned char	fats;		// number of FATs 
	unsigned char	dir_entries[2];	// root directory entries 
	unsigned char	sectors[2];	// number of sectors 
	unsigned char	media_descriptor;		// media code (unused) 
	unsigned short	fat16_length;	// sectors/FAT 
	unsigned short	sec_per_track;	// sectors per track 
	unsigned short	heads;		// number of heads 
	unsigned long	hidden;		// hidden sectors (unused) 
	unsigned long	total_sectors;	// number of sectors (if sectors == 0) 
    union
    {
	struct fat_1x
	{
	    unsigned char drive_number;
	    unsigned char reserved;
	    unsigned char boot_signature;
	    unsigned long volume_id;
	    unsigned char volume_label[ 11 ];
	    char fstype[ 8 ];
	} fat1x;
	struct fat_32
	{
	    unsigned long fat_size;
	    unsigned short reserved:8;
	    unsigned short mirroring:1;
	    unsigned short reserved2:3;
	    unsigned short active_fat:4;
	    unsigned short filesystem_version;
	    unsigned long fat32_root_cluster;
	    unsigned short filesystem_info;
	    unsigned short backup_boot_record;
	    unsigned char reserved3[ 12 ];
	    unsigned char drive_number;
	    unsigned char reserved4;
	    unsigned char boot_signature;
	    unsigned long volume_id;
	    char volume_label[ 11 ];
	    char filesyste_type[ 8 ];
	} fat32;
    } type;
};

struct disk_pos
{
    int head, track, sector;
};

/*int real_address(unsigned long *addr, int *sz );
int real_fill(char *buf, int sz);
int real_read(char *buf, int sz);*/
void dosmemput(const void *_buffer, size_t _length, unsigned long _offset);
void dosmemget(unsigned long _offset, size_t _length, void *_buffer);

enum text_modes { LASTMODE=-1, BW40=0, C40, BW80, C80, MONO=7, C4350=64 };


/* These lengths are in bytes, optimized for speed */
void dosmemget(unsigned long _offset, size_t _length, void *_buffer);
void dosmemput(const void *_buffer, size_t _length, unsigned long _offset);

 int vesa_mode_match(MODE_INFO * ret, int w, int h, int c);
int vbe_setmode(int mode);
int get_mode_info(int mode, MODE_INFO * mode_info);
int get_vbe_info(VESA_INFO *info);
void text_mode();
void SDL_vesa_stop(void);

void JICAMA_mouse_setup(int a,int b);



#ifdef __cplusplus
}
#endif
#endif
