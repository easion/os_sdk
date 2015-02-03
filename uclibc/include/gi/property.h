
#ifndef __GI_PROP_H__
#define __GI_PROP_H__ 1


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




typedef gi_id_t gi_atom_id_t;

/* THIS IS A GENERATED FILE
 *
 * Do not change!  Changing this file implies a protocol change!
 */

#define GA_PRIMARY ((gi_atom_id_t) 1)
#define GA_SECONDARY ((gi_atom_id_t) 2)
#define GA_ARC ((gi_atom_id_t) 3)
#define GA_ATOM ((gi_atom_id_t) 4)
#define GA_BITMAP ((gi_atom_id_t) 5)
#define GA_CARDINAL ((gi_atom_id_t) 6)
#define GA_COLORMAP ((gi_atom_id_t) 7)
#define GA_CURSOR ((gi_atom_id_t) 8)
#define GA_CUT_BUFFER0 ((gi_atom_id_t) 9)
#define GA_CUT_BUFFER1 ((gi_atom_id_t) 10)
#define GA_CUT_BUFFER2 ((gi_atom_id_t) 11)
#define GA_CUT_BUFFER3 ((gi_atom_id_t) 12)
#define GA_CUT_BUFFER4 ((gi_atom_id_t) 13)
#define GA_CUT_BUFFER5 ((gi_atom_id_t) 14)
#define GA_CUT_BUFFER6 ((gi_atom_id_t) 15)
#define GA_CUT_BUFFER7 ((gi_atom_id_t) 16)
#define GA_DRAWABLE ((gi_atom_id_t) 17)
#define GA_FONT ((gi_atom_id_t) 18)
#define GA_INTEGER ((gi_atom_id_t) 19)
#define GA_PIXMAP ((gi_atom_id_t) 20)
#define GA_POINT ((gi_atom_id_t) 21)
#define GA_RECTANGLE ((gi_atom_id_t) 22)
#define GA_RESOURCE_MANAGER ((gi_atom_id_t) 23)
#define GA_RGB_COLOR_MAP ((gi_atom_id_t) 24)
#define GA_RGB_BEST_MAP ((gi_atom_id_t) 25)
#define GA_RGB_BLUE_MAP ((gi_atom_id_t) 26)
#define GA_RGB_DEFAULT_MAP ((gi_atom_id_t) 27)
#define GA_RGB_GRAY_MAP ((gi_atom_id_t) 28)
#define GA_RGB_GREEN_MAP ((gi_atom_id_t) 29)
#define GA_RGB_RED_MAP ((gi_atom_id_t) 30)
#define GA_STRING ((gi_atom_id_t) 31)
#define GA_UTF8_STRING ((gi_atom_id_t) 32)
#define GA_WINDOW ((gi_atom_id_t) 33)
#define GA_WM_COMMAND ((gi_atom_id_t) 34)
#define GA_WM_HINTS ((gi_atom_id_t) 35)
#define GA_WM_CLIENT_MACHINE ((gi_atom_id_t) 36)
#define GA_WM_ICON_NAME ((gi_atom_id_t) 37)
#define GA_WM_ICON_SIZE ((gi_atom_id_t) 38)
#define GA_WM_NAME ((gi_atom_id_t) 39)
#define GA_WM_NORMAL_HINTS ((gi_atom_id_t) 40)
#define GA_WM_SIZE_HINTS ((gi_atom_id_t) 41)
#define GA_WM_ZOOM_HINTS ((gi_atom_id_t) 42)
#define GA_MIN_SPACE ((gi_atom_id_t) 43)
#define GA_NORM_SPACE ((gi_atom_id_t) 44)
#define GA_MAX_SPACE ((gi_atom_id_t) 45)
#define GA_END_SPACE ((gi_atom_id_t) 46)
#define GA_NET_WM_WINDOW_TYPE ((gi_atom_id_t) 47)
#define GA_WM_STATE ((gi_atom_id_t) 48)
#define GA_WM_WINDESC ((gi_atom_id_t) 49)
#define GA_WM_MANAGER ((gi_atom_id_t) 50)
#define GA_NET_CLIENT_LIST ((gi_atom_id_t) 51)
#define GA_NET_WM_ICON ((gi_atom_id_t) 52)
#define GA_WIN_LAYER ((gi_atom_id_t) 53)
#define GA_STRIKEOUT_DESCENT ((gi_atom_id_t) 54)
#define GA_ITALIC_ANGLE ((gi_atom_id_t) 55)
#define GA_X_HEIGHT ((gi_atom_id_t) 56)
#define GA_WM_DELETE_WINDOW ((gi_atom_id_t) 57)
#define GA_WM_PROTOCOLS ((gi_atom_id_t) 58)
#define GA_NET_WM_STATE ((gi_atom_id_t) 59)
#define GA_RESOLUTION ((gi_atom_id_t) 60)
#define GA_COPYRIGHT ((gi_atom_id_t) 61)
#define GA_NOTICE ((gi_atom_id_t) 62)
#define GA_FONT_NAME ((gi_atom_id_t) 63)
#define GA_FAMILY_NAME ((gi_atom_id_t) 64)
#define GA_FULL_NAME ((gi_atom_id_t) 65)
#define GA_CAP_HEIGHT ((gi_atom_id_t) 66)
#define GA_WM_CLASS ((gi_atom_id_t) 67)
#define GA_WM_TRANSIENT_FOR ((gi_atom_id_t) 68)

#define GA_LAST_PREDEFINED ((gi_atom_id_t) 68)



/* Property notification */

#define G_PROPERTY_NEW	0
#define G_PROPERTY_DELETE		1

#define G_PROP_MODE_Replace         0
#define G_PROP_MODE_Prepend         1
#define G_PROP_MODE_Append          2
#define G_ANY_PROP_TYPE      0L	/* special gi_atom_id_t, passed to GetProperty */



#ifndef G_PROP_NONE
#define G_PROP_NONE                 0L	/* universal null resource or null atom */
#endif

#define G_SEL_CLEAR 1
#define G_SEL_REQUEST 2
#define G_SEL_NOTIFY 3
struct GetPropertyReply
{
	gi_atom_id_t propertyType;		/*  */
    int format;  	/*   8, 16, or 32 */
    unsigned long nItems; 	/*   # of 8-, 16-, or 32-bit entities */
    unsigned long bytesAfter;	/*  */
    int length;
	//char data[0];
};



#ifndef __KERNEL__

enum{
	G_ICON_FLAG_NONE,
	G_ICON_FLAG_INFO,
	G_ICON_FLAG_WARNING,
	G_ICON_FLAG_ERROR,
	G_ICON_FLAG_HELP,
	G_ICON_FLAG_MAX,
};

enum{
	G_NIN_ADD,
	G_NIN_DEL,
	G_NIN_ACTIVE,
	G_NIN_PING,
	G_NIN_MOUSE_UP,
	G_NIN_LBUTTONDBLCLK,	
	G_NIN_CONTEXT,
	G_NIN_BALLOON_SHOW=10,
	G_NIN_BALLOON_CLICK
};
	
typedef struct g_metrics_tag
{
	uint32_t bg_color;
	uint32_t fg_color;
	uint32_t shadow_color;
	uint32_t font_color;
	int small_icon;
	int big_icon;
	int cursor_size;
	int caption_size;
	int screen_w;
	int screen_h;
	int font_size;
	uint16_t mouse_present:1;
	int double_click_x;
	int double_click_y;
	int double_click_time;
	int border;
	char system_font_name[256];
	uint32_t res[16];
}gi_wm_metrics_t;

#define G_MAX_REQUEST_SIZE 256*1024

gi_atom_id_t gi_intern_atom(const char *atom_name, gi_bool_t only_if_exists);
char *gi_get_atom_name(gi_atom_id_t atom);

int gi_delete_property(gi_window_id_t w, gi_atom_id_t property);
int gi_change_property (gi_window_id_t w,
    gi_atom_id_t property,
    gi_atom_id_t type,
    int format,  /* 8, 16, or 32 */
    int mode,  /* PropModeReplace, PropModePrepend, PropModeAppend */
    const unsigned char *data,
    int nelements);
int gi_get_window_property(
    gi_window_id_t w,
    gi_atom_id_t property,
    long offset,
    long long_length,
    gi_bool_t dele,
    gi_atom_id_t req_type,
    gi_atom_id_t *actual_type,		/*  */
    int *actual_format,  	/*   8, 16, or 32 */
    unsigned long *nitems, 	/*   # of 8-, 16-, or 32-bit entities */
    unsigned long *bytesafter,	/*  */
    unsigned char **prop_return);	/*  */
gi_atom_id_t *gi_list_properties(gi_window_id_t window, int *n_props) ;
int gi_rotate_window_properties(gi_window_id_t w,
    gi_atom_id_t *properties,   int nprops,  int npositions);


gi_window_id_t gi_get_selection_owner( gi_atom_id_t selection);
int gi_set_selection_owner(gi_atom_id_t selection,  gi_window_id_t owner, time_t time);
int gi_convert_selection(gi_atom_id_t selection,  gi_atom_id_t target,  
gi_atom_id_t property, gi_window_id_t requestor,    time_t time);

BOOL gi_clipboard_owner_set (gi_window_id_t  w,   uint32_t time_, void (*exit_cb)(void*,gi_window_id_t win, gi_atom_id_t) );
gi_bool_t gi_clipboard_set_data(const char *datatype, const char *data, int size);
gi_bool_t gi_clipboard_set_target_data(gi_atom_id_t atom, const char *data, int size);
gi_bool_t gi_clipboard_request(gi_window_id_t  w, const char* dataname,  uint32_t time_, void (*got_cb)(void*,gi_window_id_t win, gi_atom_id_t, char *, int), void *data);
gi_bool_t gi_clipboard_available(const char *type,void (*available_callback)(void*,gi_window_id_t win, gi_atom_id_t ,BOOL avail ) );

int  gi_add_proxy_tray(gi_window_id_t twin);
int gi_remove_proxy_tray(gi_window_id_t twin);
int  gi_wm_set_balloon(gi_window_id_t id, 
	const char *title, const char *message,gi_image_t* img, int flag);
int  gi_wm_show_balloon(gi_window_id_t id, int timeout);

int gi_wm_query_metrics(gi_wm_metrics_t **me);
int gi_wm_get_workarea(int *app_area_coord);


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GI_PROP_H__ */

