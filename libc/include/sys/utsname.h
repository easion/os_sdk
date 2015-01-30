/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_sys_utsname_h_
#define __dj_include_sys_utsname_h_

#ifdef __cplusplus
extern "C" {
#endif

struct utsname {
  char machine[9];
  char nodename[32];
  char release[9];
  char sysname[9];
  char version[9];
};

int	uname(struct utsname *name);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_utsname_h_ */
