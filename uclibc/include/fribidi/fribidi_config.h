
#define FRIBIDI_PACKAGE "fribidi"

#define FRIBIDI_VERSION "0.10.4"
#define FRIBIDI_MAJOR_VERSION 0
#define FRIBIDI_MINOR_VERSION 10
#define FRIBIDI_MICRO_VERSION_STR "4"
#define FRIBIDI_INTERFACE_VERSION 2
#define FRIBIDI_INTERFACE_VERSION_STR "2"

#if 0
#define FRIBIDI_NO_CHARSETS 1
#else
#undef FRIBIDI_NO_CHARSETS
#endif

#if defined(WIN32) && !defined(__MINGW32__)
#ifdef FRIBIDI_EXPORTS
#define FRIBIDI_API __declspec(dllexport)
#else
#define FRIBIDI_API __declspec(dllimport)
#endif
#else
#define FRIBIDI_API
#endif


