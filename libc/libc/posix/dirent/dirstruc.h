/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <dir.h>

struct __dj_DIR
{
 int ri;
 struct dirent de;
 int cur_ent;
};
