/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_ftw_h_
#define __dj_include_ftw_h_

#ifdef __cplusplus
extern "C" {
#endif

#define FTW_F   1
#define FTW_D   2
#define FTW_NS  3
#define FTW_DNR 4
#define FTW_VL  5

#include <sys/stat.h>

int     ftw(const char *_dir,
            int (*_fn)(const char *_file, struct stat *_sb, int _flag),
            int _depth);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_ftw_h_ */
