/*
 * JPEG decoding engine for DCT-baseline
 *
 *      copyrights 2003 by nikq | nikq::club.
 */

#include "jpeg.h"

static    unsigned long bit_buff;
static    int bit_remain;
extern    int mcu_width;
extern    int mcu_height;
extern    int mcu_preDC[3];
extern    huffman_t huff[2][3];

    // DQT
extern    int qt[3][64];
extern    int n_qt;

    // SOF
static    int width;
 static   int height;
    // SOS
    int scan_count;
    int scan_id[3];
extern    int scan_ac[3];
extern    int scan_dc[3];
    int scan_h[3];  // 
    int scan_v[3];  // 
 extern   int scan_qt[3]; // ]

static    int max_h,max_v;
static    int compo_count;
static    int compo_id[3];
static    int compo_sample[3];
static    int compo_h[3];
static    int compo_v[3];
static    int compo_qt[3];
static    int mcu_buf[32*32*4];
static    int*mcu_yuv[4];

    // i/o
static    unsigned char *data;
static    int data_index;
static    int data_size;

    // DRI
static    int interval;

static    unsigned char  jpeg_get_byte(void);
 static   unsigned short jpeg_get_word(void);
static    void skip(void); // ZOg
 static   void start_frame(void); // Start of Frame
 static   void start_scan(void); // Start Of Scan
 static   void def_restart_interval(void); // Define Restart Interval
 static   void def_quantize_tab(void); // Define Quantize Table
 static   void def_huffman_tab(void); // Define Huffman Table
	static   void idct(int *,int *);



int jpeg_init( unsigned char *ldata,int size)
{
    unsigned char c;
    int end = 0;
    int i;

	if(!ldata||!size){
	return -1;
	}

    for(i=0;i<3;i++)
        mcu_preDC[i]=0;

    n_qt = 0;
    max_h = 0;
    max_v = 0;
    bit_remain = 0;
    bit_buff   = 0;
    interval = 0; 

    decode_init();

    data= ldata;
    data_size = size;
    data_index= 0;

    while(!end)
    {
        c = jpeg_get_byte();

        if(data_index >= data_size)
            return -1;

        c = jpeg_get_byte();
        switch(c)
        {
        case 0xD8: break;
        case 0xD9: end = 1;break;
        case 0xC0: start_frame(); break;
        case 0xC4: def_huffman_tab(); break;
        case 0xDB: def_quantize_tab(); break;
        case 0xDD: def_restart_interval(); break;
        case 0xDA: start_scan(); end = 1;  break;
        default:
            skip();
        }
    }
    return 0;
}

void jpeg_decode(unsigned char *rgb)
{
    int h_unit,v_unit;
    int mcu_count,h,v;

    decode_init();

    h_unit = width / mcu_width;
    v_unit = height/ mcu_height;
    if((width  % mcu_width) > 0){
        h_unit++;
    }
    if((height % mcu_height) > 0){
        v_unit++;
    }

    mcu_count = 0;
    for(v=0;v<v_unit;v++){
        for(h=0;h<h_unit;h++){
            mcu_count++;

            decode_mcu();
            decode_yuv(h,v,rgb);

            if(interval > 0 && mcu_count >= interval){

                bit_remain -= (bit_remain & 7);
                bit_remain -= 8;

               // gfx_printf("remain:%d\n",bit_remain);
                mcu_preDC[0] = 0;
                mcu_preDC[1] = 0;
                mcu_preDC[2] = 0;
                mcu_count = 0;
            }
        }
    }
}


// ------------------------------------ MCU decode --------------------------
int decode_init(void)
{
    int i,j;

    for(i=0;i< scan_count;i++) {
        // i:scan
        for(j=0;j< compo_count;j++) {
            // j:frame
            if( scan_id[i] == compo_id[j]){
                scan_h[i] = compo_h[j];
                scan_v[i] = compo_v[j];
                scan_qt[i]= compo_qt[j];
                break;
            }
        }
        if(j >= compo_count){
            return 1;
        }
    }

    mcu_width  = max_h * 8;
    mcu_height = max_v * 8;

    for(i=0;i<32*32*4;i++){
        mcu_buf[i] = 0x80;
    }
    for(i=0;i<scan_count;i++){
        mcu_yuv[i] = mcu_buf + i*32*32;
    }
    return 0;
}


const int C1_16 = 4017;					// cos( pi/16) x4096 (2^12)
const int C2_16 = 3784;					// cos(2pi/16) x4096 (2^12)
const int C3_16 = 3406;					// cos(3pi/16) x4096 (2^12)
const int C4_16 = 2896;					// cos(4pi/16) x4096 (2^12)
const int C5_16 = 2276;					// cos(5pi/16) x4096 (2^12)
const int C6_16 = 1567;					// cos(6pi/16) x4096 (2^12)
const int C7_16 = 799;					// cos(7pi/16) x4096 (2^12)


//  original code from Yui's code
static void idct(int *src,int *dst){

    int		w;
    int		s0, s1, s2, s3, s4, s5, s6, s7;
    int		t0, t1, t2, t3, t4, t5, t6, t7;


    for (w = 0; w < 8; w++) {
        s4 = (src[1] * C7_16) - (src[7] * C1_16);
        s5 = (src[5] * C3_16) - (src[3] * C5_16);
        s6 = (src[3] * C3_16) + (src[5] * C5_16);
        s7 = (src[7] * C7_16) + (src[1] * C1_16);

        t0 = (src[0] + src[4]) * C4_16;
        t1 = (src[0] - src[4]) * C4_16;
        t2 = (src[2] * C6_16) - (src[6] * C2_16);
        t3 = (src[2] * C2_16) + (src[6] * C6_16);
        t4 = s4 + s5;
        t5 = s4 - s5;
        t6 = s7 - s6;
        t7 = s6 + s7;

        s0 = t0 + t3;
        s1 = t1 + t2;
        s2 = t1 - t2;
        s3 = t0 - t3;
        s5 = (t6 - t5) * 41 / 58;			// 1/sqrt(2)  12/17
        s6 = (t5 + t6) * 41 / 58;			// 1/sqrt(2)

        *src++ = (s0 + t7) >> 11;
        *src++ = (s1 + s6) >> 11;
        *src++ = (s2 + s5) >> 11;
        *src++ = (s3 + t4) >> 11;
        *src++ = (s3 - t4) >> 11;
        *src++ = (s2 - s5) >> 11;
        *src++ = (s1 - s6) >> 11;
        *src++ = (s0 - t7) >> 11;
    }

    src -= 64;

    for (w = 0; w < 8; w++) {

        t0 = (src[ 0] + src[32]) * C4_16;
        t1 = (src[ 0] - src[32]) * C4_16;
        t2 = src[16] * C6_16 - src[48] * C2_16;
        t3 = src[16] * C2_16 + src[48] * C6_16;
        s0 = t0 + t3;
        s1 = t1 + t2;
        s2 = t1 - t2;
        s3 = t0 - t3;

        s4 = src[ 8] * C7_16 - src[56] * C1_16;
        s5 = src[40] * C3_16 - src[24] * C5_16;
        s6 = src[24] * C3_16 + src[40] * C5_16;
        s7 = src[56] * C7_16 + src[ 8] * C1_16;
        t4 = s4 + s5;
        t5 = s4 - s5;
        t6 = s7 - s6;
        t7 = s6 + s7;

        s5 = (t6 - t5) * 41 / 58;			// 1/sqrt(2)
        s6 = (t5 + t6) * 41 / 58;			// 1/sqrt(2)

        dst[ 0] = ((s0 + t7) >> 15);		// 
        dst[ 8] = ((s1 + s6) >> 15);		// 
        dst[16] = ((s2 + s5) >> 15);		// 
        dst[24] = ((s3 + t4) >> 15);
        dst[32] = ((s3 - t4) >> 15);
        dst[40] = ((s2 - s5) >> 15);
        dst[48] = ((s1 - s6) >> 15);
        dst[56] = ((s0 - t7) >> 15);

        src++;
        dst++;
    }
}


void decode_mcu(void)
{
    int scan,val;
    int h,v;
    int *p,hh,vv;
    int block[64],dest[64];

    for(scan=0;scan<scan_count;scan++)
    {
        hh = scan_h[scan];
        vv = scan_v[scan];

        for(v=0;v<vv;v++){
            for(h=0;h<hh;h++){

                val = decode_huff(scan , block);

                idct(block,dest);

                p = mcu_buf + (scan * 32 * 32);

                mcu_bitblt(dest , p ,
                                mcu_width,
                                mcu_width * h / hh,
                                mcu_height* v / vv,
                                mcu_width * (h+1) / hh,
                                mcu_height* (v+1) / vv);
            }
        }
    }
}

// YCrCb=>RGB
void decode_yuv(int h,int v,unsigned char *rgb)
{
    int x0,y0,x,y,x1,y1;
    int *py,*pu,*pv;
    int Y,U,V,k;
    int R,G,B;
    int mw,mh,w;

    mw = mcu_width;
    mh = mcu_height;
    w = width;

    x0 = h * max_h * 8;
    y0 = v * max_v * 8;

    x1 = width - x0;
    if(x1 > mw)
        x1 = mw;
    y1 = height - y0;
    if(y1 > mh)
        y1 = mh;

    py = mcu_buf;
    pu = mcu_buf + 1024;
    pv = mcu_buf + 2048;


    for(y=0;y<y1;y++){
        for(x=0;x<x1;x++){
            k = y*mw+x;

            Y = py[ k ];
            U = pu[ k ];
            V = pv[ k ];

            R = 128 + ((Y*0x1000 + V*0x166E) / 4096);
            R = (R & 0xffffff00) ? (R >> 24) ^ 0xff : R;

            G = 128 + ((Y*0x1000 - V*0x0B6C) / 4096);
            G = (G & 0xffffff00) ? (G >> 24) ^ 0xff : G;

            B = 128 + ((Y*0x1000 - V*4 + U*0x1C59) / 4096);
            B = (B & 0xffffff00) ? (B >> 24) ^ 0xff : B;

            rgb[((y0+y)*w + (x0+x))*3  ] = R;
            rgb[((y0+y)*w + (x0+x))*3+1] = G;
            rgb[((y0+y)*w + (x0+x))*3+2] = B;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// -------------------------- I/O ----------------------------
static   unsigned char jpeg_get_byte(void)
{
    unsigned char c;

    // EOF
    if(data_index >= data_size)
        return 0;

    c = data[ data_index++ ];
    return c;
}
static  unsigned short jpeg_get_word(void)
{
    unsigned char h,l;

    h = jpeg_get_byte();
    l = jpeg_get_byte();
    return (h<<8)|l;
}

  unsigned short jpeg_get_bits(int bit)
{
    unsigned char  c;
    unsigned short ret;

    while( bit_remain <= 16 ){
        c = jpeg_get_byte();
        if(c == 0xFF)
            jpeg_get_byte();

        bit_buff = (bit_buff << 8) | c;
        bit_remain += 8;
    }

    ret = (bit_buff>>(bit_remain - bit))&((1<<bit)-1);
    bit_remain -= bit;

    return ret;
}

static  void skip(void)
{
    unsigned w;

    w = jpeg_get_word() - 2;
    data_index += w;
}

// start of frame
static  void start_frame(void)
{
    unsigned char c,n;
    int i,h,v;

    c = jpeg_get_word();
    c = jpeg_get_byte(); // bpp

    height = jpeg_get_word();
    width  = jpeg_get_word();

    n = jpeg_get_byte();    // Num of compo
    compo_count = n; // nf

    for(i=0;i<n;i++) {
        compo_id[i] = jpeg_get_byte();

        c = jpeg_get_byte();

        compo_sample[i] = c;
        h = (c>>4) & 0x0F;
        v =  c     & 0x0F;

        compo_h[i] = h;
        compo_v[i] = v;

        if(max_h < h)
            max_h = h;
        if(max_v < v)
            max_v = v;

        compo_qt[i] = jpeg_get_byte();
    }
}

// data restart interval
static  void def_restart_interval(void)
{
    jpeg_get_word();
    interval = jpeg_get_word();
}

// define quantize table
static  void def_quantize_tab(void)
{
    unsigned char c;
    int i,j,size;

    size = jpeg_get_word() - 2;

    while(size>0) {

        c = jpeg_get_byte();
        size--;
        j = c & 7;
        if(j > n_qt)
            n_qt = j;

        if((c>>3)){

            for(i=0;i<64;i++){
                size-=2;
                qt[j][ i ] = (jpeg_get_word()>>8);
            }
        }
        else{

            for(i=0;i<64;i++){
                size--;
                qt[j][ i ] = jpeg_get_byte();
            }
        }
    }
}

// define huffman table
static  void def_huffman_tab(void)
{
    unsigned tc,th;
    unsigned code = 0;
    unsigned char val;
    int i,j,k,num,Li[17];
    int len;
    huffman_t *table;

    len = jpeg_get_word() - 2;


    while(len > 0)
    {
        val = jpeg_get_byte();

        tc = (val>>4) & 0x0F; 
        th =  val     & 0x0F; // 

        table = (huffman_t*)&(huff[tc][th]);

        num = 0;
        for (i = 1; i <= 16; i++) {
            Li[i] = jpeg_get_byte();
            num += Li[i];
        }
        table->elem = num;

        k=0;
        for(i=1;i<=16;i++) {
            for(j=0;j<Li[i];j++) {
                table->size[k++] = i;
            }
        }

        k=0;
        code=0;
        i = table->size[0];
        while(k<num) {
            while(table->size[k] == i){
                table->code[k++] = code++;
            }
            if(k>=num)
                break;
            do{
                code = code << 1;
                i++;
            }while(table->size[k] != i);
        }

        for(k=0;k<num;k++)
            table->value[k] = jpeg_get_byte();

        len = len - 18 - num;
    }
}

// start of scan
static  void start_scan(void)
{
    int i;
    unsigned char c;
    jpeg_get_word();

    scan_count = jpeg_get_byte();

    for(i=0;i<scan_count;i++) {
        scan_id[i] = jpeg_get_byte();

        c = jpeg_get_byte();
        scan_dc[i] = c >> 4;   // DC Huffman Table
        scan_ac[i] = c & 0x0F; // AC Huffman Table
    }

    //3 bytes skip
    jpeg_get_byte();
    jpeg_get_byte();
    jpeg_get_byte();
}



void jpeg_args( int* _width, int* _height )
{
    *_width  = width;
    *_height = height;
}

