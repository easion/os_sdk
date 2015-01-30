/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_libc_file_h__
#define __dj_include_libc_file_h__

#include <fcntl.h>
#include <libc/dosio.h>
#include <libc/ttyprvt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IOREAD   000010
#define _IOWRT    000020
#define _IOMYBUF  000040
#define _IOEOF    000100
#define _IOERR    000200
#define _IOSTRG   000400
#define _IORW     001000
#define _IOAPPEND 002000
#define _IORMONCL 004000  /* remove on close, for temp files */
/* if _flag & _IORMONCL, ._name_to_remove needs freeing */
#define _IOUNGETC 010000  /* there is an ungetc'ed character in the buffer */
#define _IOTERM   020000  /* file's handle hooked by termios */
#define _IONTERM  040000  /* file's handle not hooked by termios */

int	_flsbuf(int, FILE*);
int	_filbuf(FILE *);
void	_fwalk(void (*)(FILE *));

static __inline__ int __getc_raw(FILE *const p)
{
	int ret;
 if(p->_cnt>0)
 {
  p->_cnt--;
  return((unsigned char)*(p->_ptr++));
 }
 ret = (_filbuf(p));
 //printf("ret ch %d", ret);
 return ret;
}

static __inline__ int __putc_raw(int const x,FILE *const p)
{
 if(p->_cnt>0)
 {
  p->_cnt--;
  return((unsigned char)(*(p->_ptr++)=(unsigned char)x));
 }
 return(_flsbuf((unsigned char)x,p));
}

static __inline__ int __is_text_file(FILE *const p)
{
 return 0;
}

static __inline__ int __getc(FILE *const p)
{
 return __getc_raw(p);
}

static __inline__ int __putc(const int x,FILE *const p)
{
 return __putc_raw(x,p);
}

#undef  fileno
#define fileno(f)	(f->_file)
#undef  feof
#define feof(f)		(((f)->_flag&_IOEOF)!=0)
#undef  ferror
#define ferror(f)	(((f)->_flag&_IOERR)!=0)

#ifdef __cplusplus
}
#endif

#endif /* __dj_include_libc_file_h__ */
