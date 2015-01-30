#define JICAMA

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <int86.h>
#include <stat.h>
#include <time.h>
#include "stdlib.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/times.h>
#include <errno.h>

int real_address(u32_t *addr, int *sz )
{
	return  netbas_system_call(84,(int)addr,sz,0,0,0);
}

int real_fill(char *buf, int sz)
{
   return  netbas_system_call(85,(int)buf,sz,0,0,0);
}

int dos_exec(long runp, char *buf, int sz)
{  
	return  netbas_system_call(57,buf,sz,runp,0,0);
}

int module_input(char *buf, char **argv)
{    
	return  netbas_system_call(67,buf,argv,0,0,0);
}

int module_destory(char *buf)
{
	return  netbas_system_call(68,buf,0,0,0,0);
}

int real_read(char *buf, int sz)
{
	return  netbas_system_call(86,buf,sz,0,0,0);
}

int int86( int num, vm86regs_t *in, vm86regs_t *out)
{
	return  netbas_system_call(82,in,num,out,0,0);
}

int realint( int num, vm86regs_t *rm)
{
	return int86(num, rm, rm);
}


