/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_dir_h_
#define __dj_include_sys_dir_h_

#ifdef __cplusplus
extern "C" {
#endif

#define dirent direct
#include <dirent.h>
#undef dirent

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_dir_h_ */
