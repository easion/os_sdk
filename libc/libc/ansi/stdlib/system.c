
#include <stdio.h> /* va_list, va_start(), va_end() */
#include <unistd.h>
#include <sys/farptr.h>

extern pid_t _fork(void);
extern pid_t _wait(int *);
extern void _exit(int);
extern void _execve(const char *path, const char ** argv, const char ** envp);
extern int _close(int);

#define	FAIL	127

const char **_penvp;
static const char *exec_tab[] = {
	"sh",			/* argv[0] */
	"-c",			/* argument to the shell */
	NULL,			/* to be filled with user command */
	NULL			/* terminating NULL */
	};

int waitstat(int *exitstatus)
{
	return wait(exitstatus);
}

int system(const char *str)
{
	int pid, exitstatus, waitval;
	int i;

	if ((pid = fork()) < 0) return str ? -1 : 0;

	if (pid == 0) {
		for (i = 3; i <= 20; i++)
			close(i);
		if (!str) str = "cd .";		/* just testing for a shell */
		exec_tab[2] = str;		/* fill in command */
		execve("/bin/sh", exec_tab, _penvp);
		/* get here if execve fails ... */
		exit(FAIL);	/* see manual page */
	}
	while ((waitval = waitstat(&exitstatus)) != pid) {
		if (waitval == -1) break;
	}
	if (waitval == -1) {
		/* no child ??? or maybe interrupted ??? */
		exitstatus = -1;
	}
	if (!str) {
		if (exitstatus == FAIL << 8)		/* execve() failed */
			exitstatus = 0;
		else exitstatus = 1;			/* /bin/sh exists */
	}
	return exitstatus;
}

