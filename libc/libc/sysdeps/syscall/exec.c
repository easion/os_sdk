
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stat.h>
#include "stdlib.h"
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


 int __execve(path, argv, envp, nargs, nenvps)
const char *path;			/* pointer to name of file to be executed */
 char * const argv[];			/* pointer to argument array */
 char * const envp[];			/* pointer to environment */
int nargs;			/* number of args */
int nenvps;			/* number of environment strings */
{
	int temp;

	temp = do_system_call(NR_EXEC,path,argv,envp,nargs,nenvps);

  /* Do the real work. 
    __asm__ volatile ("int $0x80" \
        : "=a" (temp) \
        : "0" ((long)(NR_EXEC)),"b" ((long)(path)),"c" ((long)(argv)), \
          "d" ((long)(envp)),"S" ((long)(nargs)),"D" ((long)(nenvps)) ); 	*/	

  return(temp);
}



#define WIN32

#ifdef WIN32
int __bss_count = 1;
int __main(void) { 

	printf("__main called@\n");
	return 0; 
	}
int _alloca(void) {
	printf("_alloca called@\n");
	return 0; }
#endif


