#define JICAMA

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stat.h>
#include "stdlib.h"
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
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

//extern void ___sig_restore();
//extern void ___masksig_restore();
extern int errno;


int kill(int pid, int sig);
pid_t getpid(void);

int
raise(int sig)
{
	if (sig < 0 || sig > NSIG)
		return -1;
	return kill(getpid(), sig);
}


int ___ssetmask(int mask)
{
	long res;
	__asm__("int $0x60":"=a" (res)
		:"0" (NR_SETMASK),"b" (mask));
	return res;
}

int sigpending(sigset_t *set)
{
	long res;
	__asm__("int $0x60":"=a" (res)
		:"0" (SIGPENDING),"b" (set));
	return res;
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oset)
{
	long res;

    int return_value;
    __asm__ volatile ("int $0x60" \
        : "=a" (return_value) \
        : "0" ((long)(SIGPROCMASK)),"b" ((long)(how)),"c" ((long)(set)), \
          "d" ((long)(oset)),"S" ((long)(0)),"D" ((long)(0)) ); \
    return return_value;
}

int ___sgetmask(void)
{
	long res;
	__asm__("int $0x60":"=a" (res)
		:"0" (NR_GETMASK));
	return res;
}

extern void asm_sig_restore();

void ___sig_restore(int sig, int mask, u32_t base)
{
	int res;
	printf("___sig_restore call args: %x-%x-%x\n", sig,mask,  base);

	__asm__("int $0x60":"=a" (res):
	"0" (75),"b" (sig),"c" (mask),"d" ((long)base));

	printf("___sig_restore backup\n");
	return;
}

void ___masksig_restore(int sig)
{
	int res;
	/*__asm__("int $0x60":"=a" (res):
	"0" (NR_SIGRETURN),"b" (sig),"c" (0),"d" ((long)0));*/
	res = netbas_system_call(NR_SIGRETURN,sig,0,0,0,0);
	return res;
}

__sighandler_t signal(int sig, __sighandler_t func)
{
	__sighandler_t res;

	//printf("___sig_restore -0x%x",(long)___sig_restore);

	/*__asm__("int $0x60":"=a" (res):
	"0" (NR_SIGNAL),"b" (sig),"c" ((long)func),"d" ((long)&asm_sig_restore));*/
	res = netbas_system_call(NR_SIGNAL,sig,func,asm_sig_restore,0,0);

	return res;
}

int sigaction(int sig,const struct sigaction * sa, struct sigaction * old)
{
	if (sa->sa_flags & SA_NOMASK)
		sa->sa_restorer=&asm_sig_restore;
	else
		sa->sa_restorer=___masksig_restore;

	sig=netbas_system_call(SIGACTION,sig,sa,old,0,0);

	/*__asm__("int $0x60":"=a" (sig)
		:"0" (SIGACTION),"b" (sig),"c" (sa),"d" (old));
		*/
	if (sig>=0)
		return sig;
	errno = -sig;
	return -1;
}

/* Low bit of signal masks. */
#define SIGBIT_0	((sigset_t) 1)
/* Mask of valid signals (0 - SIG_IN_PROC).  Assume the shift doesn't overflow. */
#define SIGMASK		((SIGBIT_0 << (NSIG + 1)) - 1)




static const char * const __sigstr[NSIG] = {
	"NONE", "HUP", "INT", "QUIT", "ILL", "CHLD", "ABRT", "PIPE",
	"FPE", "KILL", "STOP", "SEGV", "CONT", "TSTP", "ALRM", "TERM",
	"TTIN", "TTOU", "USR1", "USR2", "WINCH", "KILLTHR", "TRAP"
};

const char *strsignal(int sig)
{
	if(sig < 0 || sig >= NSIG)
		return NULL;

	return __sigstr[sig];
}

int
sigemptyset(sigset_t *set)
{
	*set = 0;
	return 0;
}

int
sigfillset(sigset_t *set)
{
	*set = ~0;
	return 0;
}

int 
sigaddset(sigset_t *set, int signo)
{
	sigset_t mask = (((sigset_t) 1) << (( signo ) - 1));
	return   ((*set |= mask), 0);
}

int 
sigdelset(sigset_t *set, int signo)
{
	sigset_t mask = (((sigset_t) 1) << (( signo ) - 1));	
	return   ((*set &= ~mask), 0);
}

int 
sigismember(const sigset_t *set, int signo)
{
	sigset_t mask = (((sigset_t) 1) << (( signo ) - 1));
	return   (*set & mask) ? 1 : 0 ;
}


int	sigsuspend(const sigset_t *_set)
{
	int res;
	
	res =  netbas_system_call(SIGPENDING,_set,0,0,0,0);
	return res;
}


int
send_signal(pid_t pid, int sig)
{
	return  -1;//_kern_send_proc_signal(pid, sig);
}

int
send_signal_thr(int tid, unsigned int sig)
{
	return  -1;//_kern_send_signal(tid, sig);
}

