#include <signal.h>
#include <unistd.h>
#include <errno.h>

int kill(pid_t pid, int sig)
{
 if(pid>0) return -EINVAL;
 return raise(sig);
}
