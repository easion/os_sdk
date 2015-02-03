/** @file etk_dnd.h */
#ifndef _ETK_DND_H_
#define _ETK_DND_H_

#include "etk_window.h"
#include "etk_types.h"

#define ETK_SELECTION_TARGET_TARGETS "TARGETS"
#define ETK_SELECTION_TARGET_TEXT "TEXT"
#define ETK_SELECTION_TARGET_COMPOUND_TEXT "COMPOUND_TEXT"
#define ETK_SELECTION_TARGET_STRING "STRING"
#define ETK_SELECTION_TARGET_UTF8_STRING "UTF8_STRING"
#define ETK_SELECTION_TARGET_FILENAME "FILENAME"

typedef enum Etk_Selection_Content
{
   ETK_SELECTION_CONTENT_NONE,
   ETK_SELECTION_CONTENT_TEXT,
   ETK_SELECTION_CONTENT_FILES,
   ETK_SELECTION_CONTENT_TARGETS,
   ETK_SELECTION_CONTENT_CUSTOM
} Etk_Selection_Content;

struct Etk_Event_Selection_Request
{
   void *data;
   Etk_Selection_Content content;
};

struct Etk_Selection_Data
{
   unsigned char    *data;
   int               length;

   int             (*free)(void *data);
};

struct Etk_Selection_Data_Files
{
   Etk_Selection_Data data;
   char     **files;
   int        num_files;
};

struct Etk_Selection_Data_Text
{
   Etk_Selection_Data data;
   char     *text;
};


struct Etk_Selection_Data_Targets
{
   Etk_Selection_Data data;
   char **targets;
   int num_targets;
};

/** @} */

#endif
