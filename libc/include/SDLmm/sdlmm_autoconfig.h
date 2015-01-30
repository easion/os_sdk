/* src/sdlmm_autoconfig.h.  Generated automatically by configure.  */
/* src/sdlmm_autoconfig.h.in.  Generated automatically from configure.in by autoheader.  */
#ifndef SDLMM_CONFIG_H
#define SDLMM_CONFIG_H
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
#define RCSID(X) \
 static char *rcsid __attribute__ ((unused)) =X
#elif __GNUC__ == 2
#define RCSID(X) \
 static char *rcsid = X; \
 static void *use_rcsid=(&use_rcsid, (void *)&rcsid)
#else
#define RCSID(X) \
 static char *rcsid = X
#endif


/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

#define ASSERTIONS 1

/* Define if you have the <dlfcn.h> header file.  */
#define HAVE_DLFCN_H 1

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* Name of package */
#define PACKAGE "SDLmm"

/* Version number of package */
#define VERSION "0.1.8"

#endif // SDLMM_CONFIG_H
