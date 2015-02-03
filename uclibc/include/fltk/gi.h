
#ifndef fltk_gi_h
# define fltk_gi_h


#define TRACE_HERE do{\
	printf("File %s:Got %s() line%d Not defined\n",__FILE__,__FUNCTION__,__LINE__);\
}\
while (0)


////////////////////////////////////////////////////////////////
// Try to get the parts of Xlib.h included while avoiding warnings:

#  ifndef DOXYGEN
#   define Window gi_window_id_t

// pragmas are to fix the broken SGI Irix Xlib header files:
#   if !defined(__GNUC__) && (defined(_ABIN32) || defined(_ABI64))
#    pragma set woff 3322
#   endif
#   include <gi/gi.h>
#include <gi/region.h>
#include <gi/property.h>
#   if !defined(__GNUC__) && (defined(_ABIN32) || defined(_ABI64))
#    pragma reset woff 3322
#   endif


#   if USE_XFT && !MAKEDEPEND
#   else
     typedef struct _XftDraw XftDraw;
     typedef struct _XftFont XftFont;
#   endif


#   undef Window

#   if defined(__FreeBSD__) || defined(__APPLE__) || defined(__CYGWIN__)
     typedef unsigned long	ulong;
     typedef unsigned int      	uint;
     typedef unsigned char	uchar;
#   endif

#  endif // !DOXYGEN

#include "draw.h"

extern FL_API gi_region_t*	XRectangleRegion(int x, int y, int w, int h);

namespace fltk {

/// \name fltk/x11.h
//@{

////////////////////////////////////////////////////////////////
// constant info about the X server connection:

extern FL_API void	open_display();
extern FL_API void	open_display_internal();
extern FL_API void	close_display();

extern FL_API int	xdisplay;
extern FL_API gi_window_id_t	message_window;
extern FL_API int	xscreen;
extern FL_API gi_screen_info_t* xvisual;
//extern FL_API Colormap	xcolormap;

////////////////////////////////////////////////////////////////
// event handling:

// feed events into fltk by setting xevent and calling handle:
extern FL_API gi_msg_t	xevent;
extern FL_API bool	handle();

// set by last xevent with a timestamp:
extern FL_API ulong	event_time;

////////////////////////////////////////////////////////////////
// DnD:

extern FL_API gi_window_id_t dnd_source_window;
extern FL_API gi_atom_id_t *dnd_source_types;
extern FL_API gi_atom_id_t dnd_type;
extern FL_API gi_atom_id_t dnd_source_action;
extern FL_API gi_atom_id_t dnd_action;

////////////////////////////////////////////////////////////////
// drawing functions:

//extern FL_API XftDraw*	xftc;
extern FL_API gi_gc_ptr_t	gc;
extern FL_API gi_window_id_t	xwindow;
extern FL_API ulong	current_xpixel;
extern FL_API ulong	xpixel(Color i);
extern FL_API void	clip_region(gi_region_t*);
extern FL_API gi_region_t*	clip_region();

extern FL_API void	draw_into(gi_window_id_t, int w, int h);
extern FL_API void	stop_drawing(gi_window_id_t);

//extern FL_API XFontStruct* xfont();
//extern FL_API XftFont*  xftfont();

////////////////////////////////////////////////////////////////
// only include this if <fltk/Window.h> was included:
#  if defined(fltk_Window_h) || defined(DOXYGEN)

/**
  When fltk tells X about a window, one of these objects is created.
  Warning: this object is highly subject to change!  It's definition
  is only here so that xid(Window) can be declared inline:
*/
class FL_API CreatedWindow {
public:
  gi_window_id_t xid;
  gi_window_id_t backbuffer;
  gi_window_id_t frontbuffer;
  Window *window;
  gi_region_t* region;
  void expose(const Rectangle&);
  CreatedWindow *next;
  bool wait_for_expose;
  bool backbuffer_bad; // used for XDBE
  bool overlay; // true if redraw_overlay was called
  int cursor;
  const Widget* cursor_for;
  static CreatedWindow* first;
  static CreatedWindow* find(const Window* window) {return window->i;}
  void sendxjunk();
  static void create(Window*,		     
		     int background = -1);
  static CreatedWindow* set_xid(Window*, gi_window_id_t);
  Rectangle current_size;
};

// convert xid <-> Window:
inline gi_window_id_t xid(const Window*w) {return CreatedWindow::find(w)->xid;}
Window* find(gi_window_id_t xid);

#  endif // Window_h

//@}

} // namespace fltk

#   if USE_CAIRO
#    include <fltk/fltk_cairo.h>
#    include <cairo-xlib.h>
#   else
     typedef struct _cairo cairo_t;
#   endif

#endif

