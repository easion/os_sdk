/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_wctype_h_
#define __dj_include_wctype_h_

/* Bare bones header to satisfy SGI STL's basic_string<> */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/djtypes.h>

#ifndef WEOF
#define WEOF ((wint_t)(-1))
#endif

/* Implementation defined types */
typedef unsigned short wctype_t;
typedef const unsigned char *wctrans_t;

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_wctype_h_ */

