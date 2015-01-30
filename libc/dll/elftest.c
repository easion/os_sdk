
#include <stdio.h>
#include <unistd.h>
//extern char** __environ;

#include "pthread.h"
int testa()
{
	return 1;
}

int testb()
{
	return 2;
}
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>
#ifndef JICAMA
/* This must be initialized data because commons can't have aliases.  */
static void *___brk_addr_test = 0;


int mybrk (void *addr)
{
    void *__unbounded newbrk, *__unbounded scratch;

    asm ("movl %%ebx, %1\n"	/* Save %ebx in scratch register.  */
	    "movl %3, %%ebx\n"	/* Put ADDR in %ebx to be syscall arg.  */
	    "int $0x80 # %2\n"	/* Perform the system call.  */
	    "movl %1, %%ebx\n"	/* Restore %ebx from scratch register.  */
	    : "=a" (newbrk), "=r" (scratch)
	    : "0" (__NR_brk), "g" (__ptrvalue (addr)));

	write(1,"hhhaaa777",6);
    ___brk_addr_test = newbrk;


    if (newbrk < addr)
    {
	__set_errno (ENOMEM);
	return -1;
    }

    return 0;
}


void sighld(int err)
{
	char hld[] = "sighld() called\n";
	write(1,hld,sizeof(hld));
}
unsigned int sleep2 (unsigned int seconds)
{
	struct timespec
  {
    time_t tv_sec;		/* Seconds.  */
    long int tv_nsec;		/* Nanoseconds.  */
  };
	unsigned int res;
	struct timespec ts = { .tv_sec = (long int) seconds, .tv_nsec = 0 };
	res = nanosleep(&ts, &ts);
	if (res) res = (unsigned int) ts.tv_sec + (ts.tv_nsec >= 500000000L);
	return res;
}
int main2( int argc, char **argv)
{
	int i=0;
	char** index=__environ;

	int test1 =testa();
	int test2 =testb();
	int n =	write(1,"sbbbbbbbbbbb",13);

	signal(SIGINT, sighld);
#if 1
	//void *p =mybrk(4096);
	void *p =malloc(4096);


	if (p)
	{
		write(1,"sbbbbbbbbbbb",13);
	}
	else
		write(1,"xcaaavaaaaaa777",13);
#endif
	
	printf( "\n dpp hello2 n=%d\nn", n);
	//	exit(22);
	fprintf(stderr, "dpp hello1\n");
	fprintf(stderr, "argc=%d\n", argc);

	for(i=0;i<argc;i++){
		fprintf(stderr, "argv[%d]='%s'\n", i, argv[i]);
	}

	i=0;
	while(*index) {
		fprintf(stderr, "environ[%d]='%s'\n", i++, *index++);
	}

	while (1)
	{
		int err;
		//err = sleep2(2);
		//printf("sleep 2 sec done %d %s ...\n", err, strerror(errno));
	}

	int pid;
	pid = fork();

	if (pid==0)
	{
		printf("fork() entry child proc\n");
		execl("/bin/fasm", "ff.asm",NULL);
		exit(0);
	}
	else if(pid>0)
	{
		printf("fork() entry father proc\n");
		wait(NULL);
	}
	else{
		printf("fork() error on fork\n");
	}

	exit(0);
}


void * process(void * arg)
{
  int i;
  fprintf(stderr, "Starting process %s\n", (char *) arg);
  for (i = 0; i < 10000; i++) {
    write(1, (char *) arg, 1);
  }
  return NULL;
}

int main(void)
{
  int retcode;
  pthread_t th_a, th_b;
  void * retval;

  retcode = pthread_create(&th_a, NULL, process, (void *) "a");
  if (retcode != 0) fprintf(stderr, "create a failed %d\n", retcode);
  else fprintf(stderr, "create a succeeded %d\n", retcode);
  retcode = pthread_create(&th_b, NULL, process, (void *) "b");
  if (retcode != 0) fprintf(stderr, "create b failed %d\n", retcode);
  else fprintf(stderr, "create b succeeded %d\n", retcode);
  retcode = pthread_join(th_a, &retval);
  if (retcode != 0) fprintf(stderr, "join a failed %d\n", retcode);
  else fprintf(stderr, "join a succeeded %d\n", retcode);
  retcode = pthread_join(th_b, &retval);
  if (retcode != 0) fprintf(stderr, "join b failed %d\n", retcode);
  else fprintf(stderr, "join b succeeded %d\n", retcode);
  return 0;
}


#else
int main(int argc, char *argv[], char *env[])
{
	int i;
    
    //write(1,"dpp",4);
	printf("Hello, world argc %d \n", argc);

	for (i=0; i<argc ; i++)
	{
		printf("arg%d - 0x%x - %s \n", i, (long)argv[i], argv[i]);
		//printf("arg%d - 0x%x  %s\n", i, (long)argv1, argv1);
	}

	for (i=0; env[i]; i++)
	{
		printf("env%d - 0x%x -%s \n", i, (long)env[i], env[i]);
	}
	
	return 0;
}


void __attribute__ ((__noreturn__)) 
__uClibc_start_main(int argc, char **argv, char **envp, 
	void (*app_init)(void), void (*app_fini)(void))
{
	exit(main(argc, argv, envp));
}

void __attribute__ ((__noreturn__)) 
__uClibc_main(int argc, char **argv, char ** envp)
{
    __uClibc_start_main(argc, argv, envp, NULL, NULL);
}

asm_sig_restore()
{
}

#endif

