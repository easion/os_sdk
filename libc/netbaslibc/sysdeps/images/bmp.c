
#include <stdio.h> /* va_list, va_start(), va_end() */
#include <netbas/netbas.h>
#include <netbas/farptr.h>

/*
**copyright 2004.7.29  larry.li 
*/
void draw_bmp(unsigned long addr, unsigned long cx, unsigned long cy, unsigned char transparent, unsigned long tcolor)
{
	bmp_hdr *bh;
	unsigned char *bmp_data_ptr, *this_ptr;
	unsigned long bmp_width, bmp_height, bmp_linesize;
	unsigned long draw_width, draw_height;
	unsigned long x, y;
	unsigned long bmp_usedcolors, this_color;
	unsigned long colortab[256];

   unsigned long vbe_base;
   unsigned long *PTR;

    //get_lfb( &gfx_w, &gfx_h, &gfx_bpp, &gfx_bpp, &vbe_base);

	PTR=(unsigned long*)vbe_base;

	if (cx > gfx_w)
		return;
	if (cy > gfx_h)
		return;

	bh = (bmp_hdr *)addr;

	if (bh->bftype != 0x4d42) {
		vbe_printf("Not a BMP file!\n");
		return;
	}

	bmp_width = bh->width;
	bmp_height = bh->height;
	bmp_data_ptr = (unsigned char *)(addr + bh->datastart);
	if (bh->gfx_bpp != 24) {
		bmp_usedcolors = (bh->ColorsUsed) ? bh->ColorsUsed : 1 << bh->gfx_bpp;
		if (bmp_usedcolors > sizeof(colortab))
			bmp_usedcolors = 256;
		this_ptr = (unsigned char *)(addr + sizeof(*bh));
		for (x = 0; x < bmp_usedcolors; x++, this_ptr += 4)
			colortab[x] = (*(this_ptr + 2) << 16) | (*(this_ptr + 1) << 8) | (*(this_ptr + 0));
		for (; x < sizeof(colortab) / sizeof(colortab[0]); x++)
			colortab[x] = 0;
	} else
		bmp_usedcolors = 0;

	draw_width = gfx_w - cx;
	draw_width = (draw_width > bmp_width) ? bmp_width : draw_width;
	draw_height = gfx_h - cy;
	draw_height = (draw_height > bmp_height) ? bmp_height : draw_height;

	switch (bh->gfx_bpp) {
	case 1:
		bmp_linesize = ((bmp_width + 31) / 32) * 32;
		break;
	case 4:
		bmp_linesize = ((bmp_width + 7) / 8) * 4;
		if (transparent)
			for (y = 0; y < draw_height; y++) {
				for (x = 0; x < draw_width; x++) {
					this_ptr = bmp_data_ptr + (bmp_height - y - 1) * bmp_linesize + (x / 2);
					this_color = colortab[(x & 1) ? (*this_ptr & 0x0F) : ((*this_ptr >> 4) & 0x0F)];
					if (this_color != tcolor)
						PTR[gfx_w * (cy + y) + cx + x] = this_color;
				}
			}
		else
			for (y = 0; y < draw_height; y++) {
				for (x = 0; x < draw_width; x++) {
					this_ptr = bmp_data_ptr + (bmp_height - y - 1) * bmp_linesize + (x / 2);
					this_color = colortab[(x & 1) ? (*this_ptr & 0x0F) : ((*this_ptr >> 4) & 0x0F)];
					PTR[gfx_w * (cy + y) + cx + x] = this_color;
				}
			}
		break;
	case 8:
		bmp_linesize = ((bmp_width + 3) / 4) * 4;
		if (transparent)
			for (y = 0; y < draw_height; y++) {
				for (x = 0; x < draw_width; x++) {
					this_ptr = bmp_data_ptr + (bmp_height - y - 1) * bmp_linesize + x;
					this_color = colortab[*this_ptr];
					if (this_color != tcolor)
						PTR[gfx_w * (cy + y) + cx + x] = this_color;
				}
			}
		else
			for (y = 0; y < draw_height; y++) {
				for (x = 0; x < draw_width; x++) {
					this_ptr = bmp_data_ptr + (bmp_height - y - 1) * bmp_linesize + x;
					this_color = colortab[*this_ptr];
					PTR[gfx_w * (cy + y) + cx + x] = this_color;
				}
			}
		break;
	case 16:
		printf("16 bit bmp format cannot support");
		break;
	case 24:
	case 32:
		bmp_linesize = ((bmp_width * 3 + 3) / 4) * 4;
		if (transparent)
			for (y = 0; y < draw_height; y++) {
				for (x = 0; x < draw_width; x++) {
					this_ptr = bmp_data_ptr + (bmp_height - y - 1) * bmp_linesize + x * 3;
					this_color = (*(this_ptr + 2) << 16) | (*(this_ptr + 1) << 8) | (*this_ptr);
					if (this_color != tcolor)
						PTR[gfx_w * (cy + y) + cx + x] = this_color;
				}
			}
		else
			for (y = 0; y < draw_height; y++) {
				for (x = 0; x < draw_width; x++) {
					this_ptr = bmp_data_ptr + (bmp_height - y - 1) * bmp_linesize + x * 3;
					this_color = (*(this_ptr + 2) << 16) | (*(this_ptr + 1) << 8) | (*this_ptr);
					PTR[gfx_w * (cy + y) + cx + x] = this_color;
				}
			}
		break;
	default:
		break;
	}
}




const unsigned char BayerPattern[8][8]={{0,32, 8,40, 2,34,10,42},
	{48,16,56,24,50,18,58,26},
	{12,44, 4,36,14,46, 6,38},
	{60,28,52,20,62,30,54,22},
	{3,35,11,43, 1,33, 9,41},
	{51,19,59,27,49,17,57,25},
	{15,47, 7,39,13,45, 5,37},
	{63,31,55,23,61,29,53,21}};

	#define ISPAL_PATTERN_SIZE		64			/* ��ɢ�������ߴ� */
	#define ISPAL_BEGIN		64			/* ��ɫ�������ʼ�� */
	#define ISPAL_END			224			/* ��ɫ��������ֵ */
	#define ISPAL_STEP			32			/* ��ɫ�������� */
/*
ʹ�÷����ܼ򵥣�������һ��256��sizeof(RGBQUAD)�ֽڵ��ڴ棬Ȼ����Creat256Palette()������������ɫ�塣
Ȼ��ͼ����������ض����ù�һ��CnvTo256PalIndex()����������¼���еķ���ֵ��
�����͵õ���һ����Ӧ��256ɫ��ɫ��ͼ��
*/

	/* ������ɫ�壨��ɫ���ǹ̶����ݵģ�*/
	int Creat256Palette(unsigned long *pal)
	{
		unsigned long		r, g, b;
		int			cnt = 0;
		
		/* ��׼��ɫ�� */
		for (r=ISPAL_BEGIN; r<256; r+=ISPAL_STEP)
		{
			for (g=ISPAL_BEGIN; g<256; g+=ISPAL_STEP)
			{
				for (b=ISPAL_BEGIN; b<256; b+=ISPAL_STEP)
				{
					pal[cnt++] = b|(g<<8)|(r<<16);
				}
			}
		}
		 
		/* ���ص�ɫ��ʹ������� */
		return cnt;
	}

	/* ��ָ���������ת��Ϊ��ɫ������ */
	unsigned long CnvTo256PalIndex(
		int x,			/* ��������ͼ���е�ˮƽλ�� */
		int y, 			/* ��������ͼ���еĴ�ֱλ�� */
		unsigned char ucr,		/* ���ص�R���� */
		unsigned char ucg,		/* ���ص�G���� */
		unsigned char ucb		/* ���ص�B���� */
		)
	{
		unsigned long	pix = 0;

		if (ucb > ISPAL_BEGIN)
		{
			ucb = (((ISPAL_PATTERN_SIZE*((unsigned int)ucb%ISPAL_STEP))/ISPAL_STEP) < 
				BayerPattern[y&7][x&7]) ? ((unsigned int)ucb/ISPAL_STEP)*ISPAL_STEP : 
				MIN(((unsigned int)ucb/ISPAL_STEP)*ISPAL_STEP+ISPAL_STEP, ISPAL_END);
		}
		else
		{
			ucb = ISPAL_BEGIN;
		}

		if (ucg > ISPAL_BEGIN)
		{
			ucg = (((ISPAL_PATTERN_SIZE*((unsigned int)ucg%ISPAL_STEP))/ISPAL_STEP) < 
				BayerPattern[y&7][x&7]) ? ((unsigned int)ucg/ISPAL_STEP)*ISPAL_STEP : 
				MIN(((unsigned int)ucg/ISPAL_STEP)*ISPAL_STEP+ISPAL_STEP, ISPAL_END);
		}
		else
		{
			ucg = ISPAL_BEGIN;
		}

		if (ucr > ISPAL_BEGIN)
		{
			ucr = (((ISPAL_PATTERN_SIZE*((unsigned int)ucr%ISPAL_STEP))/ISPAL_STEP) < 
				BayerPattern[y&7][x&7]) ? ((unsigned int)ucr/ISPAL_STEP)*ISPAL_STEP : 
				MIN(((unsigned int)ucr/ISPAL_STEP)*ISPAL_STEP+ISPAL_STEP, ISPAL_END);
		}
		else
		{
			ucr = ISPAL_BEGIN;
		}

		pix = ((unsigned long)ucr<<16)|((unsigned long)ucg<<8)|((unsigned long)ucb);

		/* ���ظ������ڵ�ɫ���е�����ֵ */
		return (((pix&0xff)-ISPAL_BEGIN)/ISPAL_STEP)+
			(((((pix&0xff00)>>8)-ISPAL_BEGIN)/ISPAL_STEP)*6)+
			(((((pix&0xff0000)>>16)-ISPAL_BEGIN)/ISPAL_STEP)*36);
	}


