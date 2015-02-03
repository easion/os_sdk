#ifndef _ECORE_GIX_H
#define _ECORE_GIX_H

#include <gi/gi.h>

#ifdef EAPI
#undef EAPI
#endif
#ifdef _MSC_VER
# ifdef BUILDING_DLL
#  define EAPI __declspec(dllexport)
# else
#  define EAPI __declspec(dllimport)
# endif
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif

#include <Ecore_Data.h>
#include <gi/gi.h>


#ifdef __cplusplus
extern "C" {
#endif

EAPI extern int ECORE_GIX_EVENT_POSITION;
EAPI extern int ECORE_GIX_EVENT_DESTROYED;
EAPI extern int ECORE_GIX_EVENT_GOT_FOCUS;
EAPI extern int ECORE_GIX_EVENT_LOST_FOCUS;
EAPI extern int ECORE_GIX_EVENT_KEY_DOWN;
EAPI extern int ECORE_GIX_EVENT_KEY_UP;
EAPI extern int ECORE_GIX_EVENT_BUTTON_DOWN;
EAPI extern int ECORE_GIX_EVENT_BUTTON_UP;
EAPI extern int ECORE_GIX_EVENT_MOTION;
EAPI extern int ECORE_GIX_EVENT_ENTER;
EAPI extern int ECORE_GIX_EVENT_LEAVE;
EAPI extern int ECORE_GIX_EVENT_WHEEL;
EAPI extern int ECORE_GIX_EVENT_WINDOW_DAMAGE;

EAPI extern int ECORE_GIX_EVENT_WINDOW_VISIBILITY_CHANGE;
EAPI extern int ECORE_GIX_EVENT_WINDOW_CREATE;
EAPI extern int ECORE_GIX_EVENT_WINDOW_DESTROY;
EAPI extern int ECORE_GIX_EVENT_WINDOW_HIDE;
EAPI extern int ECORE_GIX_EVENT_WINDOW_SHOW;
EAPI extern int ECORE_GIX_EVENT_WINDOW_SHOW_REQUEST;
EAPI extern int ECORE_GIX_EVENT_WINDOW_REPARENT;
EAPI extern int ECORE_GIX_EVENT_WINDOW_CONFIGURE;
EAPI extern int ECORE_GIX_EVENT_WINDOW_CONFIGURE_REQUEST;
EAPI extern int ECORE_GIX_EVENT_WINDOW_GRAVITY;
EAPI extern int ECORE_GIX_EVENT_WINDOW_RESIZE_REQUEST;
EAPI extern int ECORE_GIX_EVENT_WINDOW_STACK;
EAPI extern int ECORE_GIX_EVENT_WINDOW_STACK_REQUEST;
EAPI extern int ECORE_GIX_EVENT_WINDOW_PROPERTY;
EAPI extern int ECORE_GIX_EVENT_WINDOW_COLORMAP;
EAPI extern int ECORE_GIX_EVENT_WINDOW_MAPPING;
EAPI extern int ECORE_GIX_EVENT_SELECTION_CLEAR;
EAPI extern int ECORE_GIX_EVENT_SELECTION_REQUEST;
EAPI extern int ECORE_GIX_EVENT_SELECTION_NOTIFY;
EAPI extern int ECORE_GIX_EVENT_CLIENT_MESSAGE;
EAPI extern int ECORE_GIX_EVENT_WINDOW_SHAPE;
EAPI extern int ECORE_GIX_EVENT_SCREENSAVER_NOTIFY;
EAPI extern int ECORE_GIX_EVENT_SYNC_COUNTER;
EAPI extern int ECORE_GIX_EVENT_SYNC_ALARM;
EAPI extern int ECORE_GIX_EVENT_SCREEN_CHANGE;
EAPI extern int ECORE_GIX_EVENT_DAMAGE_NOTIFY;
EAPI extern int ECORE_GIX_EVENT_WINDOW_DELETE_REQUEST;

EAPI extern int ECORE_GIX_EVENT_WINDOW_MOVE_RESIZE_REQUEST;
EAPI extern int ECORE_GIX_EVENT_WINDOW_STATE_REQUEST;
EAPI extern int ECORE_GIX_EVENT_FRAME_EXTENTS_REQUEST;
EAPI extern int ECORE_GIX_EVENT_PING;
EAPI extern int ECORE_GIX_EVENT_DESKTOP_CHANGE;

EAPI extern int ECORE_GIX_EVENT_STARTUP_SEQUENCE_NEW;
EAPI extern int ECORE_GIX_EVENT_STARTUP_SEQUENCE_CHANGE;
EAPI extern int ECORE_GIX_EVENT_STARTUP_SEQUENCE_REMOVE;

EAPI extern int ECORE_GIX_EVENT_XDND_ENTER;
EAPI extern int ECORE_GIX_EVENT_XDND_POSITION;
EAPI extern int ECORE_GIX_EVENT_XDND_STATUS;
EAPI extern int ECORE_GIX_EVENT_XDND_LEAVE;
EAPI extern int ECORE_GIX_EVENT_XDND_DROP;
EAPI extern int ECORE_GIX_EVENT_XDND_FINISHED;


#ifndef _ECORE_GIX_WINDOW_PREDEF
typedef struct _Ecore_Gix_Window			Ecore_Gix_Window;
#endif
typedef int			Ecore_Gix_Cursor;

typedef struct _Ecore_Gix_Event_Key_Down		Ecore_Gix_Event_Key_Down; 
typedef struct _Ecore_Gix_Event_Key_Up		Ecore_Gix_Event_Key_Up;
typedef struct _Ecore_Gix_Event_Button_Down	Ecore_Gix_Event_Button_Down;
typedef struct _Ecore_Gix_Event_Button_Up		Ecore_Gix_Event_Button_Up;
typedef struct _Ecore_Gix_Event_Motion		Ecore_Gix_Event_Motion;
typedef struct _Ecore_Gix_Event_Enter		Ecore_Gix_Event_Enter;
typedef struct _Ecore_Gix_Event_Leave		Ecore_Gix_Event_Leave;
typedef struct _Ecore_Gix_Event_Wheel		Ecore_Gix_Event_Wheel;
typedef struct _Ecore_Gix_Event_Got_Focus		Ecore_Gix_Event_Got_Focus;
typedef struct _Ecore_Gix_Event_Lost_Focus		Ecore_Gix_Event_Lost_Focus;
typedef struct _Ecore_Gix_Event_Window_Damage            Ecore_Gix_Event_Window_Damage;
typedef struct _Ecore_Gix_Event_Window_Configure         Ecore_Gix_Event_Window_Configure;
typedef struct _Ecore_Gix_Event_Window_Destroy           Ecore_Gix_Event_Window_Destroy;
typedef struct _Ecore_Gix_Event_Mouse_Wheel              Ecore_Gix_Event_Mouse_Wheel;

typedef struct _Ecore_Gix_Event_Window_Hide              Ecore_Gix_Event_Window_Hide;
typedef struct _Ecore_Gix_Event_Window_Show              Ecore_Gix_Event_Window_Show;
typedef struct _Ecore_Gix_Event_Window_Delete_Request                Ecore_Gix_Event_Window_Delete_Request;
typedef long Ecore_X_Time;


struct _Ecore_Gix_Event_Mouse_Wheel
{
   int direction; /* 0 = default up/down wheel FIXME: more wheel types */
   int z; /* ...,-2,-1 = down, 1,2,... = up */
   int modifiers;
   int x, y;

   struct {
      int x, y;
   } root;

   gi_window_id_t win;
   gi_window_id_t event_win;
   Ecore_X_Time   time;
};


struct _Ecore_Gix_Event_Window_Delete_Request
{
   gi_window_id_t  win;
   Ecore_X_Time    time;
};



struct _Ecore_Gix_Event_Window_Destroy
{
   gi_window_id_t  win;
   Ecore_X_Time    time;
};

struct _Ecore_Gix_Event_Window_Hide
{
   gi_window_id_t  win;
   Ecore_X_Time    time;
};

struct _Ecore_Gix_Event_Window_Show
{
   gi_window_id_t  win;
   Ecore_X_Time    time;
};


struct _Ecore_Gix_Event_Window_Configure
{
   gi_window_id_t  win;
   gi_window_id_t  abovewin;
   int             x, y, w, h;
   int             border;
   int             override : 1;
   int             from_wm : 1;
   Ecore_X_Time    time;
};


struct _Ecore_Gix_Event_Window_Damage
{
   gi_window_id_t  win;
   int             x, y, w, h;
   int             count;
   Ecore_X_Time    time;
};



/* this struct is to keep windows data (id, window itself and surface) in memory as every call
 * to DirectFB for this values (e.g window->GetSurface(window,&surface)) will increment the
 * reference count, then we will have to release N times the data, so better we just ask for 
 them once */
struct _Ecore_Gix_Window
{
	//gi_window_id_t 		id;
	gi_window_id_t		window;
	gi_image_t	*surface;
	gi_gc_ptr_t	gc;
	Ecore_Gix_Cursor	*cursor;
	unsigned int        min_width;
   unsigned int        min_height;
   unsigned int        max_width;
   unsigned int        max_height;
   unsigned int        base_width;
   unsigned int        base_height;
   unsigned int        step_width;
   unsigned int        step_height;

   unsigned int        pointer_is_in : 1;
   unsigned int        borderless    : 1;
   unsigned int        iconified     : 1;
   unsigned int        fullscreen    : 1;
	
};



struct _Ecore_Gix_Event_Key_Down /** DirectFB Key Down event */
{
	char   *name; /**< The name of the key that was released */
   	char   *string; /**< The logical symbol of the key that was pressed */
	char   *key_compose; /**< The UTF-8 string conversion if any */
   	unsigned int time;
	gi_window_id_t win;
	int keysymbol;
};
   
struct _Ecore_Gix_Event_Key_Up /** DirectFB Key Up event */
{
	char   *name; /**< The name of the key that was released */
   	char   *string; /**< The logical symbol of the key that was pressed */
	char   *key_compose; /**< The UTF-8 string conversion if any */
   	unsigned int time;
	gi_window_id_t win;
	int keysymbol;
};

struct _Ecore_Gix_Event_Button_Down
{
	int button;
	int modifiers;
	int x, y;
	unsigned int time;
	int double_click : 1;
	int triple_click : 1;
	gi_window_id_t win;
};
struct _Ecore_Gix_Event_Button_Up
{
	int button;
	int modifiers;
	int x, y;
	unsigned int time;
	gi_window_id_t win;
};
struct _Ecore_Gix_Event_Motion
{
	int modifiers;
	int x, y;
	unsigned int time;
	gi_window_id_t win;
};

struct _Ecore_Gix_Event_Enter
{
	int modifiers;
	int x, y;
	unsigned int time;
	gi_window_id_t win;
};

struct _Ecore_Gix_Event_Leave
{
	int modifiers;
	int x, y;
	unsigned int time;
	gi_window_id_t win;
};


struct _Ecore_Gix_Event_Got_Focus
{
	unsigned int time;
	gi_window_id_t win;
};

struct _Ecore_Gix_Event_Lost_Focus
{
	unsigned int time;
	gi_window_id_t win;
};

/* main functions */
EAPI int ecore_gix_init(const char *name);
EAPI int ecore_gix_shutdown(void);

/* window operations */
EAPI Ecore_Gix_Window * ecore_gix_window_new(int x, int y, int w, int h);
EAPI void ecore_gix_window_del(Ecore_Gix_Window *window);
EAPI void ecore_gix_window_move(Ecore_Gix_Window *window, int x, int y);
EAPI void ecore_gix_window_resize(Ecore_Gix_Window *window, int w, int h);
EAPI void ecore_gix_window_focus(Ecore_Gix_Window *window);
EAPI void ecore_gix_window_show(Ecore_Gix_Window *window);
EAPI void ecore_gix_window_hide(Ecore_Gix_Window *window);
EAPI void ecore_gix_window_shaped_set(Ecore_Gix_Window *window, int set);
EAPI void ecore_gix_window_fullscreen_set(Ecore_Gix_Window *window, int set);
EAPI void ecore_gix_window_size_get(Ecore_Gix_Window *window, int *w, int *h);
EAPI void ecore_gix_window_cursor_show(Ecore_Gix_Window *window, int show);



#ifdef __cplusplus
}
#endif

#endif
