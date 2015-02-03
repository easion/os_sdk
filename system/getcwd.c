#include <stdio.h>
#include <unistd.h>


int main()
{
	char buf[256];
	printf("%s\n", getcwd(buf, 256));
}
