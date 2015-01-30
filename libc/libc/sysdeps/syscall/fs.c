#define JICAMA

#include <sys/types.h>
#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <int86.h>
#include <servers.h>
#include <unistd.h>
#include <errno.h>
#if 1
int netbas_sys_mount(const char *specialfile, const char *dir,int rwflag)
{
	return do_system_call(NR_MOUNT, (unsigned )specialfile, (unsigned )dir, (unsigned )rwflag,0,0);
}
int netbas_sys_chroot(const char *pathname)
{
	return do_system_call(NR_CHROOT, (unsigned )pathname, (unsigned )0, (unsigned )0,0,0);
}
int netbas_sys_unmount(const char *pathname)
{
	return do_system_call(NR_UMOUNT, (unsigned )pathname, (unsigned )0, (unsigned )0,0,0);
}



int mount(int signum, const struct sigaction *act, struct sigaction *oldact)
__attribute__((weak,alias("netbas_sys_mount")));


int chroot(int signum, const struct sigaction *act, struct sigaction *oldact)
__attribute__((weak,alias("netbas_sys_chroot")));



int unmount(int signum, const struct sigaction *act, struct sigaction *oldact)
__attribute__((weak,alias("netbas_sys_unmount")));
#endif

