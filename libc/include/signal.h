/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_signal_h_
#define __dj_include_signal_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#define SIG_DFL ((void (*)(int))(0))
#define SIG_ERR	((void (*)(int))(1))
#define SIG_IGN	((void (*)(int))(-1))

typedef int sig_atomic_t;


#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGILL		 4
#define SIGTRAP		 5
#define SIGABRT		 6
#define SIGIOT		 6
#define SIGBUS		 7

#define SIGFPE		 8
#define SIGKILL		 9
#define SIGUSR1		10
#define SIGSEGV		11
#define SIGUSR2		12
#define SIGPIPE		13
#define SIGALRM		14
#define SIGTERM		15

#define SIGSTKFLT	16
#define SIGCHLD		17
#define SIGCONT		18
#define SIGSTOP		19
#define SIGTSTP		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGURG		23

#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTALRM	26
#define SIGPROF		27
#define SIGWINCH	28
#define SIGIO		29
#define SIGPOLL		SIGIO
#define SIGPWR		30
#define	SIGUNUSED	31



#define SIG_BLOCK	1
#define SIG_SETMASK	2
#define SIG_UNBLOCK	3

typedef   unsigned long  sigset_t;
typedef void (*__sighandler_t) (int);
typedef void (*__sigrestorer_t) (int mask, unsigned long base);
struct sigaction {
  int sa_flags;
  __sighandler_t sa_handler;
  sigset_t sa_mask;
  __sigrestorer_t sa_restorer;
};


int	kill(int _pid, int _sig);
int	sigaction(int _sig, const struct sigaction *_act, struct sigaction *_oact);
int	sigaddset(sigset_t *_set, int _signo);
int	sigdelset(sigset_t *_set, int _signo);
int	sigemptyset(sigset_t *_set);
int	sigfillset(sigset_t *_set);
int	sigismember(const sigset_t *_set, int _signo);
int	sigpending(sigset_t *_set);
int	sigprocmask(int _how, const sigset_t *_set, sigset_t *_oset);
int	sigsuspend(const sigset_t *_set);
int	raise(int _sig);
__sighandler_t signal(int sig, __sighandler_t func);

#define sigisvalid(signo) ((unsigned) (signo) <= NSIG)


#define SA_NOCLDSTOP 1		// 当子进程处于停止状态，就不对SIGCHLD 处理。
#define SA_NOMASK 0x40000000	// 不阻止在指定的信号处理程序(信号句柄)中再收到该信号。
#define SA_ONESHOT 0x80000000	// 信号句柄一旦被调用过就恢复到默认处理句柄。


#define NSIG 32

extern char *sys_siglist[];



#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_signal_h_ */
