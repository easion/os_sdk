/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#ifndef __DJ_sys_djtypes_h_
#define __DJ_sys_djtypes_h_

typedef int clock_t;
typedef int gid_t;
typedef int off_t;
typedef int pid_t;

#ifndef __size_t__
#ifndef __SIZE_T__
#define __size_t__
#define __SIZE_T__
typedef long unsigned int size_t;
#endif
#endif


typedef int ssize_t;
typedef unsigned int time_t;
typedef int uid_t;

/* For GCC 3.00 or later we use its builtin va_list.                       */
#if __GNUC__ >= 3
typedef __builtin_va_list va_list;
#else
typedef void *va_list;
#endif

typedef int wint_t;

#ifndef __cplusplus
typedef unsigned short wchar_t;
#endif
#include <sys/jicama.h>

#endif
