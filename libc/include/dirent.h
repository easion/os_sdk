
#ifndef _dirent_h_
#define _dirent_h_

#ifdef __cplusplus
extern "C" {
#endif



#define FAT_LFNPMAX 260 /* Max length for a long file name path  */
#define FAT_LFNMAX  255 /* Max length for a long file name       */
#define FAT_SFNPMAX 64  /* Max length for a short file name path */
#define FAT_SFNMAX  14  /* Max length for a short file name      */

#define MAXNAMLEN FAT_LFNPMAX


typedef struct
{
  char  SName[FAT_SFNMAX]; /* Null-terminated short file name in ASCII        */
  char  LName[FAT_LFNPMAX]; /* Null-terminated long file name in Unicode UTF-8 */
  unsigned long Attr;          /* File attributes                                 */
  long long CTime;         /* File creation time in Win32 or DOS format       */
  long long ATime;         /* Last access time in Win32 or DOS format         */
  long long MTime;         /* Last modification time in Win32 or DOS format   */
  unsigned long SizeHi;        /* High 32 bits of the file size in bytes          */
  unsigned long SizeLo;        /* Low 32 bits of the file size in bytes           */
  unsigned char  Reserved[8];   /* Reserved bytes, must be ignored                 */
}__attribute__ ((packed)) fat_lfn_find_t;

typedef struct dirent {
	#define d_ino d_fd
	#define d_name d_lfn.LName
  int d_fd;
  fat_lfn_find_t d_lfn;
}DIR;

int		closedir(DIR *dirp);
DIR *		opendir(const char *_dirname);
DIR *	readdir(DIR *_dirp);
void		rewinddir(DIR *_dirp);


extern int __opendir_flags; /* default is zero, used only by opendir */
#define __OPENDIR_PRESERVE_CASE	0001
#define __OPENDIR_FIND_HIDDEN	0002 /* ignored; on by default */
#define __OPENDIR_FIND_LABEL	0004
#define __OPENDIR_NO_HIDDEN	0x08 /* NOT 0002 for back-compatibility */

void seekdir(DIR *_dir, long _loc);
long telldir(DIR *_dir);
void __set_need_fake_dot_dotdot(DIR *_dir);
void _lfn_find_close(int _handle);

#ifdef __cplusplus
}
#endif

#endif /* !_dirent_h_ */
