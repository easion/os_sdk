#define JICAMA
#include <stdio.h>
#include <string.h>
#include <netbas/farptr.h>
#include <netbas/int86.h>

static int current_gfx_mode=C80;



void dump_vbe_info(VESA_INFO *info)
{
	 printf("VBE INFO DUMP:\n  ");
	 printf(" VESASignature:%s\n ", info->VESASignature);
	 printf(" VESAVersion:%x\n ", info->VESAVersion);
	 printf(" OEMStringPtr:%x\n ", (unsigned int)info->OEMStringPtr);
	 printf(" VideoModePtr:%x\n ", (unsigned int)info->VideoModePtr);
	 printf(" TotalMemory:%x\n ", info->TotalMemory);
}

int get_vbe_info(VESA_INFO *info)
{
	unsigned long a=0x9000;
	int sz;
	vm86regs_t reg86;

	reg86.x.ax = 0x4F00;

	reg86.x.di = FP_OFF(a);
	reg86.x.es = FP_SEG(a);

	dosmemput("VBE2", 4, a);
	realint( 0x10, &reg86 );

	/* Mode info did not work */
	if (reg86.x.ax!=0x004f)	  return -1;

	dosmemget(a,  sizeof(VESA_INFO), (char *)info);

	if (strncmp((const char *) info->VESASignature, "VESA", 4) != 0){
	 printf("No vesa mode Found!\n");
	  return -1;
	}
	//printf("%s Found!\n", info->VESASignature);
	return 0;
}

int get_mode_info(int mode, MODE_INFO * mode_info)
{
	unsigned long a=0x9000;
	int i=0,c,sz;
	vm86regs_t reg86;

	//real_address(&a, &sz);

	//printf("sizeof(MODE_INFO)=%d", sizeof(MODE_INFO));	

	for (c = 0; c < sizeof(MODE_INFO); c++)
		_farpokeb(USER_GLOBAL_DATA, a + c, 0);

	do
	{
		reg86.x.ax = 0x4F01;
		reg86.x.cx = mode;

		reg86.x.di = FP_OFF(a);
		reg86.x.es = FP_SEG(a);

		realint( 0x10, &reg86 );

		//if (reg86.x.ax==0x004f)
			break;
	}
	while(i++<10);

	/* Mode info did not work */
	if (reg86.x.ax!=0x004f){
		printf("ax=%x|(%x)", reg86.x.ax, mode);
		return -1;
	}

	//real_read((char *)mode_info, sizeof(MODE_INFO));
	dosmemget(a,  sizeof(MODE_INFO), (char *)mode_info);

	return 0;
}

int vbe_setmode(int mode)
{
    vm86regs_t rm;

	rm.x.ax	= 0x4F02;
	rm.x.bx	= (mode|0x4000|0x8000)&0xffff ;
	rm.x.cx	= 3;

	realint( 0x10, &rm );
	if (rm.x.ax!=0x004f) return -1;
	return 0;
}

int entry_vbe_mode()
{
	 if(current_gfx_mode==C80)return 1;/*if in vbe mode*/
	vbe_setmode(current_gfx_mode);
	return 0;
}


static int vesa_scoremode(MODE_INFO * mode, int x, int y, int c)
{
	 /* Error for resolution differences */
	 const int xdiff = x - mode->XResolution;
	 const int ydiff = y - mode->YResolution;
	 const int cdiff = c - mode->BitsPerPixel;
	 int err = (xdiff * xdiff) + (ydiff * ydiff) + (cdiff * cdiff);

	 /* Supported in hardware and graphic mode */
	 if ((mode->ModeAttributes & 0x19) != 0x19){
		 printf("not graphic mode mode0x19\n");
		  return 0x0fffffff;
	 }

	 /* We prefer a linear mode if possible */
	 if (mode->ModeAttributes & 0x80)
		  --err;

	 /* We can only handle certian memory model */
	 switch (mode->MemoryModel) {

		  /* Packed pixel is ok, with some restrictions */
	 case 4:
		  if (
		 (mode->WinGranularity != 64) ||
		 (mode->WinSize != 64) || 
		 (mode->BitsPerPixel != 8)
		 ){
		 printf("vesa_scoremode error: g=%d, s=%d, p = %d", 
			 mode->WinGranularity, mode->WinSize,mode->BitsPerPixel);
				return 0x0fffffff;
		}
		  break;

		  /* We prefer direct color if possible */
	 case 6:
		  --err;
		  break;

		  /* We cant handle other wierd modes */
	 case 0:						  /* text */
	 case 1:						  /* CGA */
	 case 2:						  /* Hercules */
	 case 3:						  /* planar */
	 case 5:						  /* non-chain 4, 256 color */
	 case 7:						  /* YUV */
	 default:
		  return 0x0fffffff;
	 }
	 return err;
}

 int vesa_mode_match(MODE_INFO * ret, int w, int h, int c)
{
	 int i;
	 int mode_list[1024];
	 int number_of_modes;
	 long mode_ptr;
	 int bestmode = 0;
	 int bestscore = 0x0fffffff;

	 VESA_INFO vesa;

	 if (!ret)
	 {
		 return 0;
	 }

	 /* Get the basic VESA information */
	 if (get_vbe_info(&vesa) != 0){
		 printf("no vesa found!\n");
		  return 0;
	 }


	 /* Make a list of avialable modes */
	 mode_ptr = ((vesa.VideoModePtr & 0xFFFF0000) >> 12) + 
		 (vesa.VideoModePtr & 0xFFFF);
	 number_of_modes = 0;

	 while (_farpeekw(USER_GLOBAL_DATA, mode_ptr) != 0xFFFF) {
		  mode_list[number_of_modes] = _farpeekw(USER_GLOBAL_DATA, mode_ptr);
		  number_of_modes++;
		  mode_ptr += 2;
	 }	

	 /* Check out if the mode matches what we want */
	 for (i = 0; i < number_of_modes; i++) {
		  int score;
		  MODE_INFO mode;

		  if (get_mode_info(mode_list[i], &mode) != 0){
			  printf("mode_list[i] %d not exist\n", mode_list[i]);
				continue;
		  }

		  score = vesa_scoremode(&mode, w, h, c);

		  /* Is it a closely matching resolution */
		  if (score < bestscore) {
				bestmode = mode_list[i];
				bestscore = score;
				memcpy(ret, &mode,sizeof(mode));
				//*ret = mode;
		  }

	 }

	 return bestmode;
}



static unsigned mx__djgpp_vesa_try(const int mode)
{
	 __dpmi_regs r;

	 /* Set the graphics mode */
	 r.x.ax = 0x4F02;
	 r.x.bx = mode;
	 __dpmi_int(0x10, &r);

	 /* Check for failure */
	 if ((r.h.al != 0x4f) || (r.h.ah))
		  return 0;

	 return 1;
}

static void mx__djgpp_vesa_setbank(unsigned int bank_number)
{
	 __dpmi_regs r;

	 r.x.ax = 0x4F05;
	 r.x.bx = 0;
	 r.x.dx = bank_number;
	 __dpmi_int(0x10, &r);

}

void vesa_stop(void)
{
	 __dpmi_regs reg;

	 //if(current_gfx_mode==C80)return;

	 mx__djgpp_vesa_setbank(0);

	 /* set a text mode might help problems going vesa->vga */
	 mx__djgpp_vesa_try(0x108);

	 reg.x.ax = 0x0003;
	 __dpmi_int(0x10, &reg);

	 textmode(C80);
	current_gfx_mode=C80;
}


void text_mode()
{
	int i;
    vm86regs_t ir;

    ir.h.al = 0x03;
	realint( 0x10, &ir );
}

void real_12test()
{
	int i;
    vm86regs_t ir;

    ir.h.al = 0x12;
	realint( 0x10, &ir );
    // Put some pixels
    for (i = 0; i < 200; i++) {
	ir.h.ah = 0x0C;
	ir.h.al = i % 16;
	ir.x.bx = 0;
	ir.x.dx = i+40;
	ir.x.cx = i+100;
	realint( 0x10, &ir );
	}

}

struct video_driver_info
{
	int w,h,dpp;
	void *video_phyaddr;
	void *video_mapaddr;
	int share_id;
};

int openvesadev(struct video_driver_info *info)
{
	int vbemode;
	long limit;
	MODE_INFO *vinfo;
	int id;
	int size;
	
	vinfo = malloc(sizeof(MODE_INFO));
	
	vbemode=vesa_mode_match(vinfo, info->w, info->h, info->dpp);
	
	//if (lfb_bpp!=info->dpp)
	{
	netbas_log(3,"vbemode%x base 0x%x, x=%d y=%d bpp=%d\n", vbemode,
	vinfo->PhysBasePtr, vinfo->XResolution,vinfo->YResolution,vinfo->BitsPerPixel);
	}
	
	if(vbemode == 0){
		free(vinfo);
		return -1;
	}
	
	size=vinfo->XResolution*vinfo->YResolution*vinfo->BitsPerPixel/8;
	id = create_vm_region(vinfo->PhysBasePtr,size, 0x1000,&limit);

	if(id<0)
		return 0;
	

	info->w=vinfo->XResolution;
	info->h=vinfo->YResolution;
	info->dpp=vinfo->BitsPerPixel;

	info->video_phyaddr=vinfo->PhysBasePtr;
	info->video_mapaddr=limit;

	info->share_id=id;


	_farsetsel(_dos_ds);
	free(vinfo);
	return vbe_setmode(vbemode);  //if ok, return 0.
	
}

static char *g_bios_buf = (char *)0x4000;

static void * vesa_save_state (void)
{
	void *buffer;
	__dpmi_regs r;

	memset(&r, 0, sizeof(r));
	r.x.ax = 0x4f04;
	r.x.cx = 0xf; 	/* all states */
	r.x.dx = 0; 	/* get buffer size */
	__dpmi_int(0x10, &r);	

	if ((r.x.ax & 0xffff) != 0x4f) {
		goto err0;
	}

	buffer = g_bios_buf;
	//g_bios_buf+=((r.x.bx & 0xffff) * 64);
	if (buffer == NULL) {
		goto err0;
	}

	memset(&r, 0, sizeof(r));
	r.x.ax = 0x4f04;
	r.x.cx = 0xf; 	/* all states */
	r.x.dx = 1; 	/* save state */
	r.x.es = (unsigned int)buffer >> 4;
	r.x.bx = (unsigned int)buffer & 0xf;
	__dpmi_int(0x10, &r);
	
	if ((r.x.ax & 0xffff) != 0x4f) {
		goto err1;
	}

	return buffer;
err1:	
err0:	return NULL;
}

static int vesa_restore_state (void *buffer)
{
	int ret = 0;
	__dpmi_regs r;

	memset(&r, 0, sizeof(r));
	r.x.ax = 0x4f04;
	r.x.cx = 0xf; 	/* all states */
	r.x.dx = 2; 	/* restore state */
	r.x.es = (unsigned int) buffer >> 4;
	r.x.bx = (unsigned int) buffer & 0xf;
	__dpmi_int(0x10, &r);
		
	if ((r.x.ax & 0xffff) != 0x4f) {
		ret = -1;
	}

	return ret;
}
#if 0

static unsigned mx__djgpp_vesa_try(const int mode)
{
	 __dpmi_regs r;

	 /* Set the graphics mode */
	 r.x.ax = 0x4F02;
	 r.x.bx = mode;
	 __dpmi_int(0x10, &r);

	 /* Check for failure */
	 if ((r.h.al != 0x4f) || (r.h.ah))
		  return 0;

	 return 1;
}

static void mx__djgpp_vesa_setbank(unsigned int bank_number)
{
	 __dpmi_regs r;

	 r.x.ax = 0x4F05;
	 r.x.bx = 0;
	 r.x.dx = bank_number;
	 __dpmi_int(0x10, &r);

}


#endif

