/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>
#include <libc/dosio.h>
#include <assert.h>
void _dosemu_flush(int handle)
{
 /*_io_struct *sh=dosemu_getiostruct(handle);
 if(!sh) return;
 if(sh->file_type!=DOSEMU_FILE_NORMAL) return;
 dosemu_flush(sh);*/
}
int fsync(int _fd)
{
 _dosemu_flush(_fd);
 return 0;
}
