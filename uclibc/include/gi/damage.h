

#ifndef __GIX_DAMAGE_H__
#define __GIX_DAMAGE_H__ 1


#ifdef __cplusplus
extern "C" {
#endif


int gi_region_create(gi_boxrec_t *rects,int count);
int gi_region_destroy(gi_id_t region_id);
int gi_region_set(gi_id_t region_id,gi_boxrec_t *rects, int count);
int gi_region_copy(gi_id_t dst_id,gi_id_t src_id);
int gi_region_extents(gi_id_t region_id, gi_id_t src);
int gi_region_fetch(gi_id_t region_id,gi_boxrec_t *rects, int count);
int gi_region_expand(gi_id_t dst, gi_id_t src,int left,  int right, int top, int bottom);
int gi_region_translate(gi_id_t region_id, int dx, int dy);
int gi_region_union(gi_id_t dst_id, gi_id_t src1, gi_id_t src2);
int gi_region_intersect(gi_id_t dst_id, gi_id_t src1, gi_id_t src2);
int gi_region_subtract(gi_id_t dst_id, gi_id_t src1, gi_id_t src2);


int gi_damage_create(gi_id_t damage_id, int mode);
int gi_damage_destroy(gi_id_t damage_id);
int gi_damage_get(gi_id_t damage_id, gi_id_t region_id);
int gi_damage_subtract(gi_id_t damage_id, gi_id_t repair, gi_id_t parts);
int gi_damage_add(gi_id_t damage_id,gi_id_t region_id);

int gi_composite_dirty_region(gi_window_id_t id, gi_id_t region_id);
int gi_composite_redirect_subwindows(gi_window_id_t id, int mode);
int gi_composite_get_window_pixmap(gi_window_id_t id, void **mem, int *memsize);

#ifdef __cplusplus
}
#endif


#endif



