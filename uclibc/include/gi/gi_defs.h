#ifndef __GI_DEFS_H__
#define __GI_DEFS_H__

#ifndef __KERNEL__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*Êó±êÊÂ¼þ*/
enum { 
	E_MOUSE_TYPE,
	E_KEY_DOWN,
	E_KEY_UP,
};

typedef struct  {
	int what;
	int dev;
	int key;
	int modifiers;
	int x, y;
}gi_driver_event_t;

//#define MALLOC malloc
//#define FREE free
//#define EXIT exit

#define BOOL int
#endif //__KERNEL__

#define MSG_ALWAYS_WAIT (time_t)-1

#define MSG_NO_WAIT (time_t)0


#ifndef TRUE
#define TRUE			1
#endif
#ifndef FALSE
#define FALSE			0
#endif



#ifndef GI_MIN
#define GI_MIN(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);		\
	_x < _y ? _x : _y; })
#endif

#ifndef GI_MAX
#define GI_MAX(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);		\
	_x > _y ? _x : _y; })

#endif

#define GI_ARGB(a,r,g,b)	((gi_pixel_value_t)(((unsigned char)(b)|\
				(((unsigned)(unsigned char)(g))<<8))|\
				(((unsigned long)(unsigned char)(r))<<16)|\
				(((unsigned long)(unsigned char)(a))<<24)))
#define GI_RGB(r,g,b)	GI_ARGB(255,(r),(g),(b))		/* rgb full alpha*/
#define GI_0RGB(r,g,b)	GI_ARGB(0,(r),(g),(b))		/* rgb no alpha*/

#define GI_ALPHA(X) (((X)>>24)&0xff)
#define GI_RED(X) (((X)>>16)&0xff)
#define GI_GREEN(X) (((X)>>8)&0xff)
#define GI_BLUE(X) (((X))&0xff)

//#define IMAGE_WORDS(x)		(((x)+15)/16)

#define DKGRAY		GI_RGB( 32,  32,  32)
#define DESKTOP_COLOR GI_RGB(114,159,255)
#define WINDOW_COLOR GI_RGB(236, 233, 216)

//#define	IMAGE_SIZE(width, height)  ((height) * (((width) + sizeof(gi_bitmap_t) * 8 - 1) / (sizeof(gi_bitmap_t) * 8)))
#define	IMAGE_BITSPERIMAGE	(sizeof(gi_bitmap_t) * 8)
#define	IMAGE_FIRSTBIT		((gi_bitmap_t) 0x8000)
//#define	IMAGE_NEXTBIT(m)	((gi_bitmap_t) ((m) >> 1))
//#define	IMAGE_TESTBIT(m)	((m) & IMAGE_FIRSTBIT)	  /* use with shiftbit*/
//#define	IMAGE_SHIFTBIT(m)	((gi_bitmap_t) ((m) << 1))  /* for testbit*/

#define NUMBER_FONTS	3

#define	MAX_CURSOR_SIZE 64			/* maximum cursor x and y size*/
#define MAX_CHAR_HEIGHT	16			/* maximum text bitmap height*/
#define MAX_CLIP_REGIONS 64



enum{
	GI_CURSOR_ARROW = 1, 
	GI_CURSOR_IBEAM, 
	GI_CURSOR_WAIT,
	GI_CURSOR_CROSS, 
	GI_CURSOR_UPARROW, 
	GI_CURSOR_SIZENWSE,
	GI_CURSOR_SIZENESW, 
	GI_CURSOR_SIZEWE, 
	GI_CURSOR_SIZENS,
	GI_CURSOR_SIZEALL, 
	GI_CURSOR_NO, 
	GI_CURSOR_APPSTARTING,
	GI_CURSOR_HELP,
	GI_CURSOR_HAND,
	GI_CURSOR_MOVE,
	GI_CURSOR_WATCH,
	GI_CURSOR_NONE, 
	GI_CURSOR_USER0=20, 
	GI_CURSOR_MAX=32
};




#define GI_MAX_ARGS 15


#define insertQ(node_t) \
node_t *prev; \
node_t *next; 


typedef struct items_tag
{
	insertQ(struct items_tag); 
}item_base_t;

typedef struct 
{
   item_base_t *head;
   item_base_t *tail;
   int     count;
   void (*free)(item_base_t *);  //free function
}gi_lib_queue_t;



enum{
	GI_MODE_SET	=0,	
	GI_MODE_XOR	,	
	GI_MODE_INVERT	,	
	//GI_MODE_OR		,	
	//GI_MODE_AND	,	
	GI_MODE_MAX	=3,
};


/* LineStyle */

#define GI_GC_LINE_SOLID		0
#define GI_GC_LINE_ON_OFF_DASH		1
#define GI_GC_LINE_DOUBLE_DASH		2




/* capStyle */

#define GI_GC_CAP_NOT_LAST		0
#define GI_GC_CAP_BUTT			1
#define GI_GC_CAP_ROUND		2
#define GI_GC_CAP_PROJECTING		3



/* joinStyle */

#define GI_GC_JOIN_MITER		0
#define GI_GC_JOIN_ROUND		1
#define GI_GC_JOIN_BEVEL		2





/* fillStyle */

#define GI_GC_FILL_SOLID		0
#define GI_GC_FILL_TILED		1
#define GI_GC_FILL_STIPPLED		2
#define GI_GC_FILL_OPAQUE_STIPPLED	3



typedef int gi_render_id_t;

typedef int		gi_coord_t;		/* device coordinates*/
typedef int		gi_mode_t;		/* drawing mode*/
typedef unsigned long	gi_color_t;	/* device-independent color value*/
typedef unsigned int	gi_pixel_value_t;	/* pixel color value*/
typedef unsigned int	gi_mouse_button_t;		/* mouse button mask*/
typedef unsigned int	gi_key_modifier_t;	/* keyboard modifier mask (CTRL/SHIFT)*/
typedef int		gi_font_id_t;		/* font number, 0=default font*/
typedef unsigned short	gi_bitmap_t;	/* bitmap image unit size*/

#ifndef _WINDEF_H
typedef unsigned char 	gi_int8_t;		/* text buffer*/
#endif



typedef struct {
	gi_coord_t 	 scr_height;		/* number of rows on screen */
	gi_coord_t 	 scr_width;		/* number of columns on screen */
	int 	 xdpcm;		/* dots/centimeter in x direction */
	int 	 ydpcm;		/* dots/centimeter in y direction */
	uint32_t	 ncolors, format;	/* hw number of colors supported*/
	gi_pixel_value_t black;		/* hw value for black*/
	gi_pixel_value_t white;		/* hw value for white*/

	unsigned int blueoffset;
	unsigned int greenoffset;
	unsigned int redoffset;
	unsigned int bluelength;
	unsigned int greenlength;
	unsigned int redlength;
	unsigned int bluemask;
	unsigned int greenmask;
	unsigned int redmask;

	unsigned int bytesperpixel;
	unsigned int bitsperpixel;

	//gi_mouse_button_t 	 buttons;	/* buttons which are implemented */
	//gi_key_modifier_t modifiers;	/* modifiers which are implemented */
} gi_screen_info_t;

typedef struct {
	unsigned char ascent;
	unsigned char descent;
	int 	font;		/* font number */
	int 	height;		/* height of font */
	//int 	maxwidth;	/* maximum width of any char */
	int 	baseline;	/* baseline of font */
	//BOOL	fixed;		/* TRUE if font is fixed width */
	//gi_int8_t	widths[256];	/* table of character widths */
	int firstchar,lastchar,maxwidth,widths,fixed;
} gi_font_info_t;



typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} gi_rgb_t;




typedef struct {
	gi_coord_t 	x;		/* x coordinate of top left corner */
	gi_coord_t 	y;		/* y coordinate of top left corner */
	gi_coord_t 	w;		/* width of rectangle */
	gi_coord_t 	h;		/* height of rectangle */
} gi_cliprect_t;

typedef struct {
	gi_coord_t x;		/* x coordinate*/
	gi_coord_t y;		/* y coordinate*/
} gi_point_t;

typedef struct {
	gi_coord_t x;		/* x coordinate*/
	gi_coord_t y;		/* y coordinate*/
	int width;
} gi_spans_t;



typedef struct {
    gi_coord_t x1, y1, x2, y2;
} gi_boxrec_t,   *gi_boxrec_ptr_t;


/* fillRule */

#define EvenOddRule		0
#define WindingRule		1


typedef struct _g_region *gi_region_ptr_t;


/* 
 *   clip region
 */

typedef struct _g_region {
    long size;
    long numRects;
    gi_boxrec_t *rects;
    gi_boxrec_t extents;
	//gi_boxrec_t init; //need it??
} gi_region_t;



typedef struct 
{
	char gi_cliprgn_dirtychanged;
	gi_boxrec_t gi_cliprgn_area;
	gi_region_t gi_cliprgn_dirtyinverse;
}
gi_clip_region_t;

void gi_clip_region_dirty(gi_clip_region_t*clip,const gi_cliprect_t * rect, unsigned mark);
void gi_clip_region_init(gi_clip_region_t*clip, int w, int h);


#define gi_message_mouse_root_x(msg) ((msg)->params[0])
#define gi_message_mouse_root_y(msg) ((msg)->params[1])
#define gi_message_mouse_modifiers(msg) ((msg)->params[1])

#define gi_message_selection_subtype(msg) ((msg)->params[0])
#define gi_message_notify_selection_time(msg) ((msg)->params[1])
#define gi_message_notify_selection_requestor(msg) ((msg)->params[2])
#define gi_message_notify_selection_selection(msg) ((msg)->params[3])
#define gi_message_notify_selection_target(msg) ((msg)->body.message[0])
#define gi_message_notify_selection_property(msg) ((msg)->body.message[1])

#define gi_message_clear_selection_time(msg) ((msg)->params[1])
#define gi_message_clear_selection_window(msg) ((msg)->params[2])
#define gi_message_clear_selection_property(msg) ((msg)->params[3])

#define gi_message_request_selection_window(msg) ((msg)->params[1])
#define gi_message_request_selection_requestor(msg) ((msg)->params[2])
#define gi_message_request_selection_selection(msg) ((msg)->params[3])
#define gi_message_request_selection_target(msg) ((msg)->body.message[0])
#define gi_message_request_selection_property(msg) ((msg)->body.message[1])
#define gi_message_request_selection_time(msg) ((msg)->body.message[2])


#define gi_message_property_notify_state(msg) ((msg)->params[0])
#define gi_message_property_notify_atom(msg) ((msg)->params[1])
#define gi_message_property_notify_time(msg) ((msg)->params[2])


#endif /*__GI_DEFS_H__*/
