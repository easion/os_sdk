/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <dirent.h>
#include "dirstruc.h"

void rewinddir(DIR *dir)
{
 dir->cur_ent = 0;
}
