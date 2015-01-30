/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_stdiohk_h__
#define __dj_include_libc_stdiohk_h__

#ifdef __cplusplus
extern "C" {
#endif

#define NEEDS_UNDERSCORES

#ifndef NEEDS_UNDERSCORES
__asm__(".long __stdio_cleanup_proc");
#else
__asm__(".long ___stdio_cleanup_proc");
#endif

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_stdiohk_h__ */
