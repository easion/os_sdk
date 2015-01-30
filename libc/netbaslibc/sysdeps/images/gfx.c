#define JICAMA

#include <stdio.h> /* va_list, va_start(), va_end() */
#include <netbas/netbas.h>
#include "gfx.h"
#include <netbas/int86.h>
#include <netbas/farptr.h>



/* General information */
static unsigned int gfx_scanline;
static unsigned int gfx_w=0;
static unsigned int gfx_h=0;
static unsigned int gfx_bpp=0;
static unsigned long gfx_base=0;

static void (*gfx_pixelline) (const int x1, const int y1, const int x2, const unsigned long * color);

/* Banked mode variables */
static unsigned int gfx_bank;

int gfx_putpixel(int _x, int _y, int color)
{
	register unsigned long pos;

	pos=gfx_base;
	if(pos)return -1;
	else
	pos+=(gfx_w*_y+_x);
	 _farsetsel(USER_GLOBAL_DATA);

	switch (gfx_bpp)
	{
	case 4:
	case 8:
		_farnspokeb( pos, color&0xff);break;
	case 16:
		_farnspokew(pos, color&0xffff);break;
	case 24:	
	case 32:	
		_farnspokel( pos, color);break;
	default:
		_farnspokel( pos, color);break;
	}
	return 0;
}

int get_lfb( unsigned int *width, unsigned int *height,
             unsigned int *depth,  unsigned int *scanline,  unsigned long *ptr )
{
	*width  = gfx_w;
	*height = gfx_h;
	*scanline  =  gfx_scanline;
	*depth  = gfx_bpp;
	*ptr    = gfx_base;

	return 0;
}

int set_lfb( unsigned int width, unsigned int height,
             unsigned int depth,  unsigned int scanline,  unsigned long ptr )
{
	 gfx_w=width;
	gfx_h=height;
	gfx_scanline=scanline;
	gfx_bpp=depth;
	gfx_base=ptr;

	return 0;
}


#define MXRGB332(c) (((((unsigned long)c) & 0x00E00000) >> 16) | \
                     ((((unsigned long)c) & 0x0000E000) >> 11) | \
                     ((((unsigned long)c) & 0x000000C0) >> 6))

static const unsigned long *gfx_copy332(unsigned long start, const unsigned long end_addr, const unsigned long * color)
{
	 while ((start & 0x03) && (start <= end_addr)) {
		  _farnspokeb(start++, MXRGB332(*color));
		  ++color;
	 }

	 while (start <= end_addr - 4) {
		  _farnspokel(start,
						  ((((color[0]) & 0x00E00000) >> 16) | (((color[0]) & 0x0000E000) >> 11) | (((color[0]) & 0x000000C0) >> 6)) |
						  ((((color[1]) & 0x00E00000) >> 8) | (((color[1]) & 0x0000E000) >> 3) | (((color[1]) & 0x000000C0) << 2)) |
						  ((((color[2]) & 0x00E00000)) | (((color[2]) & 0x0000E000) << 5) | (((color[2]) & 0x000000C0) << 10)) |
						  ((((color[3]) & 0x00E00000) << 8) | (((color[3]) & 0x0000E000) << 13) | (((color[3]) & 0x000000C0) << 18)));
		  start += 4;
		  color += 4;
	 }

	 while (start <= end_addr) {
		  _farnspokeb(start++, MXRGB332(*color));
		  ++color;
	 }

	 return color;
}


#define MX__DJGPP_VESA_LINEARVAR(factor)                         \
    const unsigned int y1scanline = y1 * gfx_scanline;    \
    const unsigned long end = y1scanline + (x2 * factor); \
    unsigned long start = y1scanline + (x1 * factor);     \


static void gfx_linear8(const int x1, const int y1, const int x2, const unsigned long * color)
{
	 MX__DJGPP_VESA_LINEARVAR(1);
	 gfx_copy332(start, end, color);
}

static void gfx_linear15(const int x1, const int y1, const int x2, const unsigned long * color)
{
	 MX__DJGPP_VESA_LINEARVAR(2);

	 while (start <= end) {
		  _farnspokew(start, MXRGB555(*color));
		  ++color;
		  start += 2;
	 }
}

static void gfx_linear16(const int x1, const int y1, const int x2, const unsigned long * color)
{
	 MX__DJGPP_VESA_LINEARVAR(2);

	 while (start <= end) {
		  _farnspokew(start, MXRGB565(*color));
		  ++color;
		  start += 2;
	 }
}

static void gfx_linear24(const int x1, const int y1, const int x2, const unsigned long * color)
{
	 MX__DJGPP_VESA_LINEARVAR(3);

	 while (start <= end) {
		  _farnspokeb(start++, MXR(*color));
		  _farnspokeb(start++, MXG(*color));
		  _farnspokeb(start++, MXB(*color));
		  ++color;
	 }
}

static void gfx_linear32(const int x1, const int y1, const int x2, const unsigned long * color)
{
	 MX__DJGPP_VESA_LINEARVAR(4);

	 while (start <= end) {
		  _farnspokel(start, *color);
		  ++color;
		  start += 4;
	 }
}

