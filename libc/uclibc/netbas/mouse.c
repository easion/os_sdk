
#define JICAMA
#include <stdio.h> /* va_list, va_start(), va_end() */
#include <netbas/netbas.h>
#include <fcntl.h>
#include <netbas/farptr.h>
#include <netbas/int86.h>

static int mfd=-1;

/* sets up the mouse driver */
int mouse_dev_init()
{
   mfd= open("/dev/mouse",O_RDWR);
   return mfd;
}
	
#if 0
/* displays the mouse pointer */
void mouse_dev_on()
{
    ioctl(mfd,1,NULL,0);
}

/* hides the mouse pointer */
void mouse_dev_off()
{
   ioctl(mfd, 2,NULL,0);
}

/* sets the mouse position */
void mouse_dev_move(int _x, int _y)
{
	int _buf[2];
	_buf[0]=_x;
	_buf[1]=_y;
    ioctl(mfd,4,_buf,sizeof(_buf)); 
}



#endif
/* reads the mouse state */
void mouse_dev_read(int *_x, int *_y, int *_botton)
{
	unsigned long arg[3];
    ioctl(mfd,3,arg,sizeof(arg)); 
	*_x=(int)arg[0];
	*_y=(int)arg[1];
	*_botton=(int)arg[2];
}



void mouse_dev_xlimit(int _x, int _xsize)
{
	int _buf[2];
	_buf[0]=_x;
	_buf[1]=_xsize;
    ioctl(mfd,7,_buf,sizeof(_buf)); 
}

void mouse_dev_ylimit(int _y, int _ysize)
{
	int _buf[2];
	_buf[0]=_y;
	_buf[1]=_ysize;
    ioctl(mfd,8,_buf,sizeof(_buf)); 
}

void mouse_dev_uninstall()
{
    close(mfd); 
}


