

#ifndef __GI_UFONT_H__
#define __GI_UFONT_H__

#ifdef __cplusplus                     
extern "C" {
#endif

typedef void* gi_ufont_t;

gi_ufont_t* gi_create_ufont(const char *fontname);
int gi_ufont_set_format(gi_ufont_t* hfont, int format);
int gi_delete_ufont(gi_ufont_t* hfont);
int gi_get_family_path(const char *fontname, char *fontpath);
char** gi_list_fonts(const char* match, const int limit , int *count);
int gi_free_fonts_list(char**, int);
int gi_ufont_set_text_attr(gi_gc_ptr_t gc,gi_ufont_t *hfont, BOOL trans, gi_color_t fg, gi_color_t bg);
int gi_ufont_set_size(gi_ufont_t* hfont,int size);
int gi_font_draw_bitmap(gi_ufont_t* hfont, gi_image_t* img, const char *text,int len, int x, int y);
int gi_ufont_draw(gi_gc_ptr_t gc, gi_ufont_t* hfont,const char *text, int x, int y, int len);
int gi_ufont_param(gi_ufont_t* hfont,const char*str,int n, int *w,int *h);

int gi_ufont_ascent_get(gi_ufont_t * fn);
int gi_ufont_descent_get(gi_ufont_t * fn);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
