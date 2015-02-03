/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_stddef_h_
#define __dj_include_stddef_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
typedef unsigned short wchar_t;
#endif
typedef void*  __gnuc_va_list;

#undef NULL  
#define NULL 0
#define offsetof(s_type, mbr) ((size_t) &((s_type *)0)->mbr)

typedef int ptrdiff_t;
typedef long unsigned int size_t;

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_stddef_h_ */
