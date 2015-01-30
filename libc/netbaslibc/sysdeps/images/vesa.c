#define JICAMA
#include <stdio.h>
#include <string.h>
#include <netbas/farptr.h>
#include <netbas/int86.h>
#include "gfx.h"

static unsigned long lfb_base=0xf8000000;
static unsigned long lfb_bpp=32;
static unsigned long lfb_scanline=800*4;
int jicama_gfx_mode=C80;
static void  (*myvesa_pixel)(int x, int y, const int color);
static  int (*vesa_pixelline)(int x1,int y1, int x2, unsigned char *_buf);

int gfx_bpp()
{
	return lfb_bpp;
}


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
	 if(jicama_gfx_mode==C80)return 1;/*if in vbe mode*/
	vbe_setmode(jicama_gfx_mode);
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline int vesa_pixelline15(int x1,int y1, int x2, unsigned char *_buf)
{
    unsigned int start = lfb_base+lfb_scanline*y1+x1*lfb_bpp/8;     
    unsigned int end = start+(x2-x1)*lfb_bpp/8;     

	while(start<=end){
	_farnspokew(start+=2, MXRGB555(MXRGB(_buf[0],_buf[1],_buf[3])));
	_buf+=3;
	}
   return 0;
}


static inline int vesa_pixelline16(int x1,int y1, int x2, unsigned char *_buf)
{
    unsigned int start = lfb_base+lfb_scanline*y1+x1*lfb_bpp/8;     
    unsigned int end = start+(x2-x1)*lfb_bpp/8;     

	while(start<=end){
	_farnspokew(start+=2, MXRGB565(MXRGB(_buf[0],_buf[1],_buf[3])));
	_buf+=3;
	}
   return 0;
}

static inline int vesa_pixelline24(int x1,int y1, int x2, unsigned char *_buf)
{
    unsigned int start = lfb_base+lfb_scanline*y1+x1*lfb_bpp/8;     
    unsigned int end = start+(x2-x1)*lfb_bpp/8;     

	while(start<=end){
	_farnspokeb(start++, *_buf++); /*相反的次序*/
	_farnspokeb(start++, *_buf++);
	_farnspokeb(start++, *_buf++);
	}
   return 0;
}

static inline int vesa_pixelline32(int x1,int y1, int x2, unsigned char *_buf)
{
    unsigned int start = lfb_base+lfb_scanline*y1+x1*lfb_bpp/8;     
    unsigned int end = start+(x2-x1)*lfb_bpp/8;     

	while(start<=end){
		_farnspokel(start+=4, (MXRGB(_buf[0],_buf[1],_buf[3])));
		_buf+=3;
	}
   return 0;
}

void __jicama__putimage(unsigned short x1,unsigned short y1,unsigned short xsize,unsigned short ysize, unsigned char * image)
{
	int length;
	int __y=y1;

	_farsetsel(_dos_ds);

	 /* Push the buffer to the  screen */
	 while (__y <= ysize) {
		  vesa_pixelline(x1, __y, xsize, image);
		  image += (xsize-x1)*3;
		  ++__y;
	 }
}

static void  pixel15(int x, int y, const int color)
{
    unsigned int start = lfb_base+lfb_scanline*y+x*lfb_bpp/8;     
	_farnspokew(start, MXRGB555(color));
}

static void  pixel16(int x, int y, const int color)
{
    unsigned int start = lfb_base+lfb_scanline*y+x*lfb_bpp/8;     
	_farnspokew(start, MXRGB565(color));
}

static void  pixel24(int x, int y, const int color)
{
    unsigned int start = lfb_base+lfb_scanline*y+x*lfb_bpp/8;     
	_farnspokeb(start++, MXB(color)); /*相反的次序*/
	_farnspokeb(start++, MXG(color));
	_farnspokeb(start++, MXR(color));
}

static void  pixel32(int x, int y, const int color)
{
    unsigned int start = lfb_base+lfb_scanline*y+x*lfb_bpp/8;     
	_farnspokel(start, (color));
}

//static void  (*vesa_pixelline)(int x, int y, const int color);

void  jicama_pixel(int _x, int _y, const int _color)
{
	myvesa_pixel(_x,_y,_color);
}



void buf_fill_rgb(unsigned char *buf, int len,int clor)
{
	int i;
	unsigned char r=MXR(clor);
	unsigned char g=MXG(clor);
	unsigned char b=MXB(clor);

	for (i=0;i<len; i+=3)
	{
		*(buf++)=r;
		*(buf++)=g;
		*(buf++)=b;
	}
}


int vbeinit(int a, int b, int c)
{
	int vbemode;
	MODE_INFO *vinfo;
	long limit;

	vinfo = malloc(sizeof(MODE_INFO));

	vbemode=vesa_mode_match(vinfo, a, b, c);	

	if(vinfo->PhysBasePtr==0)vbemode=0;

	//if (lfb_bpp!=c)
		printf("vbemode%x base 0x%x, x=%d y=%d bpp=%d\n", vbemode,
		vinfo->PhysBasePtr, vinfo->XResolution,vinfo->YResolution,
			vinfo->BitsPerPixel);

	lfb_base=vinfo->PhysBasePtr;
	lfb_bpp=vinfo->BitsPerPixel;
	lfb_scanline=(vinfo->BitsPerPixel/8*vinfo->XResolution);

	//limit=get_vm_region("vesa", NULL);
	if(create_vm_region( &limit, vinfo->PhysBasePtr,"vesa", a*b*c/8, 0)<0)return 0;

	switch (vinfo->BitsPerPixel)
	{
	case 8:
		myvesa_pixel=pixel32;
	break;
	case 15:
		vesa_pixelline=vesa_pixelline15;
		break;
	case 16:
		myvesa_pixel=pixel32;
		vesa_pixelline=vesa_pixelline16;
	break;
	case 24:
		vesa_pixelline=vesa_pixelline24;
		myvesa_pixel=pixel32;
	break;
	case 32:
		myvesa_pixel=pixel32;
		vesa_pixelline=vesa_pixelline32;
	break;
	default:
		vesa_pixelline=vesa_pixelline32;
		myvesa_pixel=pixel32;
	vbemode=0;
	free(vinfo);
		return 0;
	}
	if(vbemode)	jicama_gfx_mode=vbemode;
	return vbemode;
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

void SDL_vesa_stop(void)
{
	 __dpmi_regs reg;

	 //if(jicama_gfx_mode==C80)return;

	 mx__djgpp_vesa_setbank(0);

	 /* set a text mode might help problems going vesa->vga */
	 mx__djgpp_vesa_try(0x108);

	 reg.x.ax = 0x0003;
	 __dpmi_int(0x10, &reg);

	 textmode(C80);
	jicama_gfx_mode=C80;
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

void JICAMA_mouse_setup(int a,int b)
{
#if 1
		jicama_mouse_init();
		jicama_mouse_xlimit(0,a);
		jicama_mouse_ylimit(0,b);
#endif

}

int openvesadev(struct video_driver_info *info)
{
	int vbemode;
	long limit;
	MODE_INFO *vinfo;
	
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
	
	
	//需要在4m对齐
	if(create_vm_region(&limit,vinfo->PhysBasePtr, "vesa",
		vinfo->XResolution*vinfo->YResolution*vinfo->BitsPerPixel/8, 0x1000)<0)
		return 0;

	info->w=vinfo->XResolution;
	info->h=vinfo->YResolution;
	info->dpp=vinfo->BitsPerPixel;
	info->video_phyaddr=vinfo->PhysBasePtr;
	//info->video_mapaddr=(void*)get_vm_region("vesa",NULL);


	_farsetsel(_dos_ds);
	JICAMA_mouse_setup(info->w,info->h);
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

