/* opendir -- open a directory stream	Author: D.A. Gwyn */

/*	last edit:	27-Oct-1988	D A Gwyn	*/
#define JICAMA

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define DULL (DIR *) 0
#define CULL (char *) 0


#define FATLFN
#define LFN_FETCH_SLOTS 21
#define LFN_END_FLAGS 0x40

typedef char *pointer;		/* (void *) if you have it */

#ifndef O_RDONLY
#define	O_RDONLY	0
#endif

#ifndef S_ISDIR			/* macro to test for directory file */
#define	S_ISDIR( mode )		(((mode) & S_IFMT) == S_IFDIR)
#endif


/* FAT 32-byte Long File Name Directory Entry structure */
typedef struct
{
  u8_t Order;        /* Sequence number for slot        */
  u16_t Name0_4[5];   /* First 5 Unicode characters      */
  u8_t Attr;         /* Attributes, always 0x0F         */
  u8_t Reserved;     /* Reserved, always 0x00           */
  u8_t Checksum;     /* Checksum of 8.3 name            */
  u16_t Name5_10[6];  /* 6 more Unicode characters       */
  u16_t FstClus;      /* First cluster number, must be 0 */
  u16_t Name11_12[2]; /* Last 2 Unicode characters       */
}
__attribute__ ((packed)) lfn_entry_t;

typedef struct fat_dir
{
	unsigned char file_name[8];
	unsigned char ext_name[3];	// name and extension 
	unsigned char	attribute;		// attribute bits 

	u8_t    lcase;		// Case for base and extension 
	u8_t	ctime_ms;	// Creation time, milliseconds 
	u16_t	ctime;		// Creation time 
	u16_t	cdate;		// Creation date 
	u16_t	adate;		// Last access date 
	u16_t   first_high;	// High 16 bits of cluster in FAT32 
	
	u16_t	time;
	u16_t date;
	unsigned short first_cluster;// first cluster 
	unsigned long	size;		// file size (in u8_ts) 
}__attribute__((packed))fat_dir_entry;

#define MSDOS_READONLY      1  // 只读
#define MSDOS_HIDDEN  2  // 隐藏文件 
#define MSDOS_SYS_FILE     4  // 系统文件 
#define MSDOS_VOLUME  8  // 卷标 
#define MSDOS_LONGNAME     (MSDOS_READONLY |  MSDOS_HIDDEN | MSDOS_SYS_FILE | MSDOS_VOLUME)//  
#define MSDOS_DIR     16 // 目录 
#define MSDOS_ARCH    32 // 存档文件 

#define MSDOS_ISVOLUME(attribute)		(((attribute) &0x20) && ((attribute) & 0x08))
#define MSDOS_ISDIR(attribute)		(((attribute) &0x10) && !((attribute) & 0x08))
#define MSDOS_ISREG(attribute)		(!((attribute) & 0x08) && !((attribute) &0x10))


/* Finddata block for the internal "fat_do_readdir" function (fat_readdir) */
typedef struct
{
  fat_dir_entry SfnEntry;
  u32_t     EntryOffset;
  int       LfnEntries;
  char      LName[FAT_LFNPMAX];
  char      SName[FAT_SFNMAX];
}fatfs_find_t;



/*
 * construct a dosfs filename
 */
void fat_expand_name(char* name, char* _ext, char* buf)
{
   char* p;
   char ext[4];

   strncpy(buf, name, 8);
   strncpy(ext, _ext, 3);

   buf[8] = 0;
   ext[3] = 0;

   p = buf;
   while((*p != 0) && (*p != ' '))
      p++;

   if((*ext != 0) && (*ext != ' ')) {
      char* e = ext;
      *p++ = '.';
      while((*e != 0) && (*e != ' ')) {
         *p++ = *e++;
      }
   }
   *p = 0;
}

DIR *opendir(const char *dirname)
{
  register DIR *dirp;		/* -> malloc'ed storage */
  register int fd;		/* file descriptor for read */
  static struct stat sbuf;	/* result of fstat() */

  if (stat(dirname, &sbuf) != 0 || !S_ISDIR(sbuf.st_mode)) {
	(void) close(fd);
	errno = ENOTDIR;
	return(DULL);		/* not a directory */
  }

  if ((fd = open(dirname, O_RDONLY)) < 0)
	return(DULL);		/* errno set by open() */

  if ((dirp = (DIR *) malloc(sizeof(DIR))) == DULL){
	register int serrno = errno;
	/* Errno set to ENOMEM by sbrk() */

	if (dirp != (DIR *) DULL) free((pointer) dirp);

	(void) close(fd);
	errno = serrno;
	return(DULL);		/* not enough memory */
  }

  dirp->d_fd = fd;
  //dirp->dd_magic = _DIR_MAGIC;	/* to recognize DIRs */
  //dirp->dd_loc = dirp->dd_size = 0;	/* refill needed */

  return(dirp);
}

#if 0
/* Calculate the 8-bit checksum for the long file name from its */
/* corresponding short name.                                    */
/* Called by split_lfn and find (find.c).                       */
u8_t lfn_checksum(fat_dir_entry *dirbuf)
{
  int __s = 0, i;
  char *short_name=(char *)dirbuf;

  for (i = 0; i < 11; i++)
  {
    __s = (((__s & 1) << 7) | ((__s & 0xFE) >> 1)) + short_name[i];
  }
  return __s;
}



int fat_fetch_lfn(fat_dir_entry *dir_buf, int __fpos, u16_t *fname)
{
  lfn_entry_t *lfnslot  = (lfn_entry_t *) &dir_buf[__fpos];
  u8_t       Checksum = lfn_checksum(&dir_buf[__fpos]);
  int        order    = 0;
  int        name_pos  = 0;
  int        k;

  do
  {
	  --lfnslot;
	  ++order;

   // if (lfnslot < (lfn_entry_t *) dir_buf)lfnslot += LFN_FETCH_SLOTS;

    if (lfnslot->Attr != MSDOS_LONGNAME) return 0;
    if (order != (lfnslot->Order & 0x1F)) return 0;
    if (Checksum != lfnslot->Checksum) return 0;

    /* Ok, the LFN slot is valid, attach it to the long name */
    for (k = 0; k < 5; k++) fname[name_pos++] = lfnslot->Name0_4[k];
    for (k = 0; k < 6; k++) fname[name_pos++] = lfnslot->Name5_10[k];
    for (k = 0; k < 2; k++) fname[name_pos++] = lfnslot->Name11_12[k];
  }
  while (!(lfnslot->Order & LFN_END_FLAGS));

  if (fname[name_pos - 1] != 0x0000) fname[name_pos] = 0x0000;

  return order;
}

static int fat_do_readdir( int _file, fatfs_find_t *findbuf)
{
  fat_dir_entry  dir_buf[LFN_FETCH_SLOTS];
  int        __fpos = 0; /*start first entry*/
  int        num_bytes;
  u16_t       LongNameUtf16[FAT_LFNMAX];

  num_bytes = read(_file, (char *)&dir_buf[0], 32);
  if (num_bytes < 0) return num_bytes;

  while (num_bytes > 0)
  {
    if (dir_buf[__fpos].file_name[0] == 0x00) return -1;

    if (dir_buf[__fpos].file_name[0] != 0xe5)
    {
      if (dir_buf[__fpos].attribute != MSDOS_LONGNAME)/*skip all long filename entry */
      {
        findbuf->SfnEntry    = dir_buf[__fpos];
       //findbuf->EntryOffset = _file->TargetPos - num_bytes;
        fat_expand_name(dir_buf[__fpos].file_name, dir_buf[__fpos].ext_name, findbuf->SName);

        findbuf->LfnEntries = fat_fetch_lfn(dir_buf, __fpos, LongNameUtf16);

        if (findbuf->LfnEntries){
          fd32_utf16to8(LongNameUtf16, findbuf->LName);
           //printf(("Found: %-14s%s\n", findbuf->SName, findbuf->LName));
		}
      else{
          strcpy(findbuf->LName, findbuf->SName); 
	  }

        return 0; /*ok backup*/
      }

    }

    if (++__fpos == LFN_FETCH_SLOTS) 
		__fpos = 0;

    num_bytes = read(_file, (char *)&dir_buf[__fpos], 32);
    if (num_bytes < 0) return num_bytes;

  } /*end  while */

  return -1;
}


DIR* 	readdir1(DIR *_dirp)
{
	int      Res;
	int _file;
	fat_lfn_find_t *Entry;
	fatfs_find_t F;

	_file=_dirp->d_fd;
	Entry = &_dirp->d_lfn;

  if ((Res = fat_do_readdir(_file, &F)) < 0) return DULL;

  Entry->Attr   = F.SfnEntry.attribute;
  Entry->CTime  = F.SfnEntry.ctime + (F.SfnEntry.cdate << 16);
  Entry->ATime  = F.SfnEntry.adate << 16;
  Entry->MTime  = F.SfnEntry.time + (F.SfnEntry.date << 16);
  Entry->SizeHi = 0;
  Entry->SizeLo = F.SfnEntry.size;

  strcpy(Entry->LName, F.LName);
  strcpy(Entry->SName, F.SName);
  return _dirp;
}
#endif
DIR* 	readdir(DIR *_dirp)
{
	int      Res;
	int _file;
	fat_lfn_find_t *Entry;

	_file=_dirp->d_fd;
	Entry = &_dirp->d_lfn;

  if ((Res = _readdir(_file, Entry, sizeof(fat_lfn_find_t))) < 0) {
	  //printf("no found\n");
	  return DULL;
  }

  /*Entry->Attr   = F.SfnEntry.attribute;
  Entry->CTime  = F.SfnEntry.ctime + (F.SfnEntry.cdate << 16);
  Entry->ATime  = F.SfnEntry.adate << 16;
  Entry->MTime  = F.SfnEntry.time + (F.SfnEntry.date << 16);
  Entry->SizeHi = 0;
  Entry->SizeLo = F.SfnEntry.size;

  strcpy(Entry->LName, F.LName);
  strcpy(Entry->SName, F.SName);*/
 // printf("l %s s %s\n", Entry->LName, Entry->SName);
  return _dirp;
}

int	closedir(DIR *dirp)
{
	close(dirp->d_fd);
	free(dirp);
	return 0;
}

void		rewinddir(DIR *_dirp)
{
	lseek(_dirp->d_fd, 0,0);
}

