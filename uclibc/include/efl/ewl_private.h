/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef _EWL_PRIVATE_H
#define _EWL_PRIVATE_H

#include <Ecore_Str.h>
#include <Ecore_File.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <fnmatch.h>
#include <pwd.h>
#include <grp.h>
#include <langinfo.h>

#ifdef HAVE_CONFIG_H
#include "ewl-config.h"
#endif

#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#if HAVE___ATTRIBUTE__
#define __UNUSED__ __attribute__((unused))
#else
#define __UNUSED__
#endif

/* config keys used by EWL */
#define EWL_CONFIG_DEBUG_ENABLE "/ewl/debug/enable"
#define EWL_CONFIG_DEBUG_LEVEL "/ewl/debug/level"
#define EWL_CONFIG_DEBUG_SEGV "/ewl/debug/segv"
#define EWL_CONFIG_DEBUG_BACKTRACE "/ewl/debug/backtrace"
#define EWL_CONFIG_DEBUG_EVAS_RENDER "/ewl/debug/evas/render"
#define EWL_CONFIG_DEBUG_GC_REAP "/ewl/debug/gc/reap"

#define EWL_CONFIG_CACHE_EVAS_FONT "/ewl/cache/evas/font"
#define EWL_CONFIG_CACHE_EVAS_IMAGE "/ewl/cache/evas/image"

#define EWL_CONFIG_ENGINE_NAME "/ewl/engine/name"
#define EWL_CONFIG_THEME_NAME "/ewl/theme/name"
#define EWL_CONFIG_THEME_ICON_THEME "/ewl/theme/icon/theme"
#define EWL_CONFIG_THEME_ICON_SIZE "/ewl/theme/icon/size"
#define EWL_CONFIG_THEME_PRINT_KEYS "/ewl/theme/print/keys"
#define EWL_CONFIG_THEME_PRINT_SIGNALS "/ewl/theme/print/signals"

#define EWL_CONFIG_THEME_COLOR_CLASSES_OVERRIDE "/ewl/theme/color/classes/override"
#define EWL_CONFIG_THEME_COLOR_CLASSES_COUNT "/ewl/theme/color/classes/count"

extern Ewl_Config *ewl_config;	/**< The system configuration data */

#endif

