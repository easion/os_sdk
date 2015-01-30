/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include "dirstruc.h"

struct dirent * readdir(DIR *dir)
{
 int i;
again:
 i=__libc_emu_readdir(&dir->ri,dir->cur_ent,&dir->de);
 switch(i)
 {
  case 0:		/* OK */
   dir->cur_ent++;
   return &dir->de;
  case 1:		/* not dir */
   return NULL;
  case -1:		/* out of range */
   return NULL;
  case -2:		/* not exists */
   return NULL;
  case -3:		/* deleted entry */
   dir->cur_ent++;
   goto again;
 }
 return NULL;
}
