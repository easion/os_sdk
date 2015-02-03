
#include "cfg.h"

#ifdef   NCE_WINDOWS

#include "links.h"
#include "bits.h"

#include <ctype.h>
#include <netbas/kbd.h>
#include <nce/gui.h>
#include <nce/nce.h>

//#define DEBUGF printf
#define DEBUGF

#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) > (b) ? (a) : (b))

extern struct graphics_driver nce_driver;
int bytesperpixel=32;
typedef struct lnce_device_s {
	char *title;
	GUIRect update;
	gc_t *surface;
} lnce_device_t;

typedef struct lnce_eventq_s {
	//s_list_t *list;
	//s_thread_mutex_t *mut;
} lnce_eventq_t;

typedef struct lnce_gd_s {
	//s_list_t *list;
	//s_thread_mutex_t *mut;
	struct graphics_device *active;
} lnce_gd_t;

typedef struct lnce_root_s {
	int timerid;
	int running;
	//s_thread_t *tid;
	struct nce_app_window *window;
	lnce_eventq_t *eventq;
	lnce_gd_t *gd;
} lnce_root_t;

static lnce_root_t *lnce_root = NULL;
static void lnce_set_title (struct graphics_device *dev, unsigned char *title);

static void lnce_surface_register_update (void *dev)
{
	lnce_device_t *wd;
        if (lnce_root->running == 0) return;
        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}
	wd = (lnce_device_t *) ((struct graphics_device *) dev)->driver_data;
	/*s_putboxpart(lnce_root->window->surface, wd->update.x, wd->update.y, wd->update.w, wd->update.h, 
	lnce_root->window->object.rect.w,lnce_root->window->object.rect.h, wd->surface->vbuf,
		wd->update.x, wd->update.y);*/
	wd->update = (GUIRect) {-1, -1, -1, -1};
	//s_thread_mutex_unlock(lnce_root->gd->mut);
}

static void lnce_surface_update (struct graphics_device *dev, int x, int y, int w, int h)
{
	GUIRect rect;
	lnce_device_t *wd;
	wd = (lnce_device_t *) dev->driver_data;
	rect = wd->update;
	if (rect.x >= 0) { wd->update.x = MIN(rect.x, x); } else { wd->update.x = x; }
	if (rect.y >= 0) { wd->update.y = MIN(rect.y, y); } else { wd->update.y = y; }
	if (rect.w >= 0) { wd->update.w = MAX(rect.x + rect.w, x + w) - wd->update.x; } else { wd->update.w = w; }
	if (rect.h >= 0) { wd->update.h = MAX(rect.y + rect.h, y + h) - wd->update.y; } else { wd->update.h = h; }
	register_bottom_half(lnce_surface_register_update, dev);
}



static void lnce_event_parse_keybd (unsigned short keycode)
{
	int k = 0;
	int flag = 0;
	unsigned short  ascii=keycode;

	//if (!(event->type & KEYBD_PRESSED)) {
	//	return;
	//}
	switch (keycode) {
		case NCE_KEY_ENTER:	k = KBD_ENTER;	break;
		case NCE_KEY_BACKSPACE:	k = KBD_BS;	break;
		case NCE_KEY_TAB:	k = KBD_TAB;	break;
		case NCE_KEY_ESCAPE:	k = KBD_ESC;	break;
		case NCE_KEY_UP:	k = KBD_UP;	break;
		case NCE_KEY_DOWN:	k = KBD_DOWN;	break;
		case NCE_KEY_LEFT:	k = KBD_LEFT;	break;
		case NCE_KEY_RIGHT:	k = KBD_RIGHT;	break;
		case NCE_KEY_INSERT:	k = KBD_INS;	break;
		case NCE_KEY_DELETE:	k = KBD_DEL;	break;
		case NCE_KEY_HOME:	k = KBD_HOME;	break;
		case NCE_KEY_END:	k = KBD_END;	break;
		case NCE_KEY_PAGEUP:	k = KBD_PAGE_UP;break;
		case NCE_KEY_PAGEDOWN:k = KBD_PAGE_DOWN;break;
		case NCE_KEY_F1:	k = KBD_F1;	break;
		case NCE_KEY_F2:	k = KBD_F2;	break;
		case NCE_KEY_F3:	k = KBD_F3;	break;
		case NCE_KEY_F4:	k = KBD_F4;	break;
		case NCE_KEY_F5:	k = KBD_F5;	break;
		case NCE_KEY_F6:	k = KBD_F6;	break;
		case NCE_KEY_F7:	k = KBD_F7;	break;
		case NCE_KEY_F8:	k = KBD_F8;	break;
		case NCE_KEY_F9:	k = KBD_F9;	break;
		case NCE_KEY_F10:	k = KBD_F10;	break;
		case NCE_KEY_F11:	k = KBD_F11;	break;
		case NCE_KEY_F12:	k = KBD_F12;	break;
		default:
			k = ascii;
			if (!isprint(k)) {
				return;
			}
			break;
	}
	/*if (event->keybd->flag & (KEYCODE_CTRLF)) {
		flag |= KBD_CTRL;
	}
	if (event->keybd->flag & (KEYCODE_SHIFTF)) {
	}
	if (event->keybd->flag & (KEYCODE_ALTF | KEYCODE_ALTGRF)) {
		flag |= KBD_ALT;
	}*/

#define KEYBD_HOOK0 \
	int acc = 0;\
	int pos = 0;\
	struct graphics_device *gd;\
	//s_thread_mutex_lock(lnce_root->gd->mut);\
	while (!s_list_eol(lnce_root->gd->list, pos)) {\
		gd = (struct graphics_device *) s_list_get(lnce_root->gd->list, pos);\
		if (gd == lnce_root->gd->active) {\

#define KEYBD_HOOK1 \
		}\
		pos++;\
	}\
	//s_thread_mutex_unlock(lnce_root->gd->mut);\
	if (acc) {\
		char *title;\
		struct rect r;\
		r.x1 = 0;\
		r.y1 = 0;\
		r.x2 = lnce_root->window->surface->buf->w;\
		r.y2 = lnce_root->window->surface->buf->h;\
		title = strdup(((lnce_device_t *) lnce_root->gd->active->driver_data)->title);\
		lnce_set_title(lnce_root->gd->active, title);\
		lnce_root->gd->active->resize_handler(lnce_root->gd->active);\
		lnce_root->gd->active->redraw_handler(lnce_root->gd->active, &r);\
		free(title);\
	}
#if 0
	if ((flag == KBD_CTRL) && (ascii == 'w')) {
		KEYBD_HOOK0;
		/*if (lnce_root->gd->list->nb_elt > 1) {
			s_list_remove(lnce_root->gd->list, pos);
			lnce_root->gd->active = (struct graphics_device *) s_list_get(lnce_root->gd->list, 0);
			acc = 1;
			break;
		}*/
		KEYBD_HOOK1;
		if (acc) {
			gd->keyboard_handler(gd, KBD_CLOSE, 0);
		}
	} else if ((flag == KBD_CTRL) && (k == KBD_LEFT)) {
		KEYBD_HOOK0;
		if (pos >= 1) {
			lnce_root->gd->active = (struct graphics_device *) s_list_get(lnce_root->gd->list, pos - 1);
			acc = 1;
			break;
		}
		KEYBD_HOOK1;
	} else if ((flag == KBD_CTRL) && (k == KBD_RIGHT)) {
		KEYBD_HOOK0;
		if ((pos + 1) < lnce_root->gd->list->nb_elt) {
			lnce_root->gd->active = (struct graphics_device *) s_list_get(lnce_root->gd->list, pos + 1);
			acc = 1;
			break;
		}
		KEYBD_HOOK1;
	} else {
		lnce_root->gd->active->keyboard_handler(lnce_root->gd->active, k, flag);
	}
#else
	lnce_root->gd->active->keyboard_handler(lnce_root->gd->active, k, flag);
#endif
}
/*static void lnce_event_parse_mouse (MSG *event)
{
	int x;
	int y;
	int flag = 0;

	x = event->mouse->x - lnce_root->window->surface->buf->x;
	y = event->mouse->y - lnce_root->window->surface->buf->y;
	if ((x < 0) || (x >  lnce_root->window->surface->buf->w) ||
	    (y < 0) || (y >  lnce_root->window->surface->buf->h)) {
		return;
	}
	switch (event->mouse->b) {
		case 1:  flag = B_RIGHT;  break;
		case 2:  flag = B_MIDDLE; break;
		case 4:  flag = B_LEFT;   break;
	}
	if (event->type & MOUSE_PRESSED) {
		flag |= B_DOWN;
		if (event->mouse->b == MOUSE_WHEELXBUTTON_U) {
			flag = B_MOVE | B_WHEELUP;
		} else if (event->mouse->b == MOUSE_WHEELXBUTTON_D) {
			flag = B_MOVE | B_WHEELDOWN;
		} else if (event->mouse->b == MOUSE_WHEELYBUTTON_U) {
			flag = B_MOVE | B_WHEELLEFT;
		} else if (event->mouse->b == MOUSE_WHEELYBUTTON_D) {
			flag = B_MOVE | B_WHEELRIGHT;
		}
	} else if (event->type & (MOUSE_RELEASED | MOUSE_CLICKED)) {
		flag |= B_UP;
	} else {
		if (event->mouse->buttons) {
			flag |= B_DRAG;
		} else {
			flag |= B_MOVE;
		}
	}
	lnce_root->gd->active->mouse_handler(lnce_root->gd->active, x, y, flag);
	
}
*/
static int links_event_handler(void* hWnd,unsigned iMsg,void* wParam,void* lParam)
{
	int i;
	struct nce_app_window *win=(struct nce_app_window *)hWnd;
	int flag = 0;
	extern int fCursorX,fCursorY;  

	POINT pt;
	POINT rpt;
	nce_get_mouse_pos(win,&pt);

	rpt.x = (int)wParam;
	rpt.y = (int)lParam;

	switch (iMsg)
	{	
  case WM_MOUSEMOVE:
		{
	  flag |= B_MOVE;
	  lnce_root->gd->active->mouse_handler(lnce_root->gd->active, pt.x, pt.y, flag);
	  break;
		}
	case WM_KEY_DOWN:{
		unsigned short keycode = (unsigned short)wParam;
		lnce_event_parse_keybd(keycode);
		break;
	}
	case WM_MOUSEUP:{
		//SendMessage(win, WM_MOUSEUP, NULL,NULL);
		flag = B_LEFT; 
		flag |= B_UP;
		lnce_root->gd->active->mouse_handler(lnce_root->gd->active, pt.x, pt.y, flag);
		break;
	}

	case WM_MOUSEDOWN:
		{
		flag |= B_DOWN;
		flag = B_LEFT; 
		lnce_root->gd->active->mouse_handler(lnce_root->gd->active, pt.x, pt.y, flag);
			break;
		}
	default:
		return default_class_proc(hWnd, iMsg, wParam, lParam);
		break;
  }
  return 1; //ÓÐ´¦Àí
}

static void lnce_timer (void *arg)
{
        int y = 0;
        int k = 0;
        int flag = 0;
        MSG msg;

	//s_thread_mutex_lock(lnce_root->eventq->mut);
        while (1) {
			printf("timer run ...\n");
		//event = (MSG *) s_list_get(lnce_root->eventq->list, 0);

		int retval = nce_peek_message(&msg, 1000,PM_REMOVE);
		if(retval)
			 nce_dispatch_message(&msg);
		else
			break;

		/*s_list_remove(lnce_root->eventq->list, 0);
                switch (event->type & EVENT_MASK) {
			case QUIT_EVENT:	break;
			case MOUSE_EVENT:	lnce_event_parse_mouse(event);	break;
			case KEYBD_EVENT:	lnce_event_parse_keybd(event);	break;
			case CONFIG_EVENT:	lnce_event_parse_config(event);	break;
		}
	//	s_event_uninit(event);*/
	}
	//s_thread_mutex_unlock(lnce_root->eventq->mut);

        if (lnce_root->running) {
		lnce_root->timerid = install_timer(20, lnce_timer, NULL);
	}
}

static void lnce_atevent (struct nce_app_window *window, MSG *event)
{
	/*MSG *e;

	if (lnce_root == NULL) {
	return;
	}
	switch (event->type & EVENT_MASK) {
	case QUIT_EVENT:
	case MOUSE_EVENT:
	case KEYBD_EVENT:
	case EXPOSE_EVENT:
	case CONFIG_EVENT:
	case FOCUS_EVENT:
		if (!s_event_init(&e)) {
			e->type = event->type;
			memcpy(e->mouse, event->mouse, sizeof(s_mouse_t));
			memcpy(e->keybd, event->keybd, sizeof(s_keybd_t));
			memcpy(e->expose->rect, event->expose->rect, sizeof(GUIRect));
			//s_thread_mutex_lock(lnce_root->eventq->mut);
			s_list_add(lnce_root->eventq->list, e, -1);
			//s_thread_mutex_unlock(lnce_root->eventq->mut);
		}
		break;
	default:
		break;
	}*/
}

static void lnce_atexit (struct nce_app_window *window)
{
        if (lnce_root == NULL) {
		return;
	}
	if (lnce_root->running) {
		struct graphics_device *gd = lnce_root->gd->active;

		//s_thread_mutex_lock(lnce_root->gd->mut);
		lnce_root->running = 0;
		lnce_root->gd->active = NULL;
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		gd->keyboard_handler(gd, KBD_CLOSE, 0);
	}
}


static unsigned char * lnce_init_driver (unsigned char *param, unsigned char *display)
{
        int bpp;
        int Bpp;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	lnce_root = (lnce_root_t *) malloc(sizeof(lnce_root_t));
	//lnce_root->eventq = (lnce_eventq_t *) malloc(sizeof(lnce_eventq_t));
	//s_list_init(&(lnce_root->eventq->list));
	//s_thread_mutex_init(&(lnce_root->eventq->mut));
	lnce_root->gd = (lnce_gd_t *) malloc(sizeof(lnce_gd_t));
	//s_list_init(&(lnce_root->gd->list));
	//s_thread_mutex_init(&(lnce_root->gd->mut));
	lnce_root->gd->active = NULL;

	//s_client_init(&(lnce_root->window));
	//s_window_new(lnce_root->window, WINDOW_MAIN, NULL);
	nce_init();
	GUIRect rect = {50, 50,600, 400};
	lnce_root->window = nce_create_window(&rect, NULL,WS_MAIN | WS_CAPTION,NULL );
	nce_set_window_proc(lnce_root->window,&links_event_handler);

        //bpp = lnce_root->window->surface->bitsperpixel;
        //Bpp = lnce_root->window->surface->bytesperpixel;

        if (bpp ==  32) {
		bpp = 24;
	}
	nce_driver.depth = (bpp << 3) | Bpp;

	nce_show_window (lnce_root->window);
	//lnce_root->tid = s_thread_create(s_client_main, lnce_root->window);
	//s_client_atevent(lnce_root->window, lnce_atevent);
	//s_client_atexit(lnce_root->window, lnce_atexit);
	lnce_root->running = 1;

	install_timer(20, lnce_timer, NULL);

	return NULL;
}

static struct graphics_device * lnce_init_device (void)
{
        char *vbuf;
	lnce_device_t *wd;
	struct graphics_device *gd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	wd = (lnce_device_t *) malloc(sizeof(lnce_device_t));
	wd->update = (GUIRect) {-1, -1, -1, -1};
	gd = (struct graphics_device *) malloc(sizeof(struct graphics_device));

	wd->title = NULL;

	wd->surface = get_window_gc(lnce_root->window);
	//vbuf = (char *) malloc(lnce_root->window->surface->buf->w * lnce_root->window->surface->buf->h * lnce_root->window->surface->bytesperpixel);
	//s_getsurfacevirtual(wd->surface, lnce_root->window->surface->buf->w , lnce_root->window->surface->buf->h, lnce_root->window->surface->bitsperpixel, vbuf);

	gd->size.x1 = 0;
	gd->size.x2 = lnce_root->window->object.rect.w;
	gd->size.y1 = 0;
	gd->size.y2 = lnce_root->window->object.rect.h;
	gd->clip.x1 = 0;
	gd->clip.x2 = gd->size.x2;
	gd->clip.y1 = 0;
	gd->clip.y2 = gd->size.y2;

	gd->drv = &nce_driver;
	gd->driver_data = wd;
	gd->user_data = NULL;

	//s_thread_mutex_lock(lnce_root->gd->mut);
	//s_list_add(lnce_root->gd->list, gd, -1);
	lnce_root->gd->active = gd;
	//s_thread_mutex_unlock(lnce_root->gd->mut);

	return gd;
}

static void lnce_shutdown_device (struct graphics_device *dev)
{	
   /*     int acc = 0;
        int pos = 0;
	lnce_device_t *wd;
	struct graphics_device *gd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	//s_thread_mutex_lock(lnce_root->gd->mut);
	while (!s_list_eol(lnce_root->gd->list, pos)) {
		gd = (struct graphics_device *) s_list_get(lnce_root->gd->list, pos);
		if (gd == dev) {
			s_list_remove(lnce_root->gd->list, pos);
			if (lnce_root->gd->list->nb_elt > 0) {
				lnce_root->gd->active = (struct graphics_device *) s_list_get(lnce_root->gd->list, 0);
				acc = 1;
			} else {
				lnce_root->gd->active = NULL;
			}
			break;
		}
		pos++;
	}*/
	unregister_bottom_half(lnce_surface_register_update, dev);
	/*wd = (lnce_device_t *) dev->driver_data;
	free(wd->title);
	free(wd->surface->vbuf);
	free(wd->surface);
	free(wd);
	free(dev);
	//s_thread_mutex_unlock(lnce_root->gd->mut);

	if (acc && lnce_root->running) {
		char *title;
		struct rect r;
		r.x1 = 0;
		r.y1 = 0;
		r.x2 = lnce_root->window->surface->buf->w;
		r.y2 = lnce_root->window->surface->buf->h;
		title = strdup(((lnce_device_t *) lnce_root->gd->active->driver_data)->title);
		lnce_set_title(lnce_root->gd->active, title);
		lnce_root->gd->active->resize_handler(lnce_root->gd->active);
		lnce_root->gd->active->redraw_handler(lnce_root->gd->active, &r);
		free(title);
	}*/
}

static void lnce_shutdown_driver (void)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

        nce_exit();
}

static unsigned char * lnce_driver_param (void)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

static int lnce_get_empty_bitmap (struct bitmap *dest)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	dest->data = (char *) malloc(dest->x * dest->y * bytesperpixel);
	dest->skip = dest->x * bytesperpixel;
	dest->flags = 0;

	return 0;
}

static void lnce_register_bitmap (struct bitmap *bmp)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
}

static void * lnce_prepare_strip (struct bitmap *bmp, int top, int lines)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

static void lnce_commit_strip (struct bitmap *bmp, int top, int lines)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

static void lnce_unregister_bitmap (struct bitmap *bmp)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	free(bmp->data);
}

#define	CLIP_PREFACE \
	if ((x >= dev->clip.x2) || ((x + xs) <= dev->clip.x1)) return;\
	if ((y >= dev->clip.y2) || ((y + ys) <= dev->clip.y1)) return;\
	if ((x + xs) > dev->clip.x2) xs = dev->clip.x2 - x;\
	if ((y + ys) > dev->clip.y2) ys = dev->clip.y2 - y;\
	if ((dev->clip.x1 - x) > 0){\
		xs -= (dev->clip.x1 - x);\
		data += bytesperpixel * (dev->clip.x1 - x);\
		x = dev->clip.x1;\
	}\
	if ((dev->clip.y1 - y) > 0) {\
		ys -= (dev->clip.y1 - y);\
		data += hndl->skip * (dev->clip.y1 - y);\
		y = dev->clip.y1;\
	}

static void lnce_draw_bitmap (struct graphics_device *dev, struct bitmap *hndl, int x, int y)
{
	lnce_device_t *wd;
	int xs = hndl->x;
	int ys = hndl->y;
	char *data = hndl->data;
	GUIBitmap *map;
	//gc_t *g;
	GUIAllocation rect = {0,0,hndl->x,hndl->y};

	//g = get_window_gc(lnce_root->window);

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	map = nce_create_bitmap_with_data(rect,data,bytesperpixel);
	CLIP_PREFACE;

        if (lnce_root->running == 0) return;
        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;
	gc_draw_bitmap(wd->surface,map,x, y, xs, ys,
					map->rect.w,map->rect.h);
    //    s_putboxpart(wd->surface, x, y, xs, ys, hndl->x, hndl->y, data, 0, 0);
	lnce_surface_update(dev, x, y, xs, ys);
	release_bitmap(map);
	//s_thread_mutex_unlock(lnce_root->gd->mut);
}

static void lnce_draw_bitmaps (struct graphics_device *dev, struct bitmap **hndls, int n, int x, int y)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

static long lnce_get_color (int rgb)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	//return surface_rgb_color(lnce_root->window->surface, (rgb >> 0x10) & 0xFF,
	//                                               (rgb >> 0x08) & 0xFF,
	  //                                             (rgb << 0x00) & 0xFF);
	  return rgb;
}

#define FILL_CLIP_PREFACE \
	if ((left >= right) || (top >= bottom)) return;\
	if ((left >= dev->clip.x2) || (right <= dev->clip.x1) || (top >= dev->clip.y2) || (bottom <= dev->clip.y1)) return;\
	if (left < dev->clip.x1) left = dev->clip.x1;\
	if (right > dev->clip.x2) right = dev->clip.x2;\
	if (top < dev->clip.y1) top = dev->clip.y1;\
	if (bottom > dev->clip.y2) bottom = dev->clip.y2;

static void lnce_fill_area (struct graphics_device *dev, int left, int top, int right, int bottom, long color)
{
	lnce_device_t *wd;
	color_t c;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	FILL_CLIP_PREFACE;

        if (lnce_root->running == 0) return;
        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;
	//s_fillbox(wd->surface, left, top, right - left, bottom - top, color);
	c = gc_get_fg_color(wd->surface);
	gc_set_fg_color(wd->surface,color);
	Rectangle (wd->surface, left, top, right, bottom);
	gc_set_fg_color(wd->surface,c);
	lnce_surface_update(dev, left, top, right - left, bottom - top);
	//s_thread_mutex_unlock(lnce_root->gd->mut);
}

#define HLINE_CLIP_PREFACE \
	if (left >= right) return;\
	if ((y < dev->clip.y1) || (y >= dev->clip.y2) || (right <= dev->clip.x1) || (left >= dev->clip.x2)) return;\
	if (left < dev->clip.x1) left = dev->clip.x1;\
	if (right > dev->clip.x2) right = dev->clip.x2;

#if 0
static void lnce_draw_hline (struct graphics_device *dev, int left, int y, int right, long color)
{
	lnce_device_t *wd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	HLINE_CLIP_PREFACE;

        if (lnce_root->running == 0) return;
        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;
	s_hline(wd->surface, left, y, right, color);
	lnce_surface_update(dev, left, y, right - left, 1);
	//s_thread_mutex_unlock(lnce_root->gd->mut);
}

#define VLINE_CLIP_PREFACE \
	if (top >= bottom) return;\
	if ((x < dev->clip.x1) || (x >= dev->clip.x2) || (top >= dev->clip.y2) || (bottom <= dev->clip.y1)) return;\
	if (top < dev->clip.y1) top = dev->clip.y1;\
	if (bottom > dev->clip.y2) bottom = dev->clip.y2;

static void lnce_draw_vline (struct graphics_device *dev, int x, int top, int bottom, long color)
{
	lnce_device_t *wd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	VLINE_CLIP_PREFACE;

        if (lnce_root->running == 0) return;
        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;
	s_vline(wd->surface, x, top, bottom, color);
	lnce_surface_update(dev, x, top, 1, bottom - top);
	//s_thread_mutex_unlock(lnce_root->gd->mut);
}
#else

void
nce_draw_line (gc_t       *gc,
	       int         x1,
	       int         y1,
	       int         x2,
	       int         y2)
{ 
  
  MoveToEx (gc, x1, y1, NULL);
  LineTo (gc, x2, y2);
  /* LineTo doesn't draw the last point, so if we have a pen width of 1,
   * we draw the end pixel separately... With wider pens it hopefully
   * doesn't matter?
   */
 // if (gc_private->pen_width == 1)
  //  if (!LineTo (gc, x2 + 1, y2))
   //   g_warning ("gdk_draw_line: LineTo #2 failed");
}

static void lnce_draw_hline(struct graphics_device *dev, int left, int y, int right, long color)
{
#ifdef X_DEBUG
	MESSAGE("lnce_draw_hline\n");
#endif
	lnce_device_t *wd;

	if (lnce_root->running == 0) return;
	//s_thread_mutex_lock(lnce_root->gd->mut);
	if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;

	if (left>=right)return;
	if ((y>=dev->clip.y2)||(y<dev->clip.y1)) return;
	if (right<=dev->clip.x1||left>=dev->clip.x2)return;
	//XSetForeground(x_display,x_normal_gc,color);
	gc_set_fg_color(wd->surface,color);
	nce_draw_line(wd->surface,
		left,y,right-1,y
	);
	//X_FLUSH();
}


static void lnce_draw_vline(struct graphics_device *dev, int x, int top, int bottom, long color)
{
	lnce_device_t *wd;

	if (lnce_root->running == 0) return;
	//s_thread_mutex_lock(lnce_root->gd->mut);
	if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;
#ifdef X_DEBUG
	MESSAGE("lnce_draw_vline\n");
#endif
	if (top>=bottom)return;
	if ((x>=dev->clip.x2)||(x<dev->clip.x1)) return;
	if (bottom<=dev->clip.y1||top>=dev->clip.y2)return;
	//XSetForeground(x_display,x_normal_gc,color);
	gc_set_fg_color(wd->surface,color);
	nce_draw_line(
		wd->surface,
		x,top,x,bottom-1
	);
	//X_FLUSH();
}
#endif

#define HSCROLL_CLIP_PREFACE \
	if (!sc) return 0;\
	if (sc > (dev->clip.x2 - dev->clip.x1) || -sc > (dev->clip.x2 - dev->clip.x1))\
		return 1;

static int lnce_hscroll (struct graphics_device *dev, struct rect_set **ignore, int sc)
{
	GUIRect rect;
	lnce_device_t *wd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	HSCROLL_CLIP_PREFACE;

	if (lnce_root->running == 0) return;
	//s_thread_mutex_lock(lnce_root->gd->mut);
	if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;

	ignore = NULL;

	rect.x = dev->clip.x1;
	rect.y = dev->clip.y1;
	rect.w = dev->clip.x2 - dev->clip.x1;
	rect.h = dev->clip.y2 - dev->clip.y1;
	

    //s_copybox(wd->surface, rect.x, rect.y, rect.w, rect.h, rect.x + sc, rect.y);
	nce_bitmap_copy_wh(wd->surface,rect.x, rect.y,wd->surface,rect.x+sc, rect.y, rect.w,rect.h);
	lnce_surface_update(dev, rect.x, rect.y, rect.w, rect.h);
	//s_thread_mutex_unlock(lnce_root->gd->mut);

        return 1;
}



#define VSCROLL_CLIP_PREFACE \
	if (!sc) return 0;\
	if (sc > dev->clip.y2 - dev->clip.y1 || -sc > dev->clip.y2 - dev->clip.y1) return 1;

static int lnce_vscroll (struct graphics_device *dev, struct rect_set **ignore, int sc)
{
	GUIRect rect;
	lnce_device_t *wd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	VSCROLL_CLIP_PREFACE;

        if (lnce_root->running == 0) return;
        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;

	ignore = NULL;

	rect.x = dev->clip.x1;
	rect.y = dev->clip.y1;
	rect.w = dev->clip.x2 - dev->clip.x1;
	rect.h = dev->clip.y2 - dev->clip.y1;

 	nce_bitmap_copy_wh(wd->surface,rect.x, rect.y,wd->surface,rect.x, rect.y+sc, rect.w,rect.h);
   //    s_copybox(wd->surface, rect.x, rect.y, rect.w, rect.h, rect.x, rect.y + sc);
	//lnce_surface_update(dev, rect.x, rect.y, rect.w, rect.h);
	//s_thread_mutex_unlock(lnce_root->gd->mut);

	return 1;
}

static void lnce_set_clip_area (struct graphics_device *dev, struct rect *r)
{
	lnce_device_t *wd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

        //s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		//s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}

	wd = (lnce_device_t *) dev->driver_data;

	memcpy(&dev->clip, r, sizeof(struct rect));
	if ((dev->clip.x1 >= dev->clip.x2) ||
	    (dev->clip.y2 <= dev->clip.y1) ||
	    (dev->clip.y2 <= 0) ||
	    (dev->clip.x2 <= 0) ||
	    (dev->clip.x1 >= lnce_root->window->object.rect.w) ||
	    (dev->clip.y1 >=lnce_root->window->object.rect.h)) {
		dev->clip.x1 = dev->clip.x2 = dev->clip.y1 = dev->clip.y2 = 0;
	} else {
		if (dev->clip.x1 < 0) dev->clip.x1 = 0;
		if (dev->clip.x2 > lnce_root->window->object.rect.w) dev->clip.x2 = lnce_root->window->object.rect.w;
		if (dev->clip.y1 < 0) dev->clip.y1 = 0;
		if (dev->clip.y2 >lnce_root->window->object.rect.h) dev->clip.y2 =lnce_root->window->object.rect.h;
	}
	
	//s_thread_mutex_unlock(lnce_root->gd->mut);
}

static int lnce_block (struct graphics_device *dev)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

static void lnce_unblock (struct graphics_device *dev)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

static void lnce_set_title (struct graphics_device *dev, unsigned char *title)
{
	lnce_device_t *wd;

	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);

	wd = (lnce_device_t *) dev->driver_data;
	free(wd->title);
	wd->title = strdup(title);

        ////s_thread_mutex_lock(lnce_root->gd->mut);
        if (lnce_root->gd->active != dev) {
		////s_thread_mutex_unlock(lnce_root->gd->mut);
		return;
	}


	nce_set_window_caption(lnce_root->window, title);
	//s_thread_mutex_unlock(lnce_root->gd->mut);

}

static int lnce_exec (unsigned char *command, int flag)
{
	DEBUGF ("%s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	exit(0);
}

struct graphics_driver nce_driver = {
	"nce",
	lnce_init_driver,
	lnce_init_device,
	lnce_shutdown_device,
	lnce_shutdown_driver,
	lnce_driver_param,
	lnce_get_empty_bitmap,
	lnce_register_bitmap,
	lnce_prepare_strip,
	lnce_commit_strip,
	lnce_unregister_bitmap,
	lnce_draw_bitmap,
	lnce_draw_bitmaps,
	lnce_get_color,
	lnce_fill_area,
	lnce_draw_hline,
	lnce_draw_vline,
	lnce_hscroll,
	lnce_vscroll,
	lnce_set_clip_area,
	lnce_block,
	lnce_unblock,
	lnce_set_title,
	lnce_exec,
	0,
	0,
	0,
	0,
};

#endif
