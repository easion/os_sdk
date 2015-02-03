
#ifndef __STK_WIDGETS_H__
#define __STK_WIDGETS_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "user_font.h"

/** Alignment of content in a button. */
typedef enum {
   ALIGN_LEFT,   /**< Left align. */
   ALIGN_CENTER, /**< Center align. */
   ALIGN_RIGHT   /**< Right align. */
} AlignmentType;


#define MBOX_OK 1
#define MBOX_EXIT 2
#define MBOX_CANCEL 4
#define MBOX_ICONINFORMATION 8
#define MBOX_ICONWARNING 16
#define MBOX_ICONERROR 32


/*À©Õ¹ÏûÏ¢*/
#define GI_MSG_TIMER    33

#define GI_WMSG_DESTROY    34
#define GI_WMSG_COMMAND    35
#define GI_WMSG_SETTEXT    36
#define GI_WMSG_GETTEXT    37
#define GI_WMSG_SETFOCUS    38
#define GI_WMSG_GETFOCUS    39
#define GI_WMSG_KILLFOCUS    40
#define GI_WMSG_CREATE    41
#define GI_WMSG_ERASEBKGND    42
#define GI_WMSG_ENABLE    43
#define GI_WMSG_DISABLE    44
#define GI_WMSG_ACTIVEWINDOW    45
#define GI_WMSG_DISACTIVEWINDOW    46
#define GI_WMSG_TIMER    47
#define GI_WMSG_PAINT    48
#define GI_WMSG_VSCROLL    49
#define GI_WMSG_HSCROLL    50
#define GI_WMSG_OK    51
#define GI_WMSG_CLOSE    52
#define GI_WMSG_SET_IMAGE    53
#define GI_WMSG_GET_IMAGE    54
#define GI_WMSG_GOTFOCUS    55
#define GI_WMSG_LOSTFOCUS    56
#define GI_WMSG_TXTMODIFY    57
#define GI_WMSG_DCLICK    58
#define GI_WMSG_SET_FONT    59
#define GI_WMSG_FONT_COLOR    60
#define GI_WMSG_ALIGNMENT 61
#define GI_WMSG_ENTER     62
#define GI_WMSG_LEAVE     63


#define TK_WINDOW(widget) ((widget)->winid)
#define TK_WINDGET_EVENT_OBJECT(widget) (&(widget)->base)
#define TK_GC(widget) ((widget)->base.gc)
#define TK_WIDGET(widget) ((widget)->base.data)
#define TK_WINDOW_TYPE(widget) ((widget)->base.type)


typedef struct _StkWidget StkWidget;
typedef struct _StkWindow StkWindow;

#define STK_RET_OK 1
#define STK_RET_EXIT 2
#define STK_RET_CANCEL 3


typedef struct StkObject
{
  int type;    /*Type of widget */
  int (*event_handler) (gi_msg_t *event, void *window);
  int (*filter_handler) (gi_msg_t *event, void *window);
  void *data;    /* Data associated with this window */
  void *fdata;
  gi_gc_ptr_t gc;
  gi_bool_t visible, enabled;
  long flags;
}StkObject;



typedef enum {
	STK_HINT_TREEVIEW,
	STK_HINT_TREEVIEW_HEADER,
	STK_HINT_STATUSBAR,
	STK_HINT_COMBOBOX_ENTRY,
	STK_HINT_SPINBUTTON,
	STK_HINT_SCALE,
	STK_HINT_VSCALE,
	STK_HINT_HSCALE,
	STK_HINT_SCROLLBAR,
	STK_HINT_VSCROLLBAR,
	STK_HINT_HSCROLLBAR,
	STK_HINT_PROGRESSBAR,
	STK_HINT_MENUBAR,
	STK_HINT_COUNT
} GEHint;



/* Shadow types */
typedef enum
{
  STK_SHADOW_NONE,
  STK_SHADOW_IN,
  STK_SHADOW_OUT,
  STK_SHADOW_ETCHED_IN,
  STK_SHADOW_ETCHED_OUT
} StkShadowType;

/* Widget states */
typedef enum
{
  STK_STATE_NORMAL,
  STK_STATE_ACTIVE,
  STK_STATE_PRELIGHT,
  STK_STATE_SELECTED,
  STK_STATE_INSENSITIVE
} StkStateType;


typedef enum
{
  STK_POS_LEFT,
  STK_POS_RIGHT,
  STK_POS_TOP,
  STK_POS_BOTTOM
} StkPositionType;



/* Arrow types */
typedef enum
{
	STK_ARROW_NONE,
  STK_ARROW_UP,
  STK_ARROW_DOWN,
  STK_ARROW_LEFT,
  STK_ARROW_RIGHT
} StkArrowType;

struct _StkWindow {
  StkObject base;
  gi_cliprect_t rect;
  gi_window_id_t winid;  /* The ID of this window */
  gi_window_id_t pid;  /* The ID of this window's parent */
  gi_bool_t enable_double_click;

  gi_bool_t focus;
  void* cairo_surface; 
  gi_color_t win_bg_color;
  TAILQ_ENTRY(_StkWindow) entry;
  struct _StkWidget *first_child;  
  struct _StkWidget *focus_child;  
  struct _StkWidget *mouse_child;  
};


struct _StkWidget {
  StkObject base;
  StkWindow* parent;
  gi_cliprect_t rect;  
  gi_bool_t focus;
  gi_color_t bg_color;
  gi_color_t fg_color;  
  gi_color_t text[5];
  long state;
  int hint;
  unsigned short widget_id;
  char *caption;
  struct _StkWidget *next; /* The next window in the list */
};


struct window_class
{
  struct window_class *next;  
  char *classname;
  int (*fn_event_handler) (gi_msg_t * event, void * widget);
  unsigned style;
  void *icon;
  int cursor;
};

void stk_init(void) ;

struct window_class * find_window_class(const char *classname);
int window_class_init(void);
gi_bool_t register_window_class(struct window_class *windowclass);
gi_bool_t unregister_window_class(struct window_class *windowclass);
StkWidget *stk_create_widget(unsigned long style, const char *classname,char *windowname, 
  int x, int y, int width, int height,gi_window_id_t pid,unsigned short widget_id, void *data);

int stk_destroy_widget(StkWidget* widget);
int stk_clear_widget(StkWidget* widget,void(* exp)(StkWidget* ));
void stk_clear_area(StkWidget* widget,int x, int y, int w, int h);
void stk_hide_widget(StkWidget *window);
void stk_widget_set_usize(StkWidget *window, int w, int h);
int gi_widget_send_message(StkWidget *widget, unsigned cmd, void *para);
int gi_widget_send_event(StkWidget *widget, gi_msg_t *msg);
int add_widget_on_head(StkWindow *wp, StkWidget *widget);
void stk_paint_widgets(StkWindow *wp, gi_msg_t *event);
void stk_move_widgets(StkWindow *wp, int xoffset, int yoffset);
void stk_move_widget( StkWidget *child, int x, int y);
void stk_resize_widget( StkWidget *child, int w, int h);
StkWidget* stk_get_widget_item(StkWindow* window,int id);
int gi_send_window_message(StkWindow *widget, unsigned cmd, unsigned para);
char *stk_textbox_get_text (StkWidget * widget);
int stk_set_widget_text(StkWidget *widget,const char *caption);
char* stk_get_widget_text(StkWidget *widget);
int stk_set_widget_image(StkWidget *widget,const gi_image_t *img);
gi_image_t* stk_get_widget_image(StkWidget *widget);
void stk_show_widget(StkWidget *widget);
gi_image_t* gi_load_image_file(const char *filename,int w, int h);

int stk_msgbox(StkWindow *wp, const char *title, long style, char *msg, ...);
int stk_get_open_file(StkWindow *wp, const char *title,  char *buffer, int size);
StkWindow *stk_find_window(gi_window_id_t winid);
int stk_widget_erase_background(StkWidget *widget, void *data);


struct stk_popmenu_t;
struct stk_popmenu_t *stk_menu_new(const char *icon,const char *name,unsigned short key,void (*cb)(struct stk_popmenu_t*, void *), void *data);
void stk_menu_add_item(struct stk_popmenu_t *menu, struct stk_popmenu_t *submenu);
void stk_menu_del_item(struct stk_popmenu_t *menu, struct stk_popmenu_t *submenu);
int stk_menu_popup(int x, int y, struct stk_popmenu_t *menu);

int stk_widget_disable(StkWidget *widget);
int stk_widget_enable(StkWidget *widget);
int stk_textbox_set_text (StkWidget * widget, char *s);

int stk_scroll_set_range(StkWidget *widget,int minval,int maxval);
int stk_listbox_delete_all(StkWidget *listbox);
int stk_listbox_add_item(StkWidget *listbox,char *str);
int stk_listbox_get_selected_items(StkWidget *widget, char ***listinfo, int *count);
int stk_scroll_get_thumb_position(StkWidget *widget);
int stk_listbox_get_top(StkWidget *listbox);
int stk_listbox_items_line_down(StkWidget *listbox,int n);
int stk_listbox_items_line_up(StkWidget *listbox,int n);
int stk_viewer_set_file(StkWidget *widget ,char *filename);
void stk_progressbar_update(StkWidget *widget, int percval);
int stk_viewer_set_image(StkWidget *widget ,gi_image_t *img);


int stk_get_string_height( gi_ufont_t *font);
void stk_draw_text(gi_gc_ptr_t gc,  gi_ufont_t *font,AlignmentType alignment,unsigned fg, char *text,
int iconWidth,	int x, int y, int width, int height) ;
void stk_draw_border_type(gi_gc_ptr_t gc, int x, int y,  int width, int height,int type) ;
void stk_vertgradient2(gi_gc_ptr_t surf, gi_cliprect_t * gradRect, gi_color_t c1, gi_color_t c2);
void stk_horizgradient2(gi_gc_ptr_t  surf, gi_cliprect_t * gradRect, gi_color_t c1, gi_color_t c2);
void stk_set_window_surface_size(StkWindow *window,int w, int h);


int stk_set_widget_font_color(StkWidget *widget,gi_color_t color);
int stk_set_widget_font(StkWidget *widget,const char *font);
int stk_set_widget_alignment(StkWidget *widget, AlignmentType alignment);
int stk_widget_set_focus(StkWidget *widget);
int gi_set_dispatch_filter(gi_window_id_t winid,int (*handler)(gi_msg_t *event,void *data), void *data);


#ifdef __cplusplus
}
#endif


#endif

