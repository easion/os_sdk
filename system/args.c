#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/farptr.h>
#include <sys/param.h>
#include <int86.h>
#include <bios.h>

int tty_rw(int fd, char *buf, int sz);

void text_demo(void)
{
    vm86regs_t ir;
    /* Print ASCII character */
    ir.h.ah = 9;
    /* AL = character to display */
    ir.h.al = 'x';
    /* BH = page number, BL = attribute */
    ir.x.bx = 3;
    /* Count number */
    ir.x.cx = 9;
    realint(0x10,&ir);
}

extern char **environ;
int main(int argc, char *argv[])
{
	int vbemode, i;
	MODE_INFO *vinfo;
	char *str="tcc 0.9.22\n program running!\n";

	text_demo();

	printf("argc=%d\n", argc);

	for (i=0; i<argc; i++)
	{
	printf("%s\n", argv[i]);
	}

	printf("%s\nenv:", str);
	i=0;
	while (environ[i])
	{
	printf("%s\n", environ[i]);
	i++;
	}

	//vbemode=vesa_mode_match(vinfo, 800, 600, 32);
	//printf("BEST 800*600*32 VBE MODE IS 0x%x\n", vbemode);

	return 0;
}
