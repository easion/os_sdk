/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_sysmacros_h_
#define __dj_include_sys_sysmacros_h_

#ifdef __cplusplus
extern "C" {
#endif

#define major(x)	((int)(((unsigned)(x) >> 8) & 0xff))
#define minor(x)	((int)((x) & 0xff))

#define makedev(x,y)	((dev_t)(((x) << 8) | (y)))

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_sysmacros_h_ */
