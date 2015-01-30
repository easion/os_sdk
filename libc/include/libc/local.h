/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_local_h__
#define __dj_include_libc_local_h__

#ifdef __cplusplus
extern "C" {
#endif

FILE *	__alloc_file(void);

/* A FILE* is considered "free" if its flag is zero. */

#define __FILE_REC_MAX 20
typedef struct __file_rec {
  struct __file_rec *next;
  int count;
  FILE *files[__FILE_REC_MAX];
} __file_rec;

extern __file_rec *__file_rec_list;

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_local_h__ */
