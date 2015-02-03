#ifndef _EVAS_ENGINE_GIX_H
#define _EVAS_ENGINE_GIX_H

#include <gi/gi.h>

typedef struct 
{
	int r,g,b;
}*Colormap;
//typedef struct _Evas_Engine_Info_Software_X11              Evas_Engine_Info_Software_X11;


typedef struct _Evas_Engine_Info_Gix Evas_Engine_Info_Gix;

struct _Evas_Engine_Info_Gix
{
   /* PRIVATE - don't mess with this baby or evas will poke its tongue out */
   /* at you and make nasty noises */
   Evas_Engine_Info magic;

   /* engine specific data & parameters it needs to set up */
   struct {
      //Display  *display;
      gi_window_id_t  drawable;
      gi_window_id_t    mask;
      gi_screen_info_t   *visual;
      Colormap  colormap;
      int       depth;
      int       rotation;

      int       alloc_grayscale : 1;
      int       debug : 1;
      int       shape_dither : 1;
      int       destination_alpha : 1;
      int       track_mask_changes : 1;

      int       alloc_colors_max;
   } info;
   /* engine specific function calls to query stuff about the destination */
   /* engine (what visual & colormap & depth to use, performance info etc. */
   struct {
      gi_screen_info_t *  (*best_visual_get)   ( int screen);
      Colormap  (*best_colormap_get) ( int screen);
      int       (*best_depth_get)    ( int screen);

      Evas_Performance *(*performance_test)         (Evas *e,  gi_screen_info_t *vis, Colormap cmap, gi_window_id_t draw, int depth);
      void              (*performance_free)         (Evas_Performance *perf);
      char *            (*performance_data_get)     (Evas_Performance *perf);
      char *            (*performance_key_get)      (Evas_Performance *perf);
      Evas_Performance *(*performance_new)          (Evas *e,  gi_screen_info_t *vis, Colormap cmap, gi_window_id_t draw, int depth);
      void              (*performance_build)        (Evas_Performance *perf, const char *data);
      void              (*performance_device_store) (Evas_Performance *perf);
   } func;
   
   int mask_changed
};
#endif


