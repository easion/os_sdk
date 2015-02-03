#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <netbas/netbas.h>
#include <errno.h>
#include <signal.h>
#include <sys/utsname.h>
#include <sys/socket.h>

const char **environ;
static char pwd[512]="/";
static int prog_execute(char **argv);

#define SCRIPT_NAME "initrc"
#define dbg 


int sigact(int signo, void (*handler)(int))
{
	struct sigaction sa;

	sa.sa_handler = handler; 
	sa.sa_flags = 0x40000000;
	//sigemptyset(&sa.sa_mask);
	return sigaction(signo, &sa, NULL);
}

#define printf1(format, argc...) do\
{\
	char buf[4096];\
sprintf(buf,  format, ##argc);\
write(1, buf, strlen(buf));\
}\
while (0);


void sigh(int no)
{
	printf1("init: signal %d happen\n",no);
	exit(0);
}

static char *shell_table[]=
{
		"/bin/sh",
		"/bin/bash",
		"/bin/ash",
		"/bin/msh",
		"/bin/ksh",
		"/bin/busybox",
		"/system/bin/sh",
		NULL
};

static char *find_shell()
{
	int i=0;
	struct stat statb;

		do{
			if (!shell_table[i])
			{
				return NULL;
			}
			//printf("find shell %s\n",shell_table[i]);
			if(stat(shell_table[i], &statb) == 0){
				return shell_table[i];				
			}
			
		}
		while (shell_table[i++]!=NULL);

		return NULL;
}

static char *script_table[]=
{
		"/etc/"SCRIPT_NAME,	
		"/system/"SCRIPT_NAME,
		"/"SCRIPT_NAME,	
		NULL
};

static char *find_init_script()
{
	int i=0;
	struct stat statb;

		do{
			if (!script_table[i])
			{
				return NULL;
			}

			//printf("try found %s\n", script_table[i]);
			if(stat(script_table[i], &statb) == 0){
				return script_table[i];
			}
			
		}
		while (i++);
		return NULL;
}

	 inline static void load_dlls(char *cfgfiles)
	{
		 FILE *fp = fopen(cfgfiles, "r");
		 char tmpbuf[512];
		 char *p;
		 int i;
		 char fname[64];
		 char *p1 ;

		 if (!fp)	 {
			 return ;
		 }

		 while (1)
		 {
			 p1 = fname;
			 i= 0;
			 memset(fname, 0 , sizeof(fname));
			 memset(tmpbuf, 0 , sizeof(tmpbuf));

			 p = fgets(tmpbuf, 512, fp);

			 if (p==NULL)
			 {
				 break;
			 }

			 while (*p==' ' || *p=='\t') {
				 p++;
			 }

			 if (*p == '#' || *p == '\0') {
				 continue;
			 }

			 if (strncmp(p, "module", 6))	 {
				 continue;
			 }

			 p+=6;

			 if (*p == '#' || *p == '\0') {
				 continue;
			 }

			 while (*p==' ' || *p=='\t') {
				 p++;
			 }
		
			 while (*p && *p!=' ' && *p!='\t') {
				 *p1++ = *p++;
				 if (i++>63)
				 {
					 break;
				 }
			 }


			 printf("load %s\n", fname);

			netbas_module_in(fname, (char **)0);
		 }

		 fclose(fp);
	
	}

#define SUID 0

void init_net();

int load_modules(){
	int ret;
	int fd = open("/dev/kfs", 0);
	if (fd<0)
	{
		return -1;
	}
	ret = ioctl(fd,1,NULL);
	close(fd);
	return 0;
}

void test_file_system()
{
	char buf[512];
	int fd = open("/system/vin.xml", 0);
	printf("******************************test fs:");
	if (fd<0)
	{
		printf("error\n");
		return -1;
	}
	read(fd,buf,512);
	printf("%s****************************", buf);
	close(fd);
}

static inline unsigned int do_system_call(int function_number,int p1,int p2,
                  int p3,int p4,int p5)
{
     int return_value;
    __asm__ volatile ("int $0x80" \
        : "=a" (return_value) \
        : "0" ((long)(function_number)),"b" ((long)(p1)),"c" ((long)(p2)), \
          "d" ((long)(p3)),"S" ((long)(p4)),"D" ((long)(p5)) ); \
    return return_value;
};

int netbas_setup()
{
	return do_system_call(0,0,0,0,0,0);
}


int static busybox_used=0;

int main(int argc, char *argv[])//, char ** envp)
{
	int signo;
	unsigned char ch;
	static char *execarg[4];
	struct utsname name;
	struct stat statb;
	char *initrc;
	char *shell_prog;
	int argi=0;
	int argn=0;

	int i=0;
	int need_exec_bat=1;


	for (i=0; i<argc; i++)
	{
		if (strcasecmp(argv[i],"-tty")==0)
		{
			need_exec_bat = atoi(argv[i+1]);
		}
	}

	uname(&name);
	netbas_setup();	
	busybox_used = 0;
	int fd = open("/dev/console",O_RDONLY);
	//open("/dev/console",O_RDONLY);
	//open("/dev/console",O_RDONLY);
	dup(fd);
	dup(fd);

	//write(1,"hello apps\n", 10);

	//printf("\x1B[32m Welcome %s\t%s\t%s\x1B[34;0m\n",
	//	name.sysname, name.version,   name.nodename);	



     getcwd(pwd, 512);//
	 setuid(SUID);

	/* sock start up */

	shell_prog = find_shell();
	//printf("find_shell %s OK\n", shell_prog);
	initrc= find_init_script();
	//printf("find_init_script %s OK\n", initrc);

	execarg[argi++] =shell_prog;

	if (strcmp("/bin/busybox",execarg[0]) ==0)
	{
		execarg[argi++]="ash";
		busybox_used = 1;
	}
	else{	
		execarg[argi++]=initrc;
	}

	execarg[argi]=NULL;

#if 1
	putenv("PATH=/bin:/system/bin:/user/bin");
	putenv("HOME=/user");
	putenv("HISTSIZE=50");
	putenv("ENV=$HOME/kshrc");
	putenv("TERM=vt102");
	putenv("EDITOR=/bin/vi");
#endif
	for (signo = 0; signo < 32; signo++)
		sigact(signo, SIG_IGN);

	sigact(SIGCHLD, SIG_DFL);	
#if 1
	if( busybox_used==0 && need_exec_bat){
		//printf("hi, begin exec scripts %s\n", execarg[0]);
		if(prog_execute(execarg)){
			//printf("%s() execve failed !\n",execarg[argi-1]);
			exit(1);
		}
	}
	else{
		printf("no rc files found\n");
	}
#endif
	for (; ; )
	{
		//printf("exec1d %s\n", execarg[0]);

		for (signo = 0; signo < 32; signo++)
				sigact(signo, sigh);

		sigact(SIGCHLD, SIG_DFL);

		if(busybox_used==0)
			execarg[argi-1] = NULL;

		if(prog_execute(execarg))
			exit(1);

		printf("press any key continue ...\n");
		read(0, &ch, 1);
		printf("\ninit: restart ...\n");
	}

	for (;;){
		read(0, &ch, 1);
		write(1, &ch, 1);
	}	

	return 0;
}


static int prog_execute(char **argv)
{
	pid_t pid;
	char *shell = argv[0];
	long stat=0;

	if (shell == NULL)
	{
		printf("shell program not found\n");
		exit(1);
	}


	pid = fork();

	if (pid==0) {
		printf("entry child,pid=%d\n",getpid());
		execve(shell, argv, (char **)environ);
		printf("shell not found ?pid=%d\n",getpid());
	}else if(pid>0){
		//printf("wait shell");
		wait(&stat);
	}else{
		perror("init shell failed\n");
		return -1;
	}
	return 0;
}

void tell(fd, s)
int fd;
char *s;
{
	write(fd, s, strlen(s));
}

void report(fd, label)
int fd;
char *label;
{
	int err = errno;

	tell(fd, "init: ");
	tell(fd, label);
	tell(fd, ": ");
	tell(fd, strerror(err));
	tell(fd, "\n");
	errno= err;
}
