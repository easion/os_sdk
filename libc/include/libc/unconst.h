/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_unconst_h__
#define __dj_include_libc_unconst_h__

#ifdef __cplusplus
extern "C" {
#endif

#define unconst(__v, __t) __extension__ ({union { const __t __cp; __t __p; } __q; __q.__cp = __v; __q.__p;})

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_unconst_h__ */
