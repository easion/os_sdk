


#ifndef __GI_SURFACE_H__
#define __GI_SURFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define G_SURFACE_READ_LOCK 0X01
#define G_SURFACE_WRITE_LOCK 0X02

typedef struct 
{
	long lock_flags;
	gi_window_id_t pixmap;
	gi_window_id_t attched_window;
	pthread_mutex_t lock;
	int refs;
	unsigned long gformat;

	void *phy_mem;
	void *data;
	int data_size;
	int pitch;
	//gi_image_t img;
	int width,height;

	void *font;
	unsigned char fa,fr,fg,fb; //font
	unsigned char sa,sr,sg,sb; //source
	unsigned char da,dr,dg,db; //dest
	gi_cliprect_t rect;
	gi_region_t *vis_region;
	gi_region_t *dirty_region;
	void *private_data;

}gi_surface_t;

#define G_SURFACE_WINDOW(s) ((s)->attched_window)
#define G_SURFACE_PIXMAP(s) ((s)->pixmap)
#define G_SURFACE_BUFFER(s) ((s)->data)
#define G_SURFACE_BUFFER_SIZE(s) ((s)->data_size)
#define G_SURFACE_PITCH(s) ((s)->pitch)
#define G_SURFACE_FORMAT(s) ((s)->gformat)
#define G_SURFACE_WIDTH(s) ((s)->width)
#define G_SURFACE_HEIGHT(s) ((s)->height)

int gi_get_window_surface(gi_window_id_t window, gi_surface_t **res);
void gi_surface_release(gi_surface_t *surface);

int gi_surface_lock(gi_surface_t *surface, void** mem, int *pitch, unsigned lock_flags);
int gi_surface_unlock(gi_surface_t *surface);


#ifdef __cplusplus
}
#endif
#endif


