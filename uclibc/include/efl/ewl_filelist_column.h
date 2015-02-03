/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef EWL_FILELIST_COLUMN_H
#define EWL_FILELIST_COLUMN_H

#include "ewl_filelist.h"
#include "ewl_view.h"

/**
 * @addtogroup Ewl_Filelist_Column Ewl_Filelist_Column: An expanding column view
 * A view of the files using a new column for each directory.
 *
 * @remarks Inherits from Ewl_Filelist.
 * @image html Ewl_Filelist_Column_inheritance.png
 *
 * @{
 */

/**
 * @def EWL_FILELIST_COLUMN_TYPE
 * The type name for the Ewl_Filelist_Column widget
 */
#define EWL_FILELIST_COLUMN_TYPE "filelist_column"

/**
 * @def EWL_FILELIST_COLUMN_IS(w)
 * Returns TRUE if the widget is an Ewl_Filelist_Column, FALSE otherwise
 */
#define EWL_FILELIST_COLUMN_IS(w) (ewl_widget_type_is(EWL_WIDGET(w), EWL_FILELIST_COLUMN_TYPE))

/**
 * @def EWL_FILELIST_COLUMN(fl)
 * Typecasts a pointer to an Ewl_Filelist_Column pointer
 */
#define EWL_FILELIST_COLUMN(fl) ((Ewl_Filelist_Column *)fl)

/**
 * The Ewl_Filelist_Column provides a column view of the files
 */
typedef struct Ewl_Filelist_Column Ewl_Filelist_Column;

/**
 * @brief Inherits from Ewl_Filelist and extends to provide a column view
 */
struct Ewl_Filelist_Column
{
	Ewl_Filelist list; 	/**< Inherit from filelist */

	Ewl_Widget *hbox;	/**< Hbox to contain the file lists **/
	Ecore_List *dirs;	/**< List of directories shown */
	Ewl_Widget *preview;	/**< The preview */
};

Ewl_View	*ewl_filelist_column_view_get(void);

Ewl_Widget	*ewl_filelist_column_new(void);
int		 ewl_filelist_column_init(Ewl_Filelist_Column *fl);

void		 ewl_filelist_column_dir_change(Ewl_Filelist *fl);
void 		 ewl_filelist_column_selected_file_add(Ewl_Filelist *fl,
							const char *file);
const char 	*ewl_filelist_column_filename_get(Ewl_Filelist *fl,
							void *item);
void 		 ewl_filelist_column_selected_unselect(Ewl_Filelist *fl);
void 		 ewl_filelist_column_shift_handle(Ewl_Filelist *fl,
						Ewl_Widget *clicked);

/**
 * @}
 */

#endif

