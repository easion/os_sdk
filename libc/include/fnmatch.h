/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_fnmatch_h_
#define __dj_include_fnmatch_h_

#ifdef __cplusplus
extern "C" {
#endif

#define FNM_NOESCAPE	0x01
#define FNM_PATHNAME	0x02
#define FNM_PERIOD	0x04

#define FNM_NOMATCH	1
#define FNM_ERROR	2

int fnmatch(const char *_pattern, const char *_string, int _flags);

#define FNM_NOCASE	0x08
#define FNM_CASEFOLD	FNM_NOCASE /* compatibility with GNU fnmatch */
#define FNM_IGNORECASE	FNM_NOCASE /* compatibility with Solaris */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_fnmatch_h_ */
