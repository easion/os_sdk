
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <gi/gi.h>
#include <gi/property.h>

#define WINDOW_WIDTH  760
#define WINDOW_HEIGHT  400

static gi_window_id_t  mainWin;
static gi_gc_ptr_t  gc;
static gi_image_t *bitmap;
static int x0, y0, x1, y1;


static int draw_line(gi_gc_ptr_t gc, gi_coord_t x1, gi_coord_t y1, gi_coord_t x2, gi_coord_t y2)
{
  gi_point_t pts[2];
  int i;

  pts[0].x = x1;
  pts[0].y = y1;
  pts[1].x = x2;
  pts[1].y = y2;

  gi_draw_lines ( gc, pts, 2);
}


static int window_proc(gi_msg_t *msg,void *data)
{
  gi_point_t xp[3];

  switch (msg->type)
  {
    case GI_MSG_CLIENT_MSG:
      if(msg->client.client_type==GA_WM_PROTOCOLS
          &&msg->params[0] == GA_WM_DELETE_WINDOW)
      gi_quit_dispatch();    
    break;

    case GI_MSG_MOUSE_MOVE:
      x1 = msg->x;
      y1 = msg->y;
      draw_line(gc, x0, y0, x1, y1);
      x0 = x1; y0 = y1;
      break;

    case GI_MSG_BUTTON_DOWN:
     if(msg->params[2] & GI_BUTTON_L){
      x0 = msg->x;
      y0 = msg->y;
      draw_line(  gc, x0, y0, x0, y0);
     }
    break;

    case GI_MSG_BUTTON_UP:
      break;

    case GI_MSG_EXPOSURE:
    {
    xp[0].x = WINDOW_WIDTH - 2;
    xp[0].y = 0;
    xp[1].x = 0;
    xp[1].y = 0;
    xp[2].x = 0;
    xp[2].y = WINDOW_HEIGHT - 12;
    gi_draw_lines( gc, xp, 3);

    if (bitmap)
      gi_draw_image(gc,bitmap,0,0);
  }

  break;

  default:
    return gi_default_handler(msg,data);  
  }

  return TRUE;
}

int main( int argc, char **argv ) 
{
  int err;
  gi_msg_t msg;

  gi_init();  

  mainWin = gi_create_window(GI_DESKTOP_WINDOW_ID, 30,20,WINDOW_WIDTH, WINDOW_HEIGHT,GI_RGB( 192, 192, 192 ),GI_FLAGS_NORESIZE);

  if (!mainWin)
    return 1;

  gi_set_events_mask(mainWin, GI_MASK_BUTTON_DOWN | GI_MASK_MOUSE_MOVE| GI_MASK_BUTTON_UP|GI_MASK_CLIENT_MSG
        | GI_MASK_EXPOSURE);

  gi_set_dispatch_handler(mainWin, &window_proc,NULL);
  gc = gi_create_gc((mainWin),NULL);

  gi_set_line_attributes( gc, 15,
         GI_GC_LINE_SOLID, GI_GC_CAP_ROUND, GI_GC_JOIN_MITER);
  
  gi_set_window_caption(mainWin,"paint");
  gi_show_window(mainWin);
  bitmap = NULL;

  err = gi_image_create_from_png("/test.png", &bitmap);

  if (err)
    bitmap = NULL;
 
  while (gi_get_new_message(&msg))
  {
    gi_dispatch_message(&msg);  
  }

  gi_destroy_window(mainWin);
  gi_destroy_gc(gc);
  gi_destroy_image(bitmap);
  return 0;
}
