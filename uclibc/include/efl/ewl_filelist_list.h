/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef EWL_FILELIST_LIST_H
#define EWL_FILELIST_LIST_H

#include "ewl_filelist.h"
#include "ewl_view.h"

/**
 * @addtogroup Ewl_Filelist_List Ewl_Filelist_List: A listview of the files
 * Provides a list view of the files giving name, size, etc information
 *
 * @remarks Inherits from Ewl_Filelist.
 * @image html Ewl_Filelist_List_inheritance.png
 *
 * @{
 */

/**
 * @def EWL_FILELIST_LIST_TYPE
 * The type name for the Ewl_Filelist_List widget
 */
#define EWL_FILELIST_LIST_TYPE "filelist_list"

/**
 * @def EWL_FILELIST_LIST_IS(w)
 * Returns TRUE if the widget is an Ewl_Filelist_List, FALSE otherwise
 */
#define EWL_FILELIST_LIST_IS(w) (ewl_widget_type_is(EWL_WIDGET(w), EWL_FILELIST_LIST_TYPE))

/**
 * The Ewl_Filelist_List widget provides a list view of the files
 */
typedef struct Ewl_Filelist_List Ewl_Filelist_List;

/**
 * @def EWL_FILELIST_LIST(fl)
 * Typecasts a pointer to an Ewl_Filelist_List pointer.
 */
#define EWL_FILELIST_LIST(fl) ((Ewl_Filelist_List *)fl)

/**
 * @brief Inherits from Ewl_Filelist and extends to create a list view.
 */
struct Ewl_Filelist_List
{
	Ewl_Filelist list;	/**< Inherit from filelist */
	Ewl_Widget *tree; 	/**< Tree to hold icons */
};

Ewl_View	*ewl_filelist_list_view_get(void);

Ewl_Widget	*ewl_filelist_list_new(void);
int		 ewl_filelist_list_init(Ewl_Filelist_List *fl);

void		 ewl_filelist_list_dir_change(Ewl_Filelist *fl);
void 		 ewl_filelist_list_selected_file_add(Ewl_Filelist *fl,
							const char *file);
const char 	*ewl_filelist_list_filename_get(Ewl_Filelist *fl,
							void *item);
void		 ewl_filelist_list_selected_unselect(Ewl_Filelist *fl);
void		 ewl_filelist_list_shift_handle(Ewl_Filelist *fl,
						Ewl_Widget *clicked);

/**
 * @}
 */

#endif

