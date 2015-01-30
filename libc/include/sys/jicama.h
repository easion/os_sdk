#ifndef _SYS_JICAMA_H
#define _SYS_JICAMA_H

#ifdef JICAMA

#define USER_GLOBAL_CODE 0X1b
#define USER_GLOBAL_DATA 0X23
#define DOS_DATA 0X30
#define VIDEO_DATA_SEG 0X3B
#define HZ 100
#define EXEC_PAGESIZE 4096

#define SUID		0	/* Max number of groups per user */
#define NGROUPS		32	/* Max number of groups per user */
#define NOGROUP		-1

#define MAXHOSTNAMELEN 8

typedef unsigned char   u8_t;  //×Ö½Ú
typedef unsigned short u16_t;  //×Ö
typedef unsigned long  u32_t;  //Ë«×Ö
typedef unsigned long long int u64_t;
/* Useful basic types and constants */
typedef signed   char      CHAR;
typedef signed   short     SHORT;
typedef signed   long      LONG;
typedef signed   long long LONGLONG;
typedef LONGLONG           INT64;

typedef unsigned char      BYTE;
typedef unsigned short     WORD;
typedef unsigned long      DWORD;
typedef unsigned long long QWORD;
typedef QWORD              DWORDLONG;

/* Structure to hold boot parameters. */
struct bparam_s
{
  unsigned short bp_rootdev;
  unsigned short bp_bootdev;
  unsigned bp_ramsize;
  unsigned short bp_processor;
  unsigned char bp_kernel[64];
  unsigned short bp_fs_type;
  /*video info*/
    unsigned int lfb_width;
    unsigned int lfb_height;
    unsigned int lfb_bpp;
    unsigned long lfb_ptr;
	unsigned long logo_start;
	unsigned int logo_size;
	unsigned long font_start;
	unsigned int font_size;
};

#define BLINK		0x80

#define	BLACK		0x00
#define BLUE		0x01
#define GREEN		0x02
#define CYAN		0x03
#define RED		0x04
#define MAGENTA		0x05
#define BROWN		0x06
#define WHITE		0x07
#define	GRAY		0x08
#define LTBLUE		0x09
#define LTGREEN		0x0A
#define LTCYAN		0x0B
#define LTRED		0x0C
#define LTMAGENTA	0x0D
#define YELLOW		0x0E
#define BWHITE		0x0F

#define	BG_BLACK	0x00
#define BG_BLUE		0x10
#define BG_GREEN	0x20
#define BG_CYAN		0x30
#define BG_RED		0x40
#define BG_MAGENTA	0x50
#define BG_YELLOW	0x60
#define BG_WHITE	0x70
#endif

#endif /*_SYS_TIME_H*/
