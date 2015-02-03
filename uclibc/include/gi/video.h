


#ifndef __GI_VIDEO_H__
#define __GI_VIDEO_H__

#ifdef __cplusplus
extern "C" {
#endif


#define APM_SIGNATURE (((unsigned short)('P')<<8)|(unsigned short)('M'))

#define REAL_VM_MEM (unsigned)0X9000


typedef struct 
{
	int virtual_width,virtual_height,space;
}display_mode;

typedef struct gui_surface_t
{
	int width;
	int height;
	int depth;
	int bytesperpixel;
	unsigned long lfb_base;
	int mode_index;
	int             red_length   ;
	int             green_length ;
	int             blue_length  ;
	int             red_offset  ;
	int             green_offset;
	int             blue_offset ;
}gui_surface_t;

enum
{
	NFB_GET_ACCELERANT_SIGNATURE,
	NFB_GET_FBINFO,
	NFB_SET_FBINFO,
	//NFB_GET_MOUSEINFO,
    NFB_GET_PRIVATE_DATA,
    NFB_FIFO_START,
    NFB_FIFO_STOP,
    NFB_FIFO_SYNC,
    NFB_SET_MODE,
    NFB_MOVE_CURSOR,
    NFB_SHOW_CURSOR,
	NFB_GET_DRVINFO,
};





#ifdef __cplusplus
}
#endif
#endif


