#ifndef _ECORE_STR_H
# define _ECORE_STR_H

#ifdef EAPI
#undef EAPI
#endif
#ifdef _MSC_VER
# ifdef BUILDING_DLL
#  define EAPI __declspec(dllexport)
# else
#  define EAPI __declspec(dllimport)
# endif
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif

/**
 * @file Ecore_Str.h
 * @brief Contains useful C string functions.
 */

# ifdef __cplusplus
extern "C" {
# endif

# ifdef __sgi
#  define __FUNCTION__ "unknown"
#  ifndef __cplusplus
#   define inline
#  endif
# endif


/* strlcpy implementation for libc's lacking it */
EAPI size_t ecore_strlcpy(char *dst, const char *src, size_t siz);
EAPI size_t ecore_strlcat(char *dst, const char *src, size_t siz);

EAPI int ecore_str_has_prefix(const char *str, const char *prefix);

EAPI int ecore_str_has_suffix(const char *str, const char *suffix);
EAPI char **ecore_str_split(const char *string, const char *delimiter, 
                            int max_tokens);

#ifdef __cplusplus
}
#endif

#endif				/* _ECORE_STR_H */
