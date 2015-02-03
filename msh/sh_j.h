

#ifndef _sh_H_
#define _sh_H_




union dos_time{
 struct {
  unsigned sec:5;
  unsigned min:6;
  unsigned hour:5;
	}__attribute__((packed))  t1;

	unsigned short t2;
};

union dos_date{
 struct  {
  unsigned day_of_month:5;
  unsigned month:4;
  unsigned year:7; /* since 1980 */
	}__attribute__((packed))  d1;

	unsigned short d2;
};

#define LS_BUFSZ 	(2048)

struct dir_buf
{
	char type;
	char names[20];
}ls_buf[LS_BUFSZ]; 


/* Magic numbers suggested or required by Posix specification */
#define SUCCESS	0		/* exit code in case of success */
#define FAILURE 1		/*                   or failure */


#define MSDOS_READONLY      1  // 只读
#define MSDOS_HIDDEN  2  // 隐藏文件 
#define MSDOS_SYS_FILE     4  // 系统文件 
#define MSDOS_VOLUME  8  // 卷标 
#define MSDOS_DIR     16 // 目录 
#define MSDOS_ARCH    32 // 存档文件 

#define MSDOS_ISVOLUME(attribute)		(((attribute) &0x20) && ((attribute) & 0x08))
#define MSDOS_ISDIR(attribute)		(((attribute) &0x10) && !((attribute) & 0x08))
#define MSDOS_ISREG(attribute)		(!((attribute) & 0x08) && !((attribute) &0x10))

typedef struct ndblock *ndptr;
 
struct ndblock {                /* hastable structure         */
        char    *name;          /* entry name..               */
        char    *defn;          /* definition..               */
        int     type;           /* type of the entry..        */
        ndptr   nxtptr;         /* link to next entry..       */
};
 
#define nil     ((ndptr) 0)
 

 /* How to exit the system. */
#define RBT_HALT	   0
#define RBT_REBOOT	   1
#define RBT_PANIC	   2	/* for servers */
#define RBT_MONITOR	   3	/* let the monitor do this */
#define RBT_RESET	   4	/* hard reset the system */

#define LS_LONG (0x02)

 int sh_reboot(int argc, char *argv[]);
int sh_usage(int argc, char *argv[]);
int sh_type(int argc, char *argv[]);
 int sh_cd(int argc, char *argv[]);
 int sh_ls(int argc, char *argv[]);
 int sh_dir(int argc, char *argv[]);
 int finito(int a, char *b[]);
 int sh_copy(int argc, char* argv[]);
 int sh_mkdir(int argc, char* argv[]);
int su(int c, char *s[]);
int sh_uname(int argc, char *argv[]);
 int sh_rmdir(int argc, char* argv[]);
 int sh_del(int argc, char* argv[]);
 int sh_cat(int argc, char* argv[]);
 int sh_chdir(int argc, char* argv[]);
 int sh_basename(int argc, char* argv[]);
 int sh_cwd(int argc, char* argv[]);
 int sh_sleep(int argc, char* argv[]);
int sh_exec_8086(int argc, char* argv[]);
int sh_mod_install(int argc, char* argv[]);
int sh_mod_uninstall(int argc, char* argv[]);
int sh_cls(int argc, char* argv[]);
int sh_ps(int argc, char *argv[]);
int sh_dll(int argc, char *argv[]);
int sh_ks(int argc, char *argv[]);
int sh_date(int argc, char* argv[]);
int sh_time(int argc, char* argv[]);
int sh_delfile(int argc, char *argv[]);
int sh_mkdir(int argc, char *argv[]);
int sh_beep(int argc, char** argv);
int sh_echo(int argc, char *argv[]);
int sh_pause(int argc, char *argv[]);
int module_destory(char *buf);
int module_input(char *buf, char *argv[]);
int sh_rename(int argc, char** argv);
int sh_root(int argc, char** argv);


#endif /* sh */
