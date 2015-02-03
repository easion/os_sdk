/** @file etk_selection.h */
#ifndef _ETK_SELECTION_H_
#define _ETK_SELECTION_H_

#include "etk_types.h"

/* TODO/FIXME list:
 * - support non-UTF8 text
 * - support non-text content
 */

/**
 * @defgroup Etk_Selection The selection and clipboard system of Etk
 * @brief Some functions to manipulate the clipboard and the selections
 * @{
 */

/** @brief The different types of selection */
typedef enum
{
   ETK_SELECTION_PRIMARY,       /**< The primary selection: used when a text is selected.
                                 * Its content is traditionally pasted when the middle button of the mouse is pressed */
   ETK_SELECTION_SECONDARY,     /**< The secondary selection: almost never used */
   ETK_SELECTION_CLIPBOARD      /**< The clipboard: used when Ctrl+X/C/V is pressed (traditional copy/paste) */
} Etk_Selection_Type;

/** @brief The different types of content of a selection */
typedef enum
{
   ETK_SELECTION_TEXT           /**< The content of the selection is a text */
} Etk_Selection_Content_Type;


/**
 * @brief The event structure sent to the target widget when the content
 * of a selection is received after a request (through the signal "selection_received")
 * @structinfo
 */
struct Etk_Selection_Event
{
   Etk_Selection_Type from;             /**< The selection where the content has been requested from */
   Etk_Selection_Content_Type type;     /**< The type of content received */
   union
   {
      const char *text;                 /**< The text corresponding to the type ETK_SELECTION_TEXT */
   } data;                              /**< The content of the selection */
};


void etk_selection_text_set(Etk_Selection_Type selection, const char *text);
void etk_selection_text_request(Etk_Selection_Type selection, Etk_Widget *target);
void etk_selection_clear(Etk_Selection_Type selection);

/** @} */

#endif
