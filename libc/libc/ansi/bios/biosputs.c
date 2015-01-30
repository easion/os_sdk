/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define JICAMA
#include <stdio.h>
#include <int86.h>
#include <bios.h>

void bitdemo(void)
{
    vm86regs_t ir;
    /* Print ASCII character */
    ir.h.ah = 9;
    /* AL = character to display */
    ir.h.al = '+';
    /* BH = page number, BL = attribute */
    ir.x.bx = 3;
    /* Count number */
    ir.x.cx = 3;
    realint(0x10,&ir);
}

static void biosputs(const char v86_msg[])
{
	//static const char v86_msg[] = "Hello from V86 mode";

	const char *s;
	vm86regs_t regs;

	printf("Demo 1: INT 10h AH=0Eh (display text character)\n");

	for(s = v86_msg; *s != '\0'; s++)
	{
		regs.x.ax = 0x0E00 | *(unsigned char *)s;
		regs.x.bx = 0x0000;
		realint( 0x10, &regs);
	}
	//vm86BIOSDemo();
	//while(1);
/* INT 10h AH=0Eh doesn't handle newlines, so use kprintf() to
leave a blank line (so we can see the message printed in V86 mode) */
	printf("\n");
}