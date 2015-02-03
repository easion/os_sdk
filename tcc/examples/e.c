
#include <stdio.h>

int	 _write(int fd, const void *buf, int s)
{
	register int res;	
	res=do_system_call(4, (unsigned )fd, (unsigned )buf, (unsigned )s,0,0);
	return res;
}

int main() 
{	
    _write(1, "Hello World\n", 12);
    return 0;
}

