/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_bss_h_
#define __dj_include_bss_h_

#ifdef __cplusplus
extern "C" {
#endif
/* this gets *incremented* at startup, so that if a program dumps
   itself (emacs) you still have a way of telling.  Compare this value
   with a static, and if it's different, you've been restarted.
   First time through on a non-unexec'd program, it's greater than 0 */

extern int __bss_count;

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_bss_h_ */
