/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define JICAMA
#include <stdio.h>
#include <string.h>
#include <sys/farptr.h>
#include <int86.h>
#include <bios.h>

// location of APM BIOS entry
static struct {
	unsigned long offset;
	unsigned short segment;
} apm_entry = {0,0};
#define APM_SIGNATURE (((unsigned short)('P')<<8)|(unsigned short)('M'))

static int apm_present()
{
	vm86regs_t regs16;

	// see if APM BIOS is present
	regs16.d.eax=0x5300;
	regs16.d.ebx=0x0000;
	realint(0x15,&regs16);

	if((regs16.d.ebx&0xFFFF)!=APM_SIGNATURE)
		return 0;
	// check if 32-bit pmode i/f is supported
	if(((regs16.d.ecx&0xFFFF)&0x0002)!=0x0002) {
		printf("APM: protected mode interface not supported!\n");
		return 0;
	}
	return 1;
}

static int apm_version(ver,sub_ver,flags)
unsigned long *ver,*sub_ver,*flags;
{
	vm86regs_t regs16;

	// get APM BIOS version
	regs16.d.eax=0x5304;
	regs16.d.ebx=0x0000;
	realint(0x15,&regs16);
	*ver=((regs16.d.eax&0xFF00)>>8);
	*sub_ver=(regs16.d.eax&0x00FF);
	*ver=(((*ver&0xF0)>>4)*10)+(*ver&0x0F);
	*sub_ver=(((*sub_ver&0xF0)>>4)*10)+(*sub_ver&0x0F);
}

// detect and initialize APM BIOS
void init_apm()
{
	vm86regs_t regs16;
	static char dev_name[23];
	char tmpstr[11];
	char tmpstr2[11];

	//dectos(ver,tmpstr);
	//dectos(sub_ver,tmpstr2);
	// 32-bit pmode i/f connect
	regs16.d.eax=0x5303;
	regs16.d.ebx=0x0000;
	realint(0x15,&regs16);
	regs16.d.eax=(regs16.d.eax&0xFFFF)<<4;
	regs16.d.ecx=(regs16.d.ecx&0xFFFF)<<4;
	regs16.d.edx=(regs16.d.edx&0xFFFF)<<4;
	apm_entry.offset=regs16.d.ebx;

	//apm_entry.segment=alloc_gdt(3);
	//set_gdt_entry(regs16.d.ax,0xFFFFFFFF,DESC_GRAN_4K|DESC_32_BIT_PREFIX,DESC_PRESENT|DESC_DPL_0|DESC_APPLICATION|DESC_RO_EXEC,apm_entry.segment);
	//set_gdt_entry(regs16.d.cx,0xFFFF,DESC_GRAN_1B|DESC_16_BIT_PREFIX,DESC_PRESENT|DESC_DPL_0|DESC_APPLICATION|DESC_RO_EXEC,apm_entry.segment+1);
	//set_gdt_entry(regs16.d.dx,0xFFFFFFFF,DESC_GRAN_4K|DESC_32_BIT_PREFIX,DESC_PRESENT|DESC_DPL_0|DESC_APPLICATION|DESC_RW_DATA,apm_entry.segment+2);

	strcpy(dev_name,"APM BIOS Version ");
	strcpy(dev_name+17,tmpstr);
	dev_name[17+strlen(tmpstr)]='.';
	strcpy(dev_name+18+strlen(tmpstr),tmpstr2);
	//register_device(dev_name);
	apm_entry.segment*=8;
	//save_flags(flags);
	//sti();
	// tell APM BIOS we're APM version 1.2 driver
	asm volatile (	"lcall (%%edi)\n"
			:
			: "a" ((unsigned long)(0x530E)),
			  "b" ((unsigned long)(0x0000)),
			  "c" ((unsigned long)(0x0102)),
			  "D" (&apm_entry)
			: "memory" );
	//restore_flags(flags);
}
// deinitialize APM BIOS
void deinit_apm()
{
	vm86regs_t regs16;

	regs16.d.eax=0x5304;
	regs16.d.ebx=0x0000;
	realint(0x15,&regs16);
}
