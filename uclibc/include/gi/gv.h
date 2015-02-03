
#ifndef __GIX_GV_H__
#define __GIX_GV_H__ 1


#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int gi_time_t;
typedef unsigned int XvPortID;


#define LSBFirst           0
#define BSBFirst           1

#define XvRGB           0
#define XvYUV           1

#define XvPacked        0
#define XvPlanar        1

#define XvTopToBottom   0
#define XvBottomToTop   1



#define FOURCC_YUY2 0x32595559
#define FOURCC_UYVY 0x59565955
#define FOURCC_IA44 0x34344149
#define FOURCC_AI44 0x34344941
#define FOURCC_YV12 0x32315659
#define FOURCC_I420 0x30323449



#define VIDEO_NO_CLIPPING                       0x00000001
#define VIDEO_INVERT_CLIPLIST                   0x00000002
#define VIDEO_OVERLAID_IMAGES                   0x00000004
#define VIDEO_OVERLAID_STILLS                   0x00000008
#define VIDEO_CLIP_TO_VIEWPORT                  0x00000010

typedef struct {
  int id;
  int type;
  int byte_order;
  unsigned char guid[16];
  int bits_per_pixel;
  int format;
  int num_planes;

  /* for RGB formats only */
  int depth;
  unsigned int red_mask;
  unsigned int green_mask;
  unsigned int blue_mask;

  /* for YUV formats only */
  unsigned int y_sample_bits;
  unsigned int u_sample_bits;
  unsigned int v_sample_bits;
  unsigned int horz_y_period;
  unsigned int horz_u_period;
  unsigned int horz_v_period;
  unsigned int vert_y_period;
  unsigned int vert_u_period;
  unsigned int vert_v_period;
  char component_order[32];
  int scanline_order;
} XF86ImageRec, *XF86ImagePtr;


typedef struct {
  int numerator;
  int denominator;
} XvRationalRec, *XvRationalPtr;


typedef struct {
  int id;
  //ScreenPtr pScreen;
  char *name;
  unsigned short width, height;
  XvRationalRec rate;
} XvEncodingRec, *XvEncodingPtr;

typedef struct _XvAttributeRec {
  int flags;
  int min_value;
  int max_value;
  char name[32];
} XvAttributeRec, *XvAttributePtr;

typedef struct {
  char depth;
  unsigned long visual;
} XvFormatRec, *XvFormatPtr;



typedef struct {
  int id;
  int type;
  int byte_order;
  char guid[16];
  int bits_per_pixel;
  int format;
  int num_planes;

  /* for RGB formats only */
  int depth;
  unsigned int red_mask;       
  unsigned int green_mask;   
  unsigned int blue_mask;   

  /* for YUV formats only */
  unsigned int y_sample_bits;
  unsigned int u_sample_bits;
  unsigned int v_sample_bits;   
  unsigned int horz_y_period;
  unsigned int horz_u_period;
  unsigned int horz_v_period;
  unsigned int vert_y_period;
  unsigned int vert_u_period;
  unsigned int vert_v_period;
  char component_order[32];
  int scanline_order;
} XvImageRec, *XvImagePtr; 

typedef struct {
  unsigned long id;
  void* client;
} XvGrabRec, *XvGrabPtr;



typedef struct {
  //XvEncodingID encoding_id;
  char *name;
  unsigned long width;
  unsigned long height;
  XvRationalRec rate;
  unsigned long num_encodings;
} XvEncodingInfo;



typedef struct {
  int id;
  int width, height;
  int data_size;              /* bytes */
  int num_planes;
  char *data;

  int pitches[16];               /* bytes */
  int offsets[16];               /* bytes */
  void* obdata;

} XvImage;

/*
typedef struct 
{
  int w, h;
  char *buf;
  uint32_t format; //rgb or bgr
  int data_size;
  int num_planes;
  int *pitches;
  int *offsets;
  int user;
  struct GI_server_gc *gcptr;
}gi_gv_image_t;
*/



typedef struct {
  XvPortID base_id;
  unsigned long num_ports;
  char type;
  char name[32];
  unsigned long num_formats;
  //XvFormatRec *formats;
  XvFormatRec formats[8];
  unsigned long num_adaptors;
} XvAdaptorInfo;



#ifdef __KERNEL__

struct video_adaptor
{
  struct video_adaptor *next;
  unsigned long base_id;
  unsigned char type; 
  char name[32];
  int nEncodings;
  XvEncodingPtr pEncodings;  
  int nFormats;
  XvFormatPtr pFormats; 
  int nAttributes;
  XvAttributePtr pAttributes;
  int nImages;
  XvImagePtr pImages;
  int nPorts;
  gi_application_t* port_grab_client;
  gi_server_window_t *video_output_window;

  int (*s_get_port_attribute) ( gi_atom_id_t attribute,
                                     int32_t *value,
                                     void* data);
  int (*s_set_port_attribute) ( gi_atom_id_t attribute,
                                     int32_t value,
                                     void* data);

  //struct _XvPortRec *pPorts;
  void (*s_query_best_size) ( gi_bool_t motion, short vid_w, short vid_h,
                                   short drw_w, short drw_h,
                                   unsigned int *p_w, unsigned int *p_h, void* data);
  int (*s_video_put_image)( short src_x, short src_y, short src_w, short src_h, 
	  short drw_x, short drw_y, short drw_w, short drw_h, XvImage* image, gi_bool_t sync, void* data);
  int (*s_video_stop)(void* data, gi_bool_t cleanup);
  int (*s_query_image_attributes)(int id, unsigned short *width, unsigned short *height,
                                         int *pitches, int *offsets);
};


int register_video_adapotr(struct video_adaptor *va);
int unregister_video_adapotr(struct video_adaptor *va);
struct video_adaptor *get_video_adapotr(int port);

/* Basic line-based copy for packed formats */
static inline void packed_line_copy(int w, int h, int stride, uint8_t *src, uint8_t *dest)
{
  int i;
  int len = w * 2;
  for (i = 0; i < h; i++)
  {
    memcpy(dest + i * len, src + i * stride, len);
  }
}


void uv12_to_uyvy(int w, int h, int y_pitch, int uv_pitch, uint8_t *y_p, uint8_t *u_p, uint8_t *v_p, uint8_t *dest);
#else

int gv_grab_port(XvPortID port,gi_time_t time);
int gv_ungrab_port(XvPortID port,gi_time_t time);
int gv_query_adaptors(gi_window_id_t window, unsigned int *p_nAdaptors, XvAdaptorInfo **p_pAdaptors);
int gv_put_image ( XvPortID port, gi_window_id_t d, gi_gc_ptr_t gc, XvImage *image, 
	int src_x, int src_y, unsigned int src_w, unsigned int src_h, 
	int dest_x, int dest_y, unsigned int dest_w, unsigned int dest_h);
XvImage * gv_create_image (XvPortID port, int id, char *data, int width, int height) ;
XF86ImageRec * gv_list_image_formats (XvPortID port, int *num);
XvAttributeRec* gv_query_port_attributes(XvPortID port, int *num);
void gv_free_adaptorInfo(XvAdaptorInfo *pAdaptors);


#endif


#ifdef __cplusplus
}
#endif


#endif

