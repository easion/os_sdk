#ifndef __JPEGLS_H_
#define __JPEGLS_H_

typedef struct{
    int elem; //
    unsigned short code[256];
    unsigned char  size[256];
    unsigned char  value[256];
}huffman_t;


int decode_init(void);
int decode_huff(int scan,int *block);
void mcu_bitblt(int *src,int *dest,int width,
				   int x0,int y0,int x1,int y1);
unsigned short jpeg_get_bits(int bit);

// MCU
void mcu_bitblt(int *src,int *dest,int width,
				int x0,int y0,int x1,int y1);
void decode_mcu(void);
void decode_yuv(int h,int v,unsigned char *rgb);
void decode(unsigned char *rgb);


void jpeg_decode(unsigned char *rgb);
void jpeg_args( int* _width, int* _height );
int jpeg_init( unsigned char *ldata,int size);

#endif
