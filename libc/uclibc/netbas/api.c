#define JICAMA
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <netbas/netbas.h>
#include <netbas/dirent.h>
#include <sys/stat.h>
#include <stdarg.h>

#  define weak_alias(name, aliasname) _strong_alias (name, aliasname)
#  define _strong_alias(name, aliasname) \
	__asm__(".global " __C_SYMBOL_PREFIX__ #aliasname "\n" \
                ".set " __C_SYMBOL_PREFIX__ #aliasname "," __C_SYMBOL_PREFIX__ #name);


/*
 * syslog, vsyslog --
 *     print message on log file; output is intended for syslogd(8).
 */
int netbas_log (int pri, const char *fmt, ...)
{
	int len;
	int res;	
	va_list ap;
	char buf[1024];

	va_start(ap, fmt);
	len=vsnprintf(buf,1024, fmt,ap);
	va_end(ap);

	res=netbas_system_call(9, (unsigned )pri, (unsigned )buf, (unsigned )len,0,0);
	return res;
}

weak_alias (netbas_log, syslog)

/*
void
syslog(int pri, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	//vsyslog(pri, fmt, ap);
	va_end(ap);
}
*/

/*
 * OPENLOG -- open system log
 */
void
openlog( const char *ident, int logstat, int logfac )
{
    
}

/*
 * CLOSELOG -- close the system log
 */
void
closelog( void )
{
}

/* setlogmask -- set the log mask level */
int setlogmask(int pmask)
{
    int omask=0;

   
    return (omask);
}



int netbas_outport (int port, unsigned long value, int type)	
{
	int res;	

	res=netbas_system_call(3, (unsigned )port, (unsigned )value, (unsigned )type,0,0);
	return res;
}

int netbas_inport (int port, unsigned long *value, int type)
{
	int res;	

	res=netbas_system_call(4, (unsigned )port, (unsigned )value, (unsigned )type,0,0);
	return res;
}


int netbas_module_in(const char *path, char *env)
{
	int res;	
	res=netbas_system_call(66, (unsigned )path, (unsigned )env, (unsigned )0,0,0);
	return res;
}

int netbas_module_out(const char *path)
{
	int res;	
	res=netbas_system_call(67, (unsigned )path, (unsigned )0, (unsigned )0,0,0);
	return res;
}

int netbas_reboot(int mode)
{
	return netbas_system_call(76,(int)mode,0,0,0,0);
}

static int _opendir(char *file, int mode)
{
	return netbas_system_call(5,file,(int)mode,0,0,0);
}



#define DULL (NETBAS_DIR *) 0
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
  unsigned char Order;        /* Sequence number for slot        */
  unsigned short Name0_4[5];   /* First 5 Unicode characters      */
  unsigned char Attr;         /* Attributes, always 0x0F         */
  unsigned char Reserved;     /* Reserved, always 0x00           */
  unsigned char Checksum;     /* Checksum of 8.3 name            */
  unsigned short Name5_10[6];  /* 6 more Unicode characters       */
  unsigned short FstClus;      /* First cluster number, must be 0 */
  unsigned short Name11_12[2]; /* Last 2 Unicode characters       */
}
__attribute__ ((packed)) lfn_entry_t;

typedef struct fat_dir
{
	unsigned char file_name[8];
	unsigned char ext_name[3];	// name and extension 
	unsigned char	attribute;		// attribute bits 

	unsigned char    lcase;		// Case for base and extension 
	unsigned char	ctime_ms;	// Creation time, milliseconds 
	unsigned short	ctime;		// Creation time 
	unsigned short	cdate;		// Creation date 
	unsigned short	adate;		// Last access date 
	unsigned short   first_high;	// High 16 bits of cluster in FAT32 
	
	unsigned short	time;
	unsigned short date;
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
  unsigned long     EntryOffset;
  int       LfnEntries;
  char      LName[FAT_LFNPMAX];
  char      SName[FAT_SFNMAX];
}fatfs_find_t;



NETBAS_DIR *netbas_opendir(const char *dirname)
{
  register NETBAS_DIR *dirp;		/* -> malloc'ed storage */
  register int fd;		/* file descriptor for read */
  static struct stat sbuf;	/* result of fstat() */  

  if ((fd = _opendir(dirname, O_RDONLY)) < 0)
	return(DULL);		/* errno set by open() */

  if ((dirp = (NETBAS_DIR *) malloc(sizeof(NETBAS_DIR))) == DULL){
	//register int serrno = errno;
	/* Errno set to ENOMEM by sbrk() */

	if (dirp != (NETBAS_DIR *) DULL) free((pointer) dirp);

	(void) close(fd);
	//errno = serrno;
	return(DULL);		/* not enough memory */
  }

  dirp->d_fd = fd;
  //dirp->dd_magic = _DIR_MAGIC;	/* to recognize DIRs */
  //dirp->dd_loc = dirp->dd_size = 0;	/* refill needed */

  return(dirp);
}

static ssize_t	 _readdir(int fd,  void *buf, size_t s)
{
	register int res;	
	res=netbas_system_call(52, (unsigned )fd, (unsigned )buf, (unsigned )s,0,0);
	return res;
}

void 	netbas_rewinddir(NETBAS_DIR *_dirp)
{
	lseek(_dirp->d_fd, 0, SEEK_SET);
}

vfs_dirent_t* 	netbas_readdir(NETBAS_DIR *_dirp)
{
	int      Res;
	int _file;
	vfs_dirent_t *Entry;

	_file=_dirp->d_fd;
	Entry = &_dirp->d_lfn;

  if ((Res = _readdir(_file, Entry, sizeof(vfs_dirent_t))) < 0) {
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
  return Entry;
}

int netbas_closedir(NETBAS_DIR *dir)
{
 close(dir->d_fd);
 free(dir);
 return 0;
}



__set_h_errno()
{
}

//weak_alias(netbas_readdir, readdir);
//weak_alias(netbas_opendir, opendir);
//weak_alias(netbas_closedir, closedir);
