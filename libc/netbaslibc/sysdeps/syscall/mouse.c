
#define JICAMA
#include <stdio.h> /* va_list, va_start(), va_end() */
#include <netbas/netbas.h>
#include <fcntl.h>
#include <netbas/farptr.h>
#include <netbas/int86.h>

static int mfd=-1;

/* sets up the mouse driver */
int jicama_mouse_init()
{
   mfd= open("/dev/mouse",O_RDWR);
   return mfd;
}
	

/* displays the mouse pointer */
void jicama_mouse_on()
{
    netbas_ioctl(mfd,1,NULL,0);
}

/* hides the mouse pointer */
void jicama_mouse_off()
{
   netbas_ioctl(mfd, 2,NULL,0);
}

/* reads the mouse state */
void jicama_mouse_read(int *_x, int *_y, int *_botton)
{
	unsigned long arg[3];
    netbas_ioctl(mfd,3,arg,sizeof(arg)); 
	*_x=(int)arg[0];
	*_y=(int)arg[1];
	*_botton=(int)arg[2];
}

/* sets the mouse position */
void jicama_mouse_move(int _x, int _y)
{
	int _buf[2];
	_buf[0]=_x;
	_buf[1]=_y;
    netbas_ioctl(mfd,4,_buf,sizeof(_buf)); 
}



void jicama_mouse_xlimit(int _x, int _xsize)
{
	int _buf[2];
	_buf[0]=_x;
	_buf[1]=_xsize;
    netbas_ioctl(mfd,7,_buf,sizeof(_buf)); 
}

void jicama_mouse_ylimit(int _y, int _ysize)
{
	int _buf[2];
	_buf[0]=_y;
	_buf[1]=_ysize;
    netbas_ioctl(mfd,8,_buf,sizeof(_buf)); 
}

void jicama_mouse_uninstall()
{
    close(mfd); 
}



int
kbhit(void)
{
  __dpmi_regs r;

  if (_farpeekw(_dos_ds, 0x41a) == _farpeekw(_dos_ds, 0x41c))
    return 0;

  r.h.ah = 0x11;
  __dpmi_int(0x16, &r);
  if (r.x.flags & 0x40) /* Z */
    return 0;
  return 1;
}
