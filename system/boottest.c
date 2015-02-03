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

int write(int a, char *b, int c)
{
	return do_system_call(4,a,b,c,0,0);
}

int uname(struct utsname *b)
{
	return do_system_call(122,b,0,0,0,0);
}

int exit(int err)
{
	return do_system_call(1,err,0,0,0,0);
}

int netbas_setup()
{
	return do_system_call(0,0,0,0,0,0);
}

int strlen(const char *s)
{
	int i =0;
	char *str = s;
	while(*str++)
		i++;
	return i;
}

void output(fd, s)
int fd;
const char *s;
{
	write(fd, s, strlen(s));
}


struct utsname name;


main()
{
	output("main() called\n");
	exit(1);
}

#if 1

void __attribute__ ((__noreturn__)) 
_start(int argc, char **argv)
{
	int cnt=0;
	char buf[]="argc=    \n";

	uname(&name);
	netbas_setup();	

	buf[7]=argc+'0';

	output(1,"_start() called\n");
	output(1, buf);
	exit(1);
	while(argv[cnt++])
		output(1, argv[cnt]);

	
}
#endif


#if 1
void __attribute__ ((__noreturn__)) 
__uClibc_main(int argc, char **argv, char ** envp)
{
	int cnt=0;
	char buf[]="argc=    \n";
	uname(&name);
	netbas_setup();	
	buf[7]=argc+'0';

	output(1,"__uClibc_main() showargv\n");
	output(1, buf);
	while(argv[cnt]){
		output(1, argv[cnt]);
		output(1, "\n");
		cnt++;
	}

	output(1,"__uClibc_main() showenv\n");
	cnt = 0;

	while(envp[cnt]){
		output(1, envp[cnt]);
		output(1, "\n");
		cnt++;
	}
	exit(1);
}
#else
void __attribute__ ((__noreturn__)) 
__uClibc_start_main(int argc, char **argv, char **envp, 
	void (*app_init)(void), void (*app_fini)(void))
{
	uname(&name);
	netbas_setup();	

	output(1,"__uClibc_start_main() called\n");
	exit(1);
}
#endif

