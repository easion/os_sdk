#ifndef __img_gfx_h_
#define __img_gfx_h_

    inline static unsigned short bpp24to565(unsigned char r, unsigned char g, unsigned char b) {
        unsigned short result = (unsigned short)(((r << 8) & 0xF800) | ((g << 3) & 0x07E0) | (b >> 3));
        return result;
    }

    inline static unsigned long rgb(unsigned char r, unsigned char g, unsigned char b) {
        return b | g  <<  8 | r  << 16;
    }



#define MXRGB332(c) (((((unsigned long)c) & 0x00E00000) >> 16) | \
                     ((((unsigned long)c) & 0x0000E000) >> 11) | \
                     ((((unsigned long)c) & 0x000000C0) >> 6))

#define MXRGB555(c) (((((unsigned long)c) & 0x00F80000) >> 9) | \
                     ((((unsigned long)c) & 0x0000F800) >> 6) | \
                     ((((unsigned long)c) & 0x000000F8) >> 3))

#define MXRGB565(c) (((((unsigned long)c) & 0x00F80000) >> 8) | \
                     ((((unsigned long)c) & 0x0000FC00) >> 5) | \
                     ((((unsigned long)c) & 0x000000F8) >> 3))

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


#endif

