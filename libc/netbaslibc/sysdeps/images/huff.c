
#include "jpeg.h"

    // MCU
    int mcu_width;
    int mcu_height;
    int mcu_preDC[3];

    // DQT
    int qt[3][64];
    int n_qt;
    int scan_qt[3]; // ]
    int scan_ac[3];
    int scan_dc[3];
//    int base_img[64][64];

    // DHT
    huffman_t huff[2][3];

static    int huffman_get_value(int size);
static   int get_huff(int tc,int th);

static const int zigzag_table[]={
     0, 1, 8, 16,9, 2, 3,10,
    17,24,32,25,18,11, 4, 5,
    12,19,26,33,40,48,41,34,
    27,20,13, 6, 7,14,21,28,
    35,42,49,56,57,50,43,36,
    29,22,15,23,30,37,44,51,
    58,59,52,45,38,31,39,46,
    53,60,61,54,47,55,62,63,
    0
};

static int huffman_get_value(int size) {
    int val = 0;
    if(size == 0)
        val = 0;
    else
    {
        val = jpeg_get_bits(size);
        if (!(val & (1<<(size-1))))
            val = val - (1 << size) + 1;
    }
    return val;
}

static int get_huff(int tc,int th)
{
    huffman_t *h = &(huff[tc][th]);
    int code,size,k,v;

    code = 0;
    size = 0;
    k = 0;

    while( size < 16 ) {
        size++;
        v = jpeg_get_bits(1);
        code = (code << 1) | v;

        while(h->size[k] == size){
            if(h->code[k] == code){
                return h->value[k];
            }
            k++;
        }
    }

    return -1;
}


int decode_huff(int scan,int *block)
{
    int size, val, run, index;
    int *pQt = (int *)(qt[scan_qt[scan]]);

    // DC
    size = get_huff(0,scan_dc[scan]);
    if(size < 0)
        return 0;

    val = huffman_get_value(size);
    mcu_preDC[scan] += val;
    block[0] = mcu_preDC[scan] * pQt[0];

    index = 1;
    while(index<64)
    {
        size = get_huff(1,scan_ac[scan]);
        if(size < 0)
            break;
        // EOB
        if(size == 0)
            break;

        // RLE
        run  = (size>>4)&0xF;
        size = size & 0x0F;

        val = huffman_get_value(size);

        // ZRL
        while (run-- > 0)
            block[ zigzag_table[index++] ] = 0;

        block[ zigzag_table[index] ] = val * pQt[index];
        index++;
    }
    while(index<64)
        block[zigzag_table[index++]]=0;
    return 0;
}

#define INDEX(X,Y) (((Y)*8)+(X))
void mcu_bitblt(int *src,int *dest,int width,
                       int x0,int y0,int x1,int y1)
{
    int w,h,t;
    int x,y,x2,y2;
    int dx,dy;
    int c1,c2,c3,c4;
    int vx1,vx2;
    w = x1 - x0;
    h = y1 - y0;

    for(y=y0;y<y1;y++) {
        t = (y-y0) * 8;
        y2 = t / h;
        dy = t % h;
        for(x=x0;x<x1;x++) {
            t = (x-x0) * 8;
            x2 = t / w;
            dx = t % w;
            if(x2+1 > 7){
                c1 = src[INDEX(x2,y2)];
                c2 = c1;
                if(y2+1 > 7){
                    c3 = c1;
                    c4 = c1;
                } else {
                    c3 = src[INDEX(x2,y2+1)];
                    c4 = c3;
                }
            }
            else{
                c1 = src[INDEX(x2  ,y2)];
                c2 = src[INDEX(x2+1,y2)];
                if(y2+1 > 7){
                    c3 = c1;
                    c4 = c2;
                } else {
                    c3 = src[INDEX(x2  ,y2+1)];
                    c4 = src[INDEX(x2+1,y2+1)];
                }
            }
            vx1 = (c1 * (w-dx) + c2 * dx) / w;
            vx2 = (c3 * (w-dx) + c4 * dx) / w;
            dest[(y*width) + x] = (vx1 *(h-dy) + vx2 * dy) / h;
        }
    }
}
#undef INDEX

