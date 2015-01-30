/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_ctype_h_
#define __dj_include_ctype_h_

#ifdef __cplusplus
extern "C" {
#endif
#define	_UPPER		0x0001
#define	_LOWER		0x0002
#define	_DIGIT		0x0004
#define	_SPACE		0x0008 /* HT  LF  VT  FF  CR  SP */
#define	_PUNCT		0x0010
#define	_CONTROL	0x0020
#define	_BLANK		0x0040 /* this is SP only, not SP and HT as in C99  */
#define	_HEX		0x0080
#define	_LEADBYTE	0x8000

#define	_ALPHA		0x0103
int	isalnum(int c);
int	isalpha(int c);
int	iscntrl(int c);
int	isdigit(int c);
int	isgraph(int c);
int	islower(int c);
int	isprint(int c);
int	ispunct(int c);
int	isspace(int c);
int	isupper(int c);
int	isxdigit(int c);
int	tolower(int c);
int	toupper(int c);

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#include <inlines/ctype.ha>
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */
  
int	isascii(int c);
int	toascii(int c);

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#include <inlines/ctype.hd>
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_ctype_h_ */
