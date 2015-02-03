#include "../../../lib/xynth_.h"
#include "server.h"
#include "../helper/helper.h"
#include "vesa.c"


struct video_driver_info video_info;

int s_video_netbas_server_init (s_server_conf_t *cfg)
{
	int err;
	//SysIoAccess(1);
	s_video_helper_mode_info_t *gmode;

	if (s_video_helper_mode_find(cfg, &gmode)) {
		debugf(DSER, "Couldn't find mode: %s", cfg->general.mode);
		return -1;
	}
//#ifndef SERVER_DISABLE_GRAPHICS
	//printf("Loading netbas driver\n");
	video_info.w = gmode->xdim ;
	video_info.h = gmode->ydim;
	video_info.dpp = gmode->bytesperpixel * 8;


	err = openvesadev(&video_info);
	if (err)
	{
		printf("%s: start %d %d %d error\n", gmode->xdim, gmode->ydim, gmode->bytesperpixel * 8);
		return -1;
	}	

	atexit(&vesa_stop);
	//VbeSetMode(BOCHS_WIDTH, BOCHS_HEIGHT, BOCHS_BPP);
//#endif

	server->window->surface->width=video_info.w ;
	server->window->surface->height=video_info.h;
	server->window->surface->bytesperpixel=video_info.dpp /8;
	server->window->surface->bitsperpixel=video_info.dpp;


	/*

	server->window->surface->colors = BOCHS_COLORS;
	server->window->surface->blueoffset = 0;
	server->window->surface->greenoffset = 8;
	server->window->surface->redoffset = 16;
	server->window->surface->bluelength = 8;
	server->window->surface->greenlength = 8;
	server->window->surface->redlength = 8;*/


                server->window->surface->blueoffset = 0;
                server->window->surface->greenoffset = 0;
                server->window->surface->redoffset = 0;
                server->window->surface->bluelength = 0;
                server->window->surface->greenlength = 0;
                server->window->surface->redlength = 0;
                server->window->surface->colors = 0;
 switch (server->window->surface->bitsperpixel) {
			case 8:
				server->window->surface->colors = 256;
				server->window->surface->bitsperpixel = 8;
				server->window->surface->blueoffset = 0;
				server->window->surface->greenoffset = 3;
				server->window->surface->redoffset = 6;
				server->window->surface->bluelength = 3;
				server->window->surface->greenlength = 3;
				server->window->surface->redlength = 2;
				break;
			case 15:
				server->window->surface->colors = 32768;
				server->window->surface->bitsperpixel = 15;
				server->window->surface->blueoffset = 0;
				server->window->surface->greenoffset = 5;
				server->window->surface->redoffset = 10;
				server->window->surface->bluelength = 5;
				server->window->surface->greenlength = 5;
				server->window->surface->redlength = 5;
				break;
			case 16:
				server->window->surface->colors = 65536;
				server->window->surface->bitsperpixel = 16;
				server->window->surface->blueoffset = 0;
				server->window->surface->greenoffset = 5;
				server->window->surface->redoffset = 11;
				server->window->surface->bluelength = 5;
				server->window->surface->greenlength = 6;
				server->window->surface->redlength = 5;
				break;
			case 24:
			case 32:
				server->window->surface->colors = 256 * 65536;
				server->window->surface->bitsperpixel = server->window->surface->bytesperpixel * 8;
				server->window->surface->blueoffset = 0;
				server->window->surface->greenoffset = 8;
				server->window->surface->redoffset = 16;
				server->window->surface->bluelength = 8;
				server->window->surface->greenlength = 8;
				server->window->surface->redlength = 8;
				break;
		}

	//int memFd=SysOpen("/System/Devices/Special/Memory",  0);

	server->window->surface->linear_mem_size=
		server->window->surface->width*server->window->surface->height*server->window->surface->bytesperpixel;
	server->window->surface->linear_buf=server->window->surface->vbuf=video_info.video_mapaddr;

		//(unsigned char*)SysMemoryMap(0, server->window->surface->linear_mem_size, 7, memFd, BOCHS_BASE);
	//server->window->surface->linear_mem_base=video_info.video_mapaddr;
	server->window->surface->linear_mem_base=video_info.share_id;
	//server->window->surface->linear_mem_base=video_info.video_phyaddr;
	//server->window->surface->linear_mem_base=BOCHS_BASE;
	printf("s_video_netbas_server_init()  phy 0x%x,window->surface->linear_buf=0x%x\n",
		server->window->surface->linear_mem_base,server->window->surface->linear_buf);

	//SysClose(memFd);

	if (!server->window->surface->vbuf)
		return -1;

	return 0;
}

void s_video_netbas_server_uninit (void)
{
}

s_video_driver_t s_video_netbas = {
	"netbas",
	"/System/Devices/Special/Memory",
	s_video_netbas_server_init,
	s_video_netbas_server_uninit,
};
