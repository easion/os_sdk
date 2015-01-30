/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_stddef_h_
#define __dj_include_stddef_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#undef NULL  
#define NULL 0
#define offsetof(s_type, mbr) ((size_t) &((s_type *)0)->mbr)

typedef int ptrdiff_t;

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_stddef_h_ */
