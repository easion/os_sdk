/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_search_h_
#define __dj_include_search_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct qelem {
  struct qelem *q_forw;
  struct qelem *q_back;
  char q_data[0];
} qelem;

void insque(struct qelem *_elem, struct qelem *_pred);
void remque(struct qelem *_elem);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_search_h_ */
