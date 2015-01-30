/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_atexit_h__
#define __dj_include_libc_atexit_h__

#ifdef __cplusplus
extern "C" {
#endif

struct __atexit {
  struct __atexit *__next;
  void (*__function)(void);
};

extern struct __atexit *__atexit_ptr;

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_atexit_h__ */
