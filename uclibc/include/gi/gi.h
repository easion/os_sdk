#ifndef	__GI_APP_H__
#define	__GI_APP_H__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#ifndef __KERNEL__
#include "queue.h"
#endif

#include "gi_defs.h"
#include "video.h"



typedef struct g_simple_list_t
{
	void *data;
	struct g_simple_list_t *next;
}g_simple_list_t;

typedef void     (*g_list_callback_t)          (void* data, void* user_data);

g_simple_list_t* g_simple_list_append (g_simple_list_t *list, void* data);
g_simple_list_t* g_simple_list_remove (g_simple_list_t *list, const void* data);
void g_simple_list_foreach (g_simple_list_t *list, g_list_callback_t func, void* user_data);
void g_simple_list_free (g_simple_list_t *list);



/* CoordinateMode for drawing routines */
#define GI_POLY_CoordOrigin         0       /* relative to the origin */
#define GI_POLY_CoordPrevious       1       /* relative to previous point */

/* Polygon shapes */
#define GI_SHAPE_Complex                 0       /* paths may intersect */
#define GI_SHAPE_Nonconvex               1       /* no paths intersect, but not convex */
#define GI_SHAPE_Convex                  2       /* wholly convex */

#define GI_RENDER_TYPE_OTHER	0
#define GI_RENDER_TYPE_A		1
#define GI_RENDER_TYPE_ARGB	2
#define GI_RENDER_TYPE_ABGR	3
#define GI_RENDER_TYPE_COLOR	4
#define GI_RENDER_TYPE_GRAY	5
#define GI_RENDER_TYPE_YUY2	6
#define GI_RENDER_TYPE_YV12	7
#define GI_RENDER_TYPE_BGRA	8


/*
 * While the protocol is generous in format support, the
 * sample implementation allows only packed RGB and GBR
 * representations for data to simplify software rendering,
 */
#define GI_RENDER_FORMAT(bpp,type,a,r,g,b)	(((bpp) << 24) |  \
					 ((type) << 16) | \
					 ((a) << 12) |	  \
					 ((r) << 8) |	  \
					 ((g) << 4) |	  \
					 ((b)))


#define GI_RENDER_FORMAT_BPP(f)	(((f) >> 24)       )
#define GI_RENDER_FORMAT_TYPE(f)	(((f) >> 16) & 0xff)
#define GI_RENDER_FORMAT_A(f)	(((f) >> 12) & 0x0f)
#define GI_RENDER_FORMAT_R(f)	(((f) >>  8) & 0x0f)
#define GI_RENDER_FORMAT_G(f)	(((f) >>  4) & 0x0f)
#define GI_RENDER_FORMAT_B(f)	(((f)      ) & 0x0f)
#define GI_RENDER_FORMAT_RGB(f)	(((f)      ) & 0xfff)
#define GI_RENDER_FORMAT_VIS(f)	(((f)      ) & 0xffff)
#define GI_RENDER_FORMAT_DEPTH(f)	(GI_RENDER_FORMAT_A(f) +	\
				 GI_RENDER_FORMAT_R(f) +	\
				 GI_RENDER_FORMAT_G(f) +	\
				 GI_RENDER_FORMAT_B(f))

/* 32bpp formats */
typedef enum {
	GI_RENDER_UNKNOWN = 0,
    GI_RENDER_a8r8g8b8 =	 GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ARGB,8,8,8,8),
    GI_RENDER_x8r8g8b8 =	 GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ARGB,0,8,8,8),
    GI_RENDER_a8b8g8r8 =	 GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ABGR,8,8,8,8),
    GI_RENDER_x8b8g8r8 =	 GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ABGR,0,8,8,8),
    GI_RENDER_b8g8r8a8 =	 GI_RENDER_FORMAT(32,GI_RENDER_TYPE_BGRA,8,8,8,8),
    GI_RENDER_b8g8r8x8 =	 GI_RENDER_FORMAT(32,GI_RENDER_TYPE_BGRA,0,8,8,8),
    GI_RENDER_x2r10g10b10 = GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ARGB,0,10,10,10),
    GI_RENDER_a2r10g10b10 = GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ARGB,2,10,10,10),
    GI_RENDER_x2b10g10r10 = GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ABGR,0,10,10,10),
    GI_RENDER_a2b10g10r10 = GI_RENDER_FORMAT(32,GI_RENDER_TYPE_ABGR,2,10,10,10),

/* 24bpp formats */
    GI_RENDER_r8g8b8 =	 GI_RENDER_FORMAT(24,GI_RENDER_TYPE_ARGB,0,8,8,8),
    GI_RENDER_b8g8r8 =	 GI_RENDER_FORMAT(24,GI_RENDER_TYPE_ABGR,0,8,8,8),

/* 16bpp formats */
    GI_RENDER_r5g6b5 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ARGB,0,5,6,5),
    GI_RENDER_b5g6r5 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ABGR,0,5,6,5),

    GI_RENDER_a1r5g5b5 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ARGB,1,5,5,5),
    GI_RENDER_x1r5g5b5 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ARGB,0,5,5,5),
    GI_RENDER_a1b5g5r5 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ABGR,1,5,5,5),
    GI_RENDER_x1b5g5r5 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ABGR,0,5,5,5),
    GI_RENDER_a4r4g4b4 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ARGB,4,4,4,4),
    GI_RENDER_x4r4g4b4 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ARGB,0,4,4,4),
    GI_RENDER_a4b4g4r4 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ABGR,4,4,4,4),
    GI_RENDER_x4b4g4r4 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_ABGR,0,4,4,4),

/* 8bpp formats */
    GI_RENDER_a8 =		 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_A,8,0,0,0),
    GI_RENDER_r3g3b2 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_ARGB,0,3,3,2),
    GI_RENDER_b2g3r3 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_ABGR,0,3,3,2),
    GI_RENDER_a2r2g2b2 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_ARGB,2,2,2,2),
    GI_RENDER_a2b2g2r2 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_ABGR,2,2,2,2),

    GI_RENDER_c8 =		 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_COLOR,0,0,0,0),
    GI_RENDER_g8 =		 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_GRAY,0,0,0,0),

    GI_RENDER_x4a4 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_A,4,0,0,0),

    GI_RENDER_x4c4 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_COLOR,0,0,0,0),
    GI_RENDER_x4g4 =	 GI_RENDER_FORMAT(8,GI_RENDER_TYPE_GRAY,0,0,0,0),

/* 4bpp formats */
    GI_RENDER_a4 =		 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_A,4,0,0,0),
    GI_RENDER_r1g2b1 =	 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_ARGB,0,1,2,1),
    GI_RENDER_b1g2r1 =	 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_ABGR,0,1,2,1),
    GI_RENDER_a1r1g1b1 =	 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_ARGB,1,1,1,1),
    GI_RENDER_a1b1g1r1 =	 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_ABGR,1,1,1,1),

    GI_RENDER_c4 =		 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_COLOR,0,0,0,0),
    GI_RENDER_g4 =		 GI_RENDER_FORMAT(4,GI_RENDER_TYPE_GRAY,0,0,0,0),

/* 1bpp formats */
    GI_RENDER_a1 =		 GI_RENDER_FORMAT(1,GI_RENDER_TYPE_A,1,0,0,0),

    GI_RENDER_g1 =		 GI_RENDER_FORMAT(1,GI_RENDER_TYPE_GRAY,0,0,0,0),

/* YUV formats */
    GI_RENDER_yuy2 =	 GI_RENDER_FORMAT(16,GI_RENDER_TYPE_YUY2,0,0,0,0),
    GI_RENDER_yv12 =	 GI_RENDER_FORMAT(12,GI_RENDER_TYPE_YV12,0,0,0,0)
} gi_format_code_t;



#define	GI_DESKTOP_WINDOW_ID	((gi_window_id_t) 1)


#define MAX_TITLE_BYTES 255



#define	GI_MSG_NONE				0
#define	GI_MSG_EXPOSURE			 1
#define	GI_MSG_BUTTON_DOWN		 2
#define	GI_MSG_BUTTON_UP		 3
#define	GI_MSG_MOUSE_ENTER		 4
#define	GI_MSG_MOUSE_EXIT		 5
#define	GI_MSG_CREATENOTIFY	 6
#define	GI_MSG_MOUSE_MOVE		 7
#define	GI_MSG_KEY_DOWN			 8
#define	GI_MSG_KEY_UP			 9
#define GI_MSG_KEYMAPNOTIFY			10
#define GI_MSG_GRAPHICSEXPOSURE		11
#define GI_MSG_PROPERTYNOTIFY	12
#define GI_MSG_WINDOW_HIDE	13
#define GI_MSG_WINDOW_SHOW	14
#define GI_MSG_GRAVITYNOTIFY	15
#define GI_MSG_SELECTIONNOTIFY 	16
#define GI_MSG_CONFIGURENOTIFY	17
#define GI_MSG_REPARENT 	18
#define GI_MSG_CLIENT_MSG	19
#define GI_MSG_COLORMAPNOTIFY	20
#define GI_MSG_WINDOW_DESTROY	21
#define	GI_MSG_FOCUS_IN			 22
#define	GI_MSG_FOCUS_OUT		 23
#define GI_MSG_PAINT_AREA	24


#define GI_MSG_SYSTEM_CHANGE	26
//#define GI_MSG_DOUBLE_CLICK	27



#define	GI_EVENTMASK(n)			(((gi_event_mask_t) 1) << (n))
#define	GI_MASK_ALL_EVENT		((gi_event_mask_t) -1L)

#define	GI_MASK_NONE		GI_EVENTMASK(GI_MSG_NONE)
#define	GI_MASK_EXPOSURE		(GI_EVENTMASK(GI_MSG_EXPOSURE)|GI_EVENTMASK(GI_MSG_GRAPHICSEXPOSURE))
#define	GI_MASK_GRAPHICSEXPOSURE		GI_EVENTMASK(GI_MSG_GRAPHICSEXPOSURE)
#define	GI_MASK_BUTTON_DOWN	GI_EVENTMASK(GI_MSG_BUTTON_DOWN)
#define	GI_MASK_BUTTON_UP		GI_EVENTMASK(GI_MSG_BUTTON_UP)
#define	GI_MASK_MOUSE_ENTER	GI_EVENTMASK(GI_MSG_MOUSE_ENTER)
#define	GI_MASK_MOUSE_EXIT	GI_EVENTMASK(GI_MSG_MOUSE_EXIT)
#define	GI_MASK_CREATENOTIFY	GI_EVENTMASK(GI_MSG_CREATENOTIFY)
#define	GI_MASK_MOUSE_MOVE	GI_EVENTMASK(GI_MSG_MOUSE_MOVE)
#define	GI_MASK_KEY_DOWN		GI_EVENTMASK(GI_MSG_KEY_DOWN)
#define	GI_MASK_KEY_UP		GI_EVENTMASK(GI_MSG_KEY_UP)
#define	GI_MASK_FOCUS_IN		GI_EVENTMASK(GI_MSG_FOCUS_IN)
#define	GI_MASK_FOCUS_OUT		GI_EVENTMASK(GI_MSG_FOCUS_OUT)
#define	GI_MASK_FOCUS_CHANGE	(GI_MASK_FOCUS_IN|GI_MASK_FOCUS_OUT)
#define	GI_MASK_KEYMAPNOTIFY	GI_EVENTMASK(GI_MSG_KEYMAPNOTIFY)
#define	GI_MASK_REPARENT	GI_EVENTMASK(GI_MSG_REPARENT)
#define	GI_MASK_CLIENT_MSG	GI_EVENTMASK(GI_MSG_CLIENT_MSG)
#define	GI_MASK_COLORMAPNOTIFY	GI_EVENTMASK(GI_MSG_COLORMAPNOTIFY)
#define	GI_MASK_WINDOW_DESTROY	GI_EVENTMASK(GI_MSG_WINDOW_DESTROY)
#define	GI_MASK_CONFIGURENOTIFY 	GI_EVENTMASK(GI_MSG_CONFIGURENOTIFY)
#define	GI_MASK_GRAPHICSEXPOSURE 	GI_EVENTMASK(GI_MSG_GRAPHICSEXPOSURE)
#define	GI_MASK_PROPERTYNOTIFY 	GI_EVENTMASK(GI_MSG_PROPERTYNOTIFY)
#define	GI_MASK_PAINT_AREA	GI_EVENTMASK(GI_MSG_PAINT_AREA)
#define	GI_MASK_SYSTEM_CHANGE	GI_EVENTMASK(GI_MSG_SYSTEM_CHANGE)
#define	GI_MASK_GRAVITYNOTIFY	GI_EVENTMASK(GI_MSG_GRAVITYNOTIFY)
#define	GI_MASK_SELECTIONNOTIFY	GI_EVENTMASK(GI_MSG_SELECTIONNOTIFY)
#define	GI_MASK_WINDOW_HIDE	GI_EVENTMASK(GI_MSG_WINDOW_HIDE)
#define	GI_MASK_WINDOW_SHOW	GI_EVENTMASK(GI_MSG_WINDOW_SHOW)



enum{
	GI_STRUCT_CHANGE_MOVE=1,
	GI_STRUCT_CHANGE_RESIZE,
	GI_STRUCT_CHANGE_RAISE,
	GI_STRUCT_CHANGE_LOWER,
	GI_STRUCT_REQUEST_MOVE,
	GI_STRUCT_REQUEST_RESIZE,
	GI_STRUCT_REQUEST_RAISE,
	GI_STRUCT_REQUEST_LOWER,
	GI_STRUCT_REQUEST_SHOW,
	GI_STRUCT_REQUEST_HIDE,
	GI_STRUCT_IME_SETTARGE,
	GI_STRUCT_IME_OPEN,
	GI_STRUCT_IME_CLOSE

};



/* Window properties*/
#define GI_FLAGS_NOBACKGROUND GI_EVENTMASK(1)/* */
#define GI_FLAGS_NOFOCUS	 GI_EVENTMASK(2) /* */
#define GI_FLAGS_NOMOVE	 GI_EVENTMASK(3) /* */
#define GI_FLAGS_NORAISE	 GI_EVENTMASK(4) /* */
#define GI_FLAGS_NON_FRAME	 GI_EVENTMASK(5) /* */
#define GI_FLAGS_CHILD	 GI_EVENTMASK(6) /* */
#define GI_FLAGS_NORESIZE GI_EVENTMASK(7) /* */
#define GI_FLAGS_HAS_IME GI_EVENTMASK(8) /* */
#define GI_FLAGS_WM_WINDOW GI_EVENTMASK(9) /* */
#define GI_FLAGS_TRAY_WINDOW GI_EVENTMASK(10) /* */
#define GI_FLAGS_SELF_MOUSE GI_EVENTMASK(11) /*用自身的鼠标 */
#define GI_FLAGS_TEMP_WINDOW GI_EVENTMASK(12) /*不在任务栏显示的窗体 */
#define GI_FLAGS_DESKTOP_WINDOW GI_EVENTMASK(13) /* */
#define GI_FLAGS_LOWEST_WINDOW GI_EVENTMASK(14) /* */
#define GI_FLAGS_TOPMOST_WINDOW GI_EVENTMASK(15) /* */
#define GI_FLAGS_TASKBAR_WINDOW GI_EVENTMASK(16) /* */
#define GI_FLAGS_MENU_WINDOW GI_EVENTMASK(17) /* */
#define GI_FLAGS_OVERRIDE_REDIRECT GI_EVENTMASK(20) /* */
#define GI_FLAGS_TRANSPARENT GI_EVENTMASK(21)
#define GI_FLAGS_DOUBLE_BUFFER GI_EVENTMASK(22)
#define GI_FLAGS_MASK 0xffffffffL /* Don't resize window on 1st map*/



enum {
  GI_BUTTON_L			= ( 0x01),	/* left button */
  GI_BUTTON_M			= ( 0x02),	/* middle button*/
  GI_BUTTON_R			= ( 0x04), 	/* right button*/
  GI_BUTTON_WHEEL_UP	= ( 0x08), 	/* whell up button*/
  GI_BUTTON_WHEEL_DOWN	= ( 0x10), 	/* whell down button*/
  GI_BUTTON_WHEEL_LEFT	= ( 0x20), 	/* whell left button*/
  GI_BUTTON_WHEEL_RIGHT	= ( 0x40), 	/* whell right button*/

  G_MODIFIERS_LSHIFT	= ( 1 << 16 ),
  G_MODIFIERS_RSHIFT	= ( 1 << 17 ),
  G_MODIFIERS_LCTRL		= ( 1 << 18 ),
  G_MODIFIERS_RCTRL		= ( 1 << 19 ),
  G_MODIFIERS_LALT		= ( 1 << 20 ),
  G_MODIFIERS_RALT		= ( 1 << 21),
  G_MODIFIERS_CAPSLOCK	= ( 1 << 22 ),
  G_MODIFIERS_SCRLOCK	= ( 1 << 23 ),
  G_MODIFIERS_NUMLOCK	= ( 1 << 24 ),
  G_MODIFIERS_LMETA		= ( 1 << 25 ),
  G_MODIFIERS_RMETA		= ( 1 << 26 )
};

#define G_MODIFIERS_SHIFT ( G_MODIFIERS_LSHIFT | G_MODIFIERS_RSHIFT )
#define G_MODIFIERS_CTRL  ( G_MODIFIERS_LCTRL | G_MODIFIERS_RCTRL )
#define G_MODIFIERS_ALT   ( G_MODIFIERS_LALT | G_MODIFIERS_RALT )
#define G_MODIFIERS_META   ( G_MODIFIERS_LMETA | G_MODIFIERS_RMETA )


#define	GI_BUTTON_ANY	((gi_mouse_button_t) RBUTTON|MBUTTON|LBUTTON) /* any button*/

enum{
	GI_BG_USE_COLOR,
	GI_BG_USE_PIXMAP,
	GI_BG_USE_TILE,
	GI_BG_USE_NONE,
	GI_BG_USE_ROOT,
};



#define GIX_PROTOCOL_VERSION(major,minor) ((major)<<8 | (minor))

struct gix_kernel_version {
        /* driver protocol version -- increment with incompatible change */
        uint16_t     protocol_version;
        uint16_t     capability;
        uint32_t     reserve;
};

int gi_get_kernel_version(struct gix_kernel_version *ver);

typedef int 		gi_int_t;	/* number of items */
typedef uint32_t gi_id_t;	/* resource ids */
typedef gi_id_t gi_window_id_t;/* window id */
typedef gi_id_t gi_gc_id_t;		/* graphics context id */
typedef unsigned short gi_bool_t;	/* boolean value */
typedef unsigned char gi_event_type_t;	/* event types */
typedef unsigned long gi_event_mask_t;	/* event masks */
typedef unsigned long gi_para_t;
//typedef int gi_region_id_t;


typedef struct {
	int function;		/* logical operation */
	unsigned long plane_mask;/* plane mask */
	unsigned long foreground;/* foreground pixel */
	unsigned long background;/* background pixel */
	int line_width;		/* line width */
	int line_style;	 	/* LineSolid, LineOnOffDash, LineDoubleDash */
	int cap_style;	  	/* CapNotLast, CapButt, 
				   CapRound, CapProjecting */
	int join_style;	 	/* JoinMiter, JoinRound, JoinBevel */
	int fill_style;	 	/* FillSolid, FillTiled, 
				   FillStippled, FillOpaeueStippled */
	int fill_rule;	  	/* EvenOddRule, WindingRule */
	int arc_mode;		/* ArcChord, ArcPieSlice */
	gi_window_id_t tile;		/* tile pixmap for tiling operations */
	gi_window_id_t stipple;		/* stipple 1 plane pixmap for stipping */
	int ts_x_origin;	/* offset for tile or stipple operations */
	int ts_y_origin;
    void* font;	        /* default text font for text operations */
	int subwindow_mode;     /* ClipByChildren, IncludeInferiors */
	gi_bool_t graphics_exposures;/* boolean, should exposures be generated */
	int clip_x_origin;	/* origin for clipping */
	int clip_y_origin;
	gi_window_id_t clip_mask;	/* bitmap clipping; other calls for rects */
	int dash_offset;	/* patterned/dashed line information */
	char dash_list_len;
	//unsigned short	dashOffset;
    //unsigned short	numInDashList;
    unsigned char	*dash_list;

} gi_gc_values_t;

typedef struct _gc_struct
{
    void *ext_data; /* hook for extension to hang data */
    gi_gc_id_t gcid;       /* protocol ID for graphics context */
	gi_window_id_t winid;
    gi_bool_t rects;         /* boolean: TRUE if clipmask is list of rectangles */
    //gi_bool_t dashes;        /* boolean: TRUE if dash-list is really a list */
    unsigned long dirty;/* cache dirty bits */
    gi_gc_values_t values;   /* shadow structure of values */
    /* there is more to this structure, but it is private to Xlib */
}
*gi_gc_ptr_t;

/** surface struct
  */
struct surface_struct {
	
	/** surface bits per pixel */
	unsigned short bytesperpixel;
	unsigned short bitsperpixel;
	
	/** blue color offset */
	unsigned int blueoffset;
	/** green color offset */
	unsigned int greenoffset;
	/** red color offset */
	unsigned int redoffset;
	/** blue color length */
	unsigned int bluelength;
	/** green color length */
	unsigned int greenlength;
	/** red color length */
	unsigned int redlength;
	/** blue color mask */
	unsigned int bluemask;
	/** green color mask */
	unsigned int greenmask;
	/** red color mask */
	unsigned int redmask;
};


typedef struct 
{
	int w, h;
	gi_color_t *rgba;
	uint32_t format;
	unsigned int pitch;
	struct surface_struct s;
	int refs; //引用计数
}
gi_image_t;

gi_color_t gi_surface_rgb_color (struct surface_struct * surface, int r, int g, int b);


typedef enum {PM_NOREMOVE,PM_REMOVE}event_peek_t;




typedef struct {
  gi_window_id_t windowid;		
  gi_window_id_t parent;		
  gi_window_id_t child;		
  gi_window_id_t bottom_id;		
  gi_window_id_t above_id;		
  gi_bool_t mapped;		
  gi_coord_t x;			
  gi_coord_t y;			
  gi_coord_t width;		
  gi_coord_t height;		
  gi_color_t background;		
  gi_event_mask_t eventmask;	
  unsigned long flags;
  uint32_t format;
  uint16_t type;
  uint16_t res1;
  gi_window_id_t pixmap;
  long res[4];
  //gi_bool_t iconified;
} gi_window_info_t;

typedef struct {
  gi_gc_id_t gcid;		
  gi_color_t foreground, background;		
  gi_mode_t mode;			
  gi_bool_t usebackground;	
  gi_window_id_t window;
  int function;
  int line_width;
  int gc_xoff,gc_yoff;
} gi_gc_info_t;



#define MAX_EVENT_PARAMS 4

typedef struct gi_msg_t
{
  gi_event_type_t type;		/**< event type */
  unsigned char client_sent:1;
  unsigned char  attribute_1:1;
  unsigned char  attribute_2:1;
  unsigned char  attribute_3:1;
  unsigned char  attribute_4:4;
  gi_window_id_t ev_window;		/** window id*/
  gi_window_id_t effect_window;		/***/
  uint32_t params[MAX_EVENT_PARAMS]; 

  union{	  
	  gi_cliprect_t rect;	 
	  uint32_t message[4];	  
	  uint16_t message16[8];	  
	  uint8_t message8[16];	  
	  struct 
	  {
		uint8_t client_message[6];
		gi_id_t client_param;
		uint8_t client_other;
		uint8_t client_format;
		gi_id_t client_type;		
	  }__attribute__((packed)) client;
  }body;

  unsigned time;
}__attribute__((packed)) gi_msg_t;

typedef enum {
        /** @name ASCII mapped keysyms
         *  The keyboard syms have been cleverly chosen to map to ASCII
         */
        /*@{*/
	G_KEY_UNKNOWN		= 0,
	G_KEY_FIRST		= 0,
	G_KEY_BACKSPACE		= 8,
	G_KEY_TAB		= 9,
	G_KEY_ENTER		= 10,
	G_KEY_CLEAR		= 12,
	G_KEY_RETURN		= 13,
	G_KEY_PAUSE		= 19,
	G_KEY_ESCAPE		= 27,
	G_KEY_SPACE		= 32,
	G_KEY_EXCLAIM		= 33,
	G_KEY_QUOTEDBL		= 34,
	G_KEY_HASH		= 35,
	G_KEY_DOLLAR		= 36,
	G_KEY_AMPERSAND		= 38,
	G_KEY_QUOTE		= 39,
	G_KEY_LEFTPAREN		= 40,
	G_KEY_RIGHTPAREN		= 41,
	G_KEY_ASTERISK		= 42,
	G_KEY_PLUS		= 43,
	G_KEY_COMMA		= 44,
	G_KEY_MINUS		= 45,
	G_KEY_PERIOD		= 46,
	G_KEY_SLASH		= 47,
	G_KEY_0			= 48,
	G_KEY_1			= 49,
	G_KEY_2			= 50,
	G_KEY_3			= 51,
	G_KEY_4			= 52,
	G_KEY_5			= 53,
	G_KEY_6			= 54,
	G_KEY_7			= 55,
	G_KEY_8			= 56,
	G_KEY_9			= 57,
	G_KEY_COLON		= 58,
	G_KEY_SEMICOLON		= 59,
	G_KEY_LESS		= 60,
	G_KEY_EQUALS		= 61,
	G_KEY_GREATER		= 62,
	G_KEY_QUESTION		= 63,
	G_KEY_AT			= 64,
	/* 
	   Skip uppercase letters
	 */
	G_KEY_LEFTBRACKET	= 91,
	G_KEY_BACKSLASH		= 92,
	G_KEY_RIGHTBRACKET	= 93,
	G_KEY_CARET		= 94,
	G_KEY_UNDERSCORE		= 95,
	G_KEY_BACKQUOTE		= 96,
	G_KEY_a			= 97,
	G_KEY_b			= 98,
	G_KEY_c			= 99,
	G_KEY_d			= 100,
	G_KEY_e			= 101,
	G_KEY_f			= 102,
	G_KEY_g			= 103,
	G_KEY_h			= 104,
	G_KEY_i			= 105,
	G_KEY_j			= 106,
	G_KEY_k			= 107,
	G_KEY_l			= 108,
	G_KEY_m			= 109,
	G_KEY_n			= 110,
	G_KEY_o			= 111,
	G_KEY_p			= 112,
	G_KEY_q			= 113,
	G_KEY_r			= 114,
	G_KEY_s			= 115,
	G_KEY_t			= 116,
	G_KEY_u			= 117,
	G_KEY_v			= 118,
	G_KEY_w			= 119,
	G_KEY_x			= 120,
	G_KEY_y			= 121,
	G_KEY_z			= 122,
	G_KEY_DELETE		= 127,
	/* End of ASCII mapped keysyms */
        /*@}*/

	/** @name International keyboard syms */
        /*@{*/
	G_KEY_WORLD_0		= 160,		/* 0xA0 */
	G_KEY_WORLD_1		= 161,
	G_KEY_WORLD_2		= 162,
	G_KEY_WORLD_3		= 163,
	G_KEY_WORLD_4		= 164,
	G_KEY_WORLD_5		= 165,
	G_KEY_WORLD_6		= 166,
	G_KEY_WORLD_7		= 167,
	G_KEY_WORLD_8		= 168,
	G_KEY_WORLD_9		= 169,
	G_KEY_WORLD_10		= 170,
	G_KEY_WORLD_11		= 171,
	G_KEY_WORLD_12		= 172,
	G_KEY_WORLD_13		= 173,
	G_KEY_WORLD_14		= 174,
	G_KEY_WORLD_15		= 175,
	G_KEY_WORLD_16		= 176,
	G_KEY_WORLD_17		= 177,
	G_KEY_WORLD_18		= 178,
	G_KEY_WORLD_19		= 179,
	G_KEY_WORLD_20		= 180,
	G_KEY_WORLD_21		= 181,
	G_KEY_WORLD_22		= 182,
	G_KEY_WORLD_23		= 183,
	G_KEY_WORLD_24		= 184,
	G_KEY_WORLD_25		= 185,
	G_KEY_WORLD_26		= 186,
	G_KEY_WORLD_27		= 187,
	G_KEY_WORLD_28		= 188,
	G_KEY_WORLD_29		= 189,
	G_KEY_WORLD_30		= 190,
	G_KEY_WORLD_31		= 191,
	G_KEY_WORLD_32		= 192,
	G_KEY_WORLD_33		= 193,
	G_KEY_WORLD_34		= 194,
	G_KEY_WORLD_35		= 195,
	G_KEY_WORLD_36		= 196,
	G_KEY_WORLD_37		= 197,
	G_KEY_WORLD_38		= 198,
	G_KEY_WORLD_39		= 199,
	G_KEY_WORLD_40		= 200,
	G_KEY_WORLD_41		= 201,
	G_KEY_WORLD_42		= 202,
	G_KEY_WORLD_43		= 203,
	G_KEY_WORLD_44		= 204,
	G_KEY_WORLD_45		= 205,
	G_KEY_WORLD_46		= 206,
	G_KEY_WORLD_47		= 207,
	G_KEY_WORLD_48		= 208,
	G_KEY_WORLD_49		= 209,
	G_KEY_WORLD_50		= 210,
	G_KEY_WORLD_51		= 211,
	G_KEY_WORLD_52		= 212,
	G_KEY_WORLD_53		= 213,
	G_KEY_WORLD_54		= 214,
	G_KEY_WORLD_55		= 215,
	G_KEY_WORLD_56		= 216,
	G_KEY_WORLD_57		= 217,
	G_KEY_WORLD_58		= 218,
	G_KEY_WORLD_59		= 219,
	G_KEY_WORLD_60		= 220,
	G_KEY_WORLD_61		= 221,
	G_KEY_WORLD_62		= 222,
	G_KEY_WORLD_63		= 223,
	G_KEY_WORLD_64		= 224,
	G_KEY_WORLD_65		= 225,
	G_KEY_WORLD_66		= 226,
	G_KEY_WORLD_67		= 227,
	G_KEY_WORLD_68		= 228,
	G_KEY_WORLD_69		= 229,
	G_KEY_WORLD_70		= 230,
	G_KEY_WORLD_71		= 231,
	G_KEY_WORLD_72		= 232,
	G_KEY_WORLD_73		= 233,
	G_KEY_WORLD_74		= 234,
	G_KEY_WORLD_75		= 235,
	G_KEY_WORLD_76		= 236,
	G_KEY_WORLD_77		= 237,
	G_KEY_WORLD_78		= 238,
	G_KEY_WORLD_79		= 239,
	G_KEY_WORLD_80		= 240,
	G_KEY_WORLD_81		= 241,
	G_KEY_WORLD_82		= 242,
	G_KEY_WORLD_83		= 243,
	G_KEY_WORLD_84		= 244,
	G_KEY_WORLD_85		= 245,
	G_KEY_WORLD_86		= 246,
	G_KEY_WORLD_87		= 247,
	G_KEY_WORLD_88		= 248,
	G_KEY_WORLD_89		= 249,
	G_KEY_WORLD_90		= 250,
	G_KEY_WORLD_91		= 251,
	G_KEY_WORLD_92		= 252,
	G_KEY_WORLD_93		= 253,
	G_KEY_WORLD_94		= 254,
	G_KEY_WORLD_95		= 255,		/* 0xFF */
        /*@}*/

	/** @name Numeric keypad */
        /*@{*/
	G_KEY_KP0		= 256,
	G_KEY_KP1		= 257,
	G_KEY_KP2		= 258,
	G_KEY_KP3		= 259,
	G_KEY_KP4		= 260,
	G_KEY_KP5		= 261,
	G_KEY_KP6		= 262,
	G_KEY_KP7		= 263,
	G_KEY_KP8		= 264,
	G_KEY_KP9		= 265,
	G_KEY_KP_PERIOD		= 266,
	G_KEY_KP_DIVIDE		= 267,
	G_KEY_KP_MULTIPLY	= 268,
	G_KEY_KP_MINUS		= 269,
	G_KEY_KP_PLUS		= 270,
	G_KEY_KP_ENTER		= 271,
	G_KEY_KP_EQUALS		= 272,
        /*@}*/

	/** @name Arrows + Home/End pad */
        /*@{*/
	G_KEY_UP			= 273,
	G_KEY_DOWN		= 274,
	G_KEY_RIGHT		= 275,
	G_KEY_LEFT		= 276,
	G_KEY_INSERT		= 277,
	G_KEY_HOME		= 278,
	G_KEY_END		= 279,
	G_KEY_PAGEUP		= 280,
	G_KEY_PAGEDOWN		= 281,
        /*@}*/

	/** @name Function keys */
        /*@{*/
	G_KEY_F1			= 282,
	G_KEY_F2			= 283,
	G_KEY_F3			= 284,
	G_KEY_F4			= 285,
	G_KEY_F5			= 286,
	G_KEY_F6			= 287,
	G_KEY_F7			= 288,
	G_KEY_F8			= 289,
	G_KEY_F9			= 290,
	G_KEY_F10		= 291,
	G_KEY_F11		= 292,
	G_KEY_F12		= 293,
	G_KEY_F13		= 294,
	G_KEY_F14		= 295,
	G_KEY_F15		= 296,
        /*@}*/

	/** @name Key state modifier keys */
        /*@{*/
	G_KEY_NUMLOCK		= 300,
	G_KEY_CAPSLOCK		= 301,
	G_KEY_SCROLLOCK		= 302,
	G_KEY_RSHIFT		= 303,
	G_KEY_LSHIFT		= 304,
	G_KEY_RCTRL		= 305,
	G_KEY_LCTRL		= 306,
	G_KEY_RALT		= 307,
	G_KEY_LALT		= 308,
	G_KEY_RMETA		= 309,
	G_KEY_LMETA		= 310,
	G_KEY_LSUPER		= 311,		/**< Left "Windows" key */
	G_KEY_RSUPER		= 312,		/**< Right "Windows" key */
	G_KEY_MODE		= 313,		/**< "Alt Gr" key */
	G_KEY_COMPOSE		= 314,		/**< Multi-key compose key */
        /*@}*/

	/** @name Miscellaneous function keys */
        /*@{*/
	G_KEY_HELP		= 315,
	G_KEY_PRINT		= 316,
	G_KEY_SYSREQ		= 317,
	G_KEY_BREAK		= 318,
	G_KEY_MENU		= 319,
	G_KEY_POWER		= 320,		/**< Power Macintosh power key */
	G_KEY_EURO		= 321,		/**< Some european keyboards */
	G_KEY_UNDO		= 322,		/**< Atari keyboard has Undo */
        /*@}*/

	/* Add any other keys here */

	G_KEY_LAST
} gi_keycode_t;



typedef struct _gi_arc_t {
    gi_int_t x , y ;
    gi_int_t   width , height ;
    gi_int_t   angle1 , angle2 ;
} gi_arc_t;

int gi_set_touch_matrix(void *ts, int size);

int gi_register_input(int sock,void (*callback)(int fd, void *param,long type),void *data);
int gi_unregister_input(int sock);

int gi_fill_arcs( gi_window_id_t pDraw, gi_gc_ptr_t pGC, gi_arc_t *parcs, int narcs);
int gi_draw_arcs(  gi_window_id_t d, gi_gc_ptr_t gc, gi_arc_t *parcs, int narcs);

typedef gi_bool_t (*g_if_event_callback)(gi_window_id_t, gi_event_mask_t,
				 gi_msg_t *, void *);
int gi_get_typed_event_pred(gi_window_id_t wid, gi_event_mask_t mask, 
	gi_msg_t *ep, gi_bool_t block, g_if_event_callback matchfn, void *arg);
void gi_push_message_cache(gi_msg_t *ep);
int gi_get_event_count(void);
int gi_event_poll(gi_msg_t *ep, time_t timeout );
int gi_next_message(gi_msg_t *ep);
int gi_get_event_cached(gi_bool_t cache_now);

int gi_screen_height(void);
int gi_screen_width(void);
unsigned gi_screen_format(void);
int gi_get_connection_fd(void);
int gi_query_pointer(gi_window_id_t wid, gi_window_id_t *child, int *rootx, int *rooty, 
  gi_coord_t *x, gi_coord_t *y, unsigned int *mask);
int gi_get_mouse_pos(gi_window_id_t wid,gi_window_id_t *ret,  gi_coord_t *x, gi_coord_t *y);
int gi_query_child_tree(gi_window_id_t wid, gi_window_id_t *parentid, gi_window_id_t **children,
	int *nchildren);
gi_bool_t gi_translate_coordinates(
  gi_window_id_t src_w, gi_window_id_t dest_w,  int src_x, int src_y, 
  int *dest_x_return, int *dest_y_return, gi_window_id_t *child_return);

int gi_beep(int pitch, int duration);
int gi_restack_windows (gi_window_id_t* windows, int n);
int gi_get_system_path(char *path, int len, const char *fmt, ...);

#ifndef __KERNEL__

//#include <wctype.h>
//#include <wchar.h>
typedef uint32_t gi_wchar_t;

int gi_post_keyboard_event(long mod, int key, gi_bool_t down, gi_bool_t skip_grab);
int gi_post_mouse_event(int x, int y, unsigned long buttons);
int gi_post_wc_string(gi_window_id_t window, gi_wchar_t *str, 
	int len, gi_msg_t *event, gi_bool_t is_char);

int gi_register_hotkey(gi_window_id_t window, long flags, int key);
int gi_unregister_hotkey(int keyid);

#endif

int		gi_init(void);
int		gi_exit(void);
int gi_set_window_caption(gi_window_id_t window, const char *text);
int gi_set_window_icon_name(gi_window_id_t window, const char *title);
int gi_set_window_opacity(gi_window_id_t window, uint8_t opacity);
int gi_set_window_command(gi_window_id_t window, char *command) ;

int gi_set_window_utf8_caption(gi_window_id_t window, const char *title);
int gi_set_window_desc(gi_window_id_t window, const char *text);
int gi_set_window_icon(gi_window_id_t window, uint32_t *data, int w, int h);
gi_image_t* gi_create_image(int w, int h);
gi_window_id_t gi_create_pixmap_window(gi_window_id_t win, 
	gi_coord_t width, gi_coord_t height, uint32_t format);

gi_window_id_t gi_create_pixmap_share(gi_window_id_t win, 
	gi_coord_t width, gi_coord_t height, uint32_t format, int pitch);

int gi_set_dashes(gi_gc_ptr_t gc,unsigned offset, unsigned ndash, const char *pdash);
int gi_set_line_attributes(gi_gc_ptr_t gc, unsigned linewidth, int linestyle, int capstyle, int joinstyle);
int gi_set_arcmode ( gi_gc_ptr_t gc,int arc_mode);
int gi_set_linewidth ( gi_gc_ptr_t gc,int line_width);
int gi_set_joinstyle ( gi_gc_ptr_t gc,int join_style);
int gi_set_capstyle ( gi_gc_ptr_t gc,int cap_style);
int gi_set_linestyle ( gi_gc_ptr_t gc,int line_style);
int gi_set_fillstyle ( gi_gc_ptr_t gc,int fill_style);

int gi_set_window_background(gi_window_id_t window,  gi_color_t c, int use_pixmap);
int gi_set_window_flags(gi_window_id_t wid, long flags);
int gi_set_window_pixmap(gi_window_id_t wid, const gi_window_id_t id,  int flags);
int gi_set_window_surface(gi_window_id_t wid, const gi_window_id_t id);
int		gi_get_screen_info(gi_screen_info_t *sip);
void gi_arc_angle(gi_gc_ptr_t psd, int x0, int y0, int rx, int ry,
	int angle1, int angle2, int type);
int
gi_draw_arc(  gi_window_id_t d,    gi_gc_ptr_t gc,    int x, int y, unsigned int	width,
    unsigned int height,    int angle1,    int angle2);

int gi_fill_arc( gi_window_id_t d, gi_gc_ptr_t gc, int x, int y, unsigned int width, unsigned int height, int angle1, int angle2);

int gi_fill_polygon(gi_gc_ptr_t gcid, gi_point_t *points, int n_points, int shape, int mode);

gi_window_id_t	gi_create_window(gi_window_id_t parent, gi_coord_t x, gi_coord_t y,
			gi_coord_t width, gi_coord_t height, gi_color_t background, long fl);

gi_window_id_t	gi_create_input_window(gi_window_id_t parent, gi_coord_t x, gi_coord_t y,
				gi_coord_t width, gi_coord_t height);

int		gi_destroy_window(gi_window_id_t window);
int gi_destroy_pixmap(gi_window_id_t id);

int gi_load_cursor(gi_window_id_t wid,  int cursor);
int gi_setup_cursor(int type,  gi_coord_t hotx,	gi_coord_t hoty,  gi_image_t *image);
int gi_create_cursor_image(gi_window_id_t wid, int x, int y, gi_image_t* img);


gi_gc_ptr_t	gi_create_gc(gi_window_id_t, gi_gc_values_t*val);
gi_gc_ptr_t gi_dup_gc(gi_gc_ptr_t gc);
gi_region_t*gi_create_region_from_pixmap(gi_window_id_t src, int x, int y, int width,	int height);
int gi_gc_set_clip_origin(  gi_gc_ptr_t pGC,int x, int y);
int gi_destroy_font(int font);
int gi_gc_set_expose(gi_gc_ptr_t pGC, gi_bool_t on);
int gi_change_gc(gi_gc_ptr_t pGC, uint32_t mask, uint32_t *pval, int size);


int		gi_get_gc_info(gi_gc_ptr_t gc, gi_gc_info_t *gcip);
int		gi_destroy_gc(gi_gc_ptr_t gc);
uint32_t gi_get_choose_format(int depth);

void gi_pixel_to_color(gi_screen_info_t *surface, gi_color_t c,int *red, int *green, int *blue) ;
gi_color_t gi_color_to_pixel(gi_screen_info_t *surface, int r,int g, int b) ;


int gi_image_create_from_jpeg(const char *path,gi_image_t **bmp);
int gi_image_create_from_png (const char *file, gi_image_t **pimg);
gi_image_t *gi_image_create_from_ico (char *file);

gi_image_t* gi_bitmap_resize(gi_image_t* bmp_from, int width, int height, uint32_t format);
int gi_bitmap_copy_wh(gi_image_t *mapto, int to_x, int to_y,
  gi_image_t *mapfrom, int from_x, int from_y, int w, int h);
gi_color_t gi_image_getpixel(const gi_image_t * bitmap, int x1, int y1);
void gi_image_putpixel(gi_image_t * bitmap, int x1, int y1, gi_color_t color);
gi_image_t *gi_get_window_image(gi_window_id_t win, int x, int y,int width, int height,uint32_t  format,int bg, void *mem);
int gi_get_window_buffer(gi_window_id_t win, int x, int y,int width, int height,int bg,uint32_t  format, void *mem);
int gi_copy_area( gi_window_id_t src_drawable, gi_gc_ptr_t gc, int src_x, int src_y, unsigned int width,
     unsigned int height, int dst_x, int dst_y);
gi_image_t* gi_create_image_with_pitch(int w, int h, uint32_t fmt, int pitch);
gi_image_t* gi_create_image_with_param(int w, int h, gi_format_code_t fmt, void *rgba, int pitch);

int gi_show_window_all(gi_window_id_t wid);
int gi_hide_window_all(gi_window_id_t wid);
int		gi_show_window(gi_window_id_t window);
int		gi_hide_window(gi_window_id_t window);
int		gi_raise_window(gi_window_id_t window);
int		gi_lower_window(gi_window_id_t window);
int		gi_move_window(gi_window_id_t window, gi_coord_t x, gi_coord_t y);
int		gi_resize_window(gi_window_id_t window, gi_coord_t width, gi_coord_t height);
int gi_move_resize_window(gi_window_id_t wid,int x, int y, gi_coord_t width, gi_coord_t height);
int		gi_get_window_info(gi_window_id_t window, gi_window_info_t *infoptr);
int		gi_get_font_info(gi_font_id_t font, gi_font_info_t *fip);
int gi_reparent_window(gi_window_id_t window, gi_window_id_t pwid, gi_coord_t x, gi_coord_t y);
int		gi_set_focus_window(gi_window_id_t window);
gi_window_id_t gi_get_focus_window(int toplevel);

int		gi_clear_window(gi_window_id_t window, gi_bool_t exposeflag);
int		gi_set_events_mask(gi_window_id_t window, gi_event_mask_t eventmask);
int		gi_get_message(gi_msg_t *ep, time_t t);
int gi_check_typed_message(gi_msg_t *ep,gi_window_id_t window,long event_mask);
int		gi_check_next_message(gi_msg_t *ep);
int gi_send_event(gi_window_id_t w,  gi_bool_t propagate,   long event_mask, gi_msg_t *event);
int gi_peek_message(gi_msg_t *ep);


void *gi_dispatch_get_param(gi_window_id_t winid);
int		gi_dispatch_message(gi_msg_t *ep);
gi_bool_t gi_get_new_message(gi_msg_t *event);
void gi_quit_dispatch(void);
int gi_set_dispatch_handler(gi_window_id_t winid,int (*handler)(gi_msg_t *event,void *data), void *data);
int gi_remove_dispatch_handler(gi_window_id_t winid);
void gi_dispatch_foreach ( g_list_callback_t func, void* user_data);
int gi_default_handler(gi_msg_t *event,void *data);
void *gi_dispatch_get_param(gi_window_id_t winid);


int		gi_flush(void);
int gi_draw_lines (gi_gc_ptr_t  gc, gi_point_t *points, int npoints);
int		gi_draw_line(gi_gc_ptr_t gc, gi_coord_t x1, gi_coord_t y1,
			gi_coord_t x2, gi_coord_t y2);
int		gi_set_pixel(gi_gc_ptr_t gc, gi_coord_t x, gi_coord_t y);
int		gi_draw_rect(gi_gc_ptr_t gc, gi_coord_t x, gi_coord_t y,
			gi_coord_t width, gi_coord_t height);
int		gi_fill_rect(gi_gc_ptr_t gc, gi_coord_t x, gi_coord_t y,
			gi_coord_t width, gi_coord_t height);
int		gi_poly(gi_gc_ptr_t gc, gi_int_t count,
			gi_point_t *pointtable);
int		gi_fill_poly(gi_gc_ptr_t gc, gi_int_t count,
			gi_point_t *pointtable);
int		gi_ellipse(gi_gc_ptr_t gc, gi_coord_t x, gi_coord_t y,
			gi_coord_t rx, gi_coord_t ry);
int		gi_fill_ellipse(gi_gc_ptr_t gc, gi_coord_t x,
			gi_coord_t y, gi_coord_t rx, gi_coord_t ry);
int gi_set_gc_clip_rectangles(  gi_gc_ptr_t gc, gi_boxrec_t * r , int num);
int gi_set_window_clip_rectangles(gi_window_id_t wid, gi_boxrec_t * r , int num, int redraw);

int gi_set_gc_foreground_pixel(gi_gc_ptr_t gc,  gi_color_t foreground);
int gi_set_gc_background_pixel(gi_gc_ptr_t gc, gi_color_t background);
int gi_set_gc_function(gi_gc_ptr_t gc, gi_mode_t mode);
int gi_create_kernel_font(const char *fontname);

int gi_parse_color (const char *name, gi_color_t *color);

int		gi_set_gc_foreground(gi_gc_ptr_t gc, gi_color_t foreground);
int		gi_set_gc_background(gi_gc_ptr_t gc, gi_color_t background);
int		gi_set_gc_background_flags(gi_gc_ptr_t gc, gi_bool_t flag);

int		gi_set_gc_font(gi_gc_ptr_t gc, gi_font_id_t font);
int		gi_get_string_size(gi_gc_ptr_t gc, gi_int8_t *cp, gi_coord_t len,
			gi_coord_t *retwidth, gi_coord_t *retheight,gi_coord_t *retbase);
int		gi_area_save(gi_window_id_t id, gi_coord_t x, gi_coord_t y, gi_coord_t width,
			gi_coord_t height, gi_pixel_value_t *pixels);
int		gi_draw_bitmap(gi_gc_ptr_t gc, gi_coord_t x, gi_coord_t y,
			gi_coord_t width, gi_coord_t height, gi_bitmap_t *imagebits);
int		gi_draw_string(gi_gc_ptr_t gc,int font, gi_coord_t x, gi_coord_t y,
			gi_int8_t *str, gi_int_t count);
int gi_set_cursor(gi_window_id_t window,  gi_coord_t hotx,	gi_coord_t hoty,  gi_image_t *image);
int		gi_move_cursor(gi_coord_t x, gi_coord_t y);
int gi_batch_blit(gi_gc_ptr_t gc, gi_image_t *image,gi_cliprect_t *region, 	int count, gi_coord_t x2, gi_coord_t y2);
int gi_bitblt_image(gi_gc_ptr_t gc, 
	gi_coord_t x, gi_coord_t y, gi_coord_t width, gi_coord_t height,
	gi_image_t *bitmaptable, gi_coord_t x2, gi_coord_t y2);
int gi_bitblt_raw_bitmap(gi_gc_ptr_t gc, gi_coord_t x, gi_coord_t y, gi_coord_t width, gi_coord_t height,
		gi_image_t *bitmaptable, gi_coord_t x2, gi_coord_t y2);
int gi_draw_points(gi_gc_ptr_t gc,gi_point_t*points,int npoints);
int gi_fill_spans(gi_gc_ptr_t gc, gi_spans_t* points, int npoints);
void gi_patblt_image(gi_gc_ptr_t gc,gi_image_t *image, 
  gi_coord_t x, gi_coord_t y, gi_coord_t w, gi_coord_t h);
int gi_draw_image(gi_gc_ptr_t gc,gi_image_t *bitmaptable, gi_coord_t x2, gi_coord_t y2);
int gi_get_window_region(gi_window_id_t window, gi_region_t *prop);
int gi_gc_attch_window(gi_gc_ptr_t gc,gi_window_id_t id);

int gi_image_get_pitch(gi_format_code_t fmt, int width);
gi_image_t* gi_create_image_with_data(int w, int h, void *rgba, gi_format_code_t depth);
int gi_release_bitmap_struct(gi_image_t* img);
int gi_destroy_image(gi_image_t* img);
void gi_image_reference(gi_image_t* img);
gi_image_t* gi_create_image_depth(int w, int h, gi_format_code_t depth);
gi_image_t* gi_create_image(int w, int h);
gi_image_t* gi_create_bitmap_from_data(const char *data, unsigned width, unsigned height);

int gi_grab_pointer(gi_window_id_t grab_window,gi_bool_t owner_events,
	  gi_bool_t key_mode,unsigned int event_mask,int cursor, int button );
int gi_ungrab_pointer(void);
int gi_clear_area(gi_window_id_t wid, int x,int y,int w, int h,  gi_bool_t exposeflag);
int gi_grab_keyboard(gi_window_id_t grab_window, gi_bool_t owner_events, int pointer_mode, int keyboard_mode);
int gi_ungrab_keyboard(void);


#ifndef __KERNEL__

#if defined(__LINUX__)
#include  <pthread.h>
#endif

struct g_timer_obj;
struct g_timer_list {
  LIST_HEAD(, g_timer_obj) timer_list;
#if defined(__LINUX__)
	pthread_mutex_t mutex;
#else
  void *mutex;
#endif
};
typedef int (* g_timer_handler_t)(void *arg);
void* g_timer_add(struct g_timer_list *lists,uint32_t msecs, g_timer_handler_t h, void *arg)
;
int g_timer_change(struct g_timer_list *lists, void *obj, uint32_t msecs,
	g_timer_handler_t time_cb, void *arg);
gi_bool_t g_timer_set_interval(void *obj,uint32_t msecs);
gi_bool_t g_timer_set_arg(void *obj,void *arg);
int  g_timer_remove(struct g_timer_list *lists, void *handler);
int g_timer_run(struct g_timer_list *lists, gi_msg_t *msg);
void* gi_dispatch_timer_new(uint32_t msecs, g_timer_handler_t h, void *arg);
int gi_dispatch_timer_change(void* hld, uint32_t msecs, g_timer_handler_t h, void *arg);
int gi_dispatch_timer_remove(void *hld);
void g_timer_init(struct g_timer_list *lists);
#endif

int gi_iconify_window (gi_window_id_t w);
int gi_post_quit_message(gi_window_id_t window);
int gi_wm_activate_window(gi_window_id_t window);
int gi_wm_focus_window(gi_window_id_t window);
//int gi_wm_maximize_window(gi_window_id_t window);
int gi_fullscreen_window(gi_window_id_t window, int fullscreen);
int gi_wm_set_window_bounds(gi_window_id_t window,int x, int y,int w, int h, long flags);
int gi_wm_window_maximize(gi_window_id_t window, gi_bool_t setting);
gi_window_id_t locate_system_tray(void);

int gi_fetch_window_caption_name (gi_window_id_t w, char **name);
int gi_get_transient_for_hint(gi_window_id_t w,gi_window_id_t * propWindow);

enum  { 
        G_WINDOW_LAYER_DESKTOP = 12,
        G_WINDOW_LAYER_BELOW = 10,
        G_WINDOW_LAYER_NORMAL = 8,
        G_WINDOW_LAYER_ONTOP = 6,
        G_WINDOW_LAYER_DOCK = 4,
        G_WINDOW_LAYER_ABOVE_DOCK = 2,
        G_WINDOW_LAYER_MENU = 0
    };

int gi_set_window_keep_above(gi_window_id_t window, gi_bool_t setting);
int gi_set_window_keep_below(gi_window_id_t window, gi_bool_t setting);
int gi_set_window_stack (gi_window_id_t windows, unsigned layer);
int gi_flush(void);



typedef struct gi_animation_t
{
	int width,height;
	int time;//
	int n_frame;
	gi_bool_t has_trans;
	gi_color_t trans_color;
	gi_image_t **animation_frame;
	int *delay_time;
	void *data;
}gi_animation_t; 


void gi_destroy_animation(gi_animation_t *anim);
gi_animation_t *gi_create_animation_with_gif(const char *path);
gi_animation_t *gi_create_animation_with_gif_format(const char *path,gi_format_code_t gformat);


typedef struct  {
        uint32_t flags;
		int x,y;
        uint32_t params[4];
}gi_composition_form_t;

#define IME_GET_INPUT_STATUS 0x01
#define IME_SET_INPUT_STATUS 0x02


int gi_ime_associate_window(gi_window_id_t window, gi_composition_form_t *attr);
int gi_ime_set_server_window(gi_window_id_t window, gi_composition_form_t *attr);
int gi_ime_get_target_window(gi_window_id_t *window);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
