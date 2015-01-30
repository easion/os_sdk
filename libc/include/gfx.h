#ifndef gfx_H
#define gfx_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	unsigned short bftype;
	unsigned long  FileSize;
	unsigned long  Reserved;
	unsigned long  datastart;

	unsigned long  HeaderSize;
	unsigned long  width;
	unsigned long  height;
	unsigned short Planes;
	unsigned short  bpp;

	unsigned long compression; //Compression. Usually set to 0. 
    unsigned long SizeImage; //Size in bytes of the bitmap.  
    unsigned long XPixelsPerMeter;// Horizontal pixels per meter. 
    unsigned long YPixelsPerMeter; //Vertical pixels per meter. 
    unsigned long ColorsUsed; //Number of colors used. 
    unsigned long ColorsImportant;

} __attribute__ ((packed)) bmp_hdr;

typedef struct bitmap
{
	int x1,x2;
	int y1,y2;
	char *buf;
}BMP;

#define MXRGB(r, g, b) ((((unsigned long)r) << 16) | \
                        (((unsigned long)g) << 8) | \
                        (((unsigned long)b)))

#define MXRGBT(r, g, b, a) ((((unsigned long)a) << 24) | \
                            (((unsigned long)r) << 16) | \
                            (((unsigned long)g) << 8) | \
                            (((unsigned long)b)))

#define MXT(c) (((c) >> 24) & 0xFF)
#define MXR(c) (((c) >> 16) & 0xFF)
#define MXG(c) (((c) >> 8) & 0xFF)
#define MXB(c) (((c) & 0xFF))

#define MXTRANS(c, a) ((((unsigned long)a) << 24) | ((c) & 0xFFFFFF))

#define MXBLENDT(c1, c2, a1) \
                ((((((c1) & 0x00FF00FFl) * (256 - (a1)) + ((c2) & 0x00FF00FFl) * (a1)) & 0xFF00FF00l) | \
                  ((((c1) & 0x0000FF00l) * (256 - (a1)) + ((c2) & 0x0000FF00l) * (a1)) & 0x00FF0000l)) >> 8)

#define MXBLEND(c1, c2) (((c1) & 0xFF000000l) ? ((((c1) & 0xFF000000l) == 0xFF000000l) ? (c2) : MXBLENDT((c1), (c2), MXT(c1))) : (c1))

#define MXRGB332(c) (((((unsigned long)c) & 0x00E00000) >> 16) | \
                     ((((unsigned long)c) & 0x0000E000) >> 11) | \
                     ((((unsigned long)c) & 0x000000C0) >> 6))

#define MXRGB555(c) (((((unsigned long)c) & 0x00F80000) >> 9) | \
                     ((((unsigned long)c) & 0x0000F800) >> 6) | \
                     ((((unsigned long)c) & 0x000000F8) >> 3))

#define MXRGB565(c) (((((unsigned long)c) & 0x00F80000) >> 8) | \
                     ((((unsigned long)c) & 0x0000FC00) >> 5) | \
                     ((((unsigned long)c) & 0x000000F8) >> 3))


int gfx_putpixel(int _x, int _y, int color);
int set_lfb( unsigned int width, unsigned int height,
             unsigned int depth,  unsigned int scanline,  unsigned long ptr );
 int get_lfb( unsigned int *width, unsigned int *height,
             unsigned int *depth,  unsigned int *scanline,  unsigned long *ptr );            
int vbe_init(int mode);

#ifdef __cplusplus
}
#endif
#endif

