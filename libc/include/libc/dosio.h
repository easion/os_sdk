/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_dosio_h__
#define __dj_include_libc_dosio_h__

#ifdef __cplusplus
extern "C" {
#endif

/* set to O_BINARY or O_TEXT */
extern char *__file_handle_modes;
extern void __file_handle_set(int fd, int mode);

int __doserr_to_errno(int doserr);

int __libc_execute_file(int __argc,char ** __argv,char ** __envp);

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_dosio_h__ */
