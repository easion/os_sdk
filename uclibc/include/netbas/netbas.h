

#ifndef	unistd_h
#define	unistd_h
#ifdef __cplusplus
extern "C" {
#endif


#define NR_CALLS		  256	/* number of system calls allowed */

#define SYSVEC 0x80


//extern int NR_exec(regs_t reg);
#define NR_EXIT		   1 
#define NR_FORK		   2 
#define NR_READ		   3 
#define NR_WRITE		   4 
#define NR_OPEN		   5 
#define NR_CLOSE		   6 
#define NR_WAITPID		  7
#define NR_WAIT		   114
#define NR_CREAT		   8 
#define NR_LINK		   9 
#define NR_UNLINK		  10 
#define NR_CHDIR		  12 
#define NR_TIME		  13
#define NR_MKNOD		  14 
#define NR_CHMOD		  15 
#define NR_CHOWN		  16 
#define NR_BRK		  17
//#define NR_STAT		  18 
#define NR_LSEEK		  19
#define NR_GETPID		  20
#define NR_MOUNT		  21 
#define NR_UMOUNT		  22 
#define NR_SETUID		  23
#define NR_GETUID		  24
#define NR_STIME		  25
#define NR_PTRACE		  26
#define NR_ALARM		  27
#define NR_FSTAT		  28 
#define NR_STAT		  106 
#define NR_PAUSE		  29
#define NR_UTIME		  30 
#define NR_ACCESS		  33 
#define NR_NICE		  34
#define NR_SYNC		  36 
#define NR_KILL		  37
#define NR_RENAME		  38
#define NR_MKDIR		  39
#define NR_RMDIR		  40
#define NR_DUP		  41 
#define NR_PIPE		  42 
#define NR_TIMES		  43
#define NR_SETGID		  46
#define NR_GETGID		  47
#define NR_IOCTL		  54
#define NR_FCNTL		  55
#define NR_UNAME	  58
#define NR_EXEC		  11
#define NR_UMASK		  60 
#define NR_CHROOT		  61 
#define NR_SETSID		  62
#define NR_DUP2		  63
#define NR_GETPPID		  64
#define NR_GETTIMEOFDAY		  78

#if 0
#define NR_GETPGRP		  63
#define NR_OPENDIR		  65
#define NR_READDIR		  66

#define NR_GETPWD		  69

#define NR_GETMASK		  68
#define NR_SETMASK		  69
#define NR_SIGNAL		 70

/* Posix signal handling. */
#define SIGACTION	  71
#define SIGSUSPEND	  72
#define SIGPENDING	  73
#define SIGPROCMASK	  74
#define SIGRETURN	  75
#define NR_SIGRETURN 75
#define NR_REBOOT		  76
#endif

#define FAT_SFNMAX  14  /* Max length for a short file name      */
#define FAT_LFNPMAX 260 /* Max length for a long file name path  */
struct vm_region
{
	int id;
	int lock;
	int wiring;

	unsigned long vm_base;
	unsigned long vm_addr;
	int vm_size;
	char vm_name[32];
};

inline  int netbas_system_call(int function_number,int p1,int p2,
                  int p3,int p4,int p5);


int netbas_socketStartup();
int netbas_log (int pri, const char *fmt, ...);

int netbas_module_in(const char *path, char *env);
int netbas_module_out(const char *path);
int netbas_reboot(int mode);
int netbas_setup();
int sys_select( int fd, int cmd, ...);
struct shm_info
{
	char name[128];
	int len; //长度
	int count; //长度
	unsigned proc_addr_user; // 在进程中的地址
	unsigned proc_addr; // 在进程中的地址
	unsigned phy_addr; //在系统全局的物理地址
	int id;
	long flags;
	void *res1;      /* List. */
	void *res2;      /* List. */
};

int get_vm_region_info (int id, struct shm_info *dest );
int clone_vm_region (int id, char* name, void**paddr );
int remap_vm_region (int id, void* myspace);
int new_vm_region (char *name, int size, long flags, void**addr  );
int delete_vm_region ( int id );

int create_vm_region (unsigned long dest , int size, long flags, unsigned *addr  );
void* attach_vm_region (int id, int size, int *id2);

int get_vm_region_param (unsigned long *dest , int *size);
int vm_init();


typedef struct
{
    int   dy_image_id;  
    char  dy_name[ 256 ];    
    int   dy_num_count; 
    void*dy_entry_point;  
    void* dy_init;   
    void* dy_fini;  
    void* dy_text_addr;   
    void* dy_data_addr;   
    int   dy_text_size;  
    int   dy_data_size;   
    void*dy_ctor_addr;
    int dy_ctor_count;
} dyinfo_t;

int get_dynamic_module_info(int id, dyinfo_t *info);
void*dynamic_symbol(int id, char *name);
int unload_library(int id);
int load_library(char const *path,long flags);


//typedef void *va_list;
#   define DIO_BYTE	  'b'	/* byte type values */
#   define DIO_WORD	  'w'	/* word type values */
#   define DIO_LONG	  'l'	/* long type values */

#define sys_outb(p,v)	netbas_outport((p), (unsigned long) (v), DIO_BYTE)
#define sys_outw(p,v)	netbas_outport((p), (unsigned long) (v), DIO_WORD)
#define sys_outl(p,v)	netbas_outport((p), (unsigned long) (v), DIO_LONG)

/* Shorthands for netbas_inport() system call. */
#define sys_inb(p,v)	netbas_inport((p), (unsigned long*) (v), DIO_BYTE)
#define sys_inw(p,v)	netbas_inport((p), (unsigned long*) (v), DIO_WORD)
#define sys_inl(p,v)	netbas_inport((p), (unsigned long*) (v), DIO_LONG)


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
#ifdef __cplusplus
}
#endif

#endif


