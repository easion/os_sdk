
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

#ifndef _PATH_MAX
	#define _PATH_MAX 255
#endif

typedef struct
{
  char  l_long_name[260]; /* Null-terminated long file name in Unicode UTF-8 */
  unsigned short l_item_size;
  unsigned long l_attribute;          /* File attributes                                 */
  long long l_ctime;         /* File creation time in Win32 or DOS format       */
  long long l_atime;         /* Last access time in Win32 or DOS format         */
  long long l_mtime;         /* Last modification time in Win32 or DOS format   */
  unsigned long l_size_high;        /* High 32 bits of the file size in bytes          */
  unsigned long l_size_low;        /* Low 32 bits of the file size in bytes           */
  union{
    unsigned char  l_res[8];   /* Reserved bytes, must be ignored                 */
	struct 
	{
		long l_ino;
		long l_off;
	}d;
  };
}__attribute__((packed)) vfs_dirent_t;


typedef struct netbas_dirent {
	//#define d_ino d_fd
	//#define d_name d_lfn.LName
  int d_fd;
  vfs_dirent_t d_lfn;
}NETBAS_DIR;

int		netbas_closedir(NETBAS_DIR *dirp);
NETBAS_DIR *		netbas_opendir(const char *_dirname);
vfs_dirent_t* 	netbas_readdir(NETBAS_DIR *_dirp);
void		netbas_rewinddir(NETBAS_DIR *_dirp);


extern int __opendir_flags; /* default is zero, used only by opendir */
#define __OPENDIR_PRESERVE_CASE	0001
#define __OPENDIR_FIND_HIDDEN	0002 /* ignored; on by default */
#define __OPENDIR_FIND_LABEL	0004
#define __OPENDIR_NO_HIDDEN	0x08 /* NOT 0002 for back-compatibility */

void __set_need_fake_dot_dotdot(NETBAS_DIR *_dir);
void _lfn_find_close(int _handle);

#ifdef __cplusplus
}
#endif

#endif /* !_dirent_h_ */
