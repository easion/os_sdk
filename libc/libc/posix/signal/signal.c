#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>

typedef void (*SignalHandler) (int);

static SignalHandler signal_list[SIGMAX];	/* SIG_DFL = 0 */

extern int end __asm__("end");

SignalHandler signal(int sig, SignalHandler func)
{
 SignalHandler temp;
 if(sig <= 0 || sig > SIGMAX || sig == SIGKILL)
 {
  errno = EINVAL;
  return SIG_ERR;
 }
 temp = signal_list[sig - 1];
 signal_list[sig - 1] = func;
 return temp;
}

int raise(int sig)
{
 SignalHandler temp;
 if(sig <= 0) return -1;
 if(sig > SIGMAX) return -1;
 temp = signal_list[sig - 1];
 if(temp == (SignalHandler)SIG_IGN
    || (sig == SIGQUIT && temp == (SignalHandler)SIG_DFL)) return 0; /* Ignore it */
 if(temp == (SignalHandler)SIG_DFL)
 {
  __libclog_printf("Exiting due to signal %u\n",sig);
  _exit(sig);
 } else if((unsigned)temp < 4096 || temp > (SignalHandler)&end) {
  __libclog_printf("Bad signal %u handler",sig);
  _exit(1);
 } else temp(sig);
 return 0;
}
