#define JICAMA
#include <stdlib.h>
#include <stdio.h>
#include <sys/farptr.h>
#include <int86.h>
#include <signal.h>
#include "jpeg.h"
#include "gfx.h"


int decode_jpeg(u8_t *p, int s, int _x, int _y)
{
    int pos_x, pos_y;
    int Vbpp    = gfx_bpp() / 8;
    unsigned char *img_buffer;
	 int  w,h;

	if(jpeg_init(p,s)!=0){
		printf("JPEG format error!\n");
		return -1;
	}
    jpeg_args(&w, &h);
	printf("decode_jpeg w=%d,h=%d", w,h);

    img_buffer = malloc(w * h * 3);
	if(!img_buffer){
		printf("JPEG VIEW Failed!\n");
		return -1;
		}
    jpeg_decode(img_buffer);

	if(entry_vbe_mode())return -1;

    for(pos_y = 0; pos_y < h; pos_y++)
    {
        for(pos_x = 0; pos_x < w; pos_x++)
        {
            //int k  = (pos_x + (pos_y * VESAwidth)) * Vbpp;
            int k2 = (pos_x + (pos_y * w)) * 3;
            //if (Vbpp == 2)/*16 bit*/
            //{
                //*(unsigned short*)&VESAlfb[k] = bpp24to565(img_buffer[k2], img_buffer[k2 + 1], img_buffer[k2 + 2]);
           // }
           // else /*24-32*/
           // {
				jicama_pixel(pos_x+_x,pos_y+_y,
					MXRGB( img_buffer[k2 + 0],img_buffer[k2 + 1],img_buffer[k2 + 2]));
                //VESAlfb[k]   = img_buffer[k2 + 2];
                //VESAlfb[k+1] = img_buffer[k2 + 1];
                //VESAlfb[k+2] = img_buffer[k2];
           // }
        }
    }
	free(img_buffer);
	return 0;
}


void sigalrm(int signo)
{
	printf("receive alarm, signo=%d\n", signo);
}

int view_jpg(char *file, int x, int y)
{
	char *buf;
	int fd, len,n;
	int vbemode;

	fd=open(file,0);
	if(fd<0){
		printf("file %s not found!\n", file);
		return -1;
	}

	len=filelength(fd);

	if((buf=malloc(len))==NULL){
		close(fd);
		printf("no memory(%s need %d bytes)!\n", file,len);
		return -1;
	}
	n=read(fd, buf, len);
	if(n<0){
		printf("no bytes read!\n", file);
		return -1;
	}
	if((vbeinit(800,600,32))==0){
		printf("can not set vesa mode!\n");
		free(buf);
		close(fd);
		return -1;
	}
	decode_jpeg(buf, len, x, y);
	free(buf);
	close(fd);
 /* Now sleep. */
  signal(SIGALRM, sigalrm);
  alarm(15);
  pause();
	SDL_vesa_stop();
	return 0;
}

load_logo()
{
	view_jpg("/system/logo.jpg", 0,0);
}


