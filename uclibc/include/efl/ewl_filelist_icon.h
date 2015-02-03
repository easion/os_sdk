/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef EWL_FILELIST_ICON_H
#define EWL_FILELIST_ICON_H

#include "ewl_filelist.h"
#include "ewl_view.h"

/**
 * @addtogroup Ewl_Filelist_Icon Ewl_Filelist_Icon: A icon file view
 * A view of the files using simple name/icon graphics
 *
 * @remarks Inherits from Ewl_Filelist.
 * @image html Ewl_Filelist_Icon_inheritance.png
 *
 * @{
 */

/**
 * @def EWL_FILELIST_ICON_TYPE
 * The type name for the Ewl_Filelist_Icon widget
 */
#define EWL_FILELIST_ICON_TYPE "filelist_icon"

/**
 * @def EWL_FILELIST_ICON_IS(w)
 * Returns TRUE if the widget is an Ewl_Filelist_Icon, FALSE otherwise
 */
#define EWL_FILELIST_ICON_IS(w) (ewl_widget_type_is(EWL_WIDGET(w), EWL_FILELIST_ICON_TYPE))

/**
 * The Ewl_Filelist_Icon provides an icon view of the files
 */
typedef struct Ewl_Filelist_Icon Ewl_Filelist_Icon;

/**
 * @def EWL_FILELIST_ICON(fl)
 * Typecasts a pointer to an Ewl_Filelist_Icon pointer
 */
#define EWL_FILELIST_ICON(fl) ((Ewl_Filelist_Icon *)fl)

/**
 * @brief Inherits from Ewl_Filelist and extends for an icon view
 */
struct Ewl_Filelist_Icon
{
	Ewl_Filelist list;	/**< Inherit from filelist */
	Ewl_Widget *freebox; 	/**< Freebox to hold icons */
};

Ewl_View	*ewl_filelist_icon_view_get(void);

Ewl_Widget	*ewl_filelist_icon_new(void);
int		 ewl_filelist_icon_init(Ewl_Filelist_Icon *fl);

void		 ewl_filelist_icon_dir_change(Ewl_Filelist *fl);
void 		 ewl_filelist_icon_selected_file_add(Ewl_Filelist *fl,
							const char *file);
const char 	*ewl_filelist_icon_filename_get(Ewl_Filelist *fl,
							void *item);
void		 ewl_filelist_icon_selected_unselect(Ewl_Filelist *fl);
void		 ewl_filelist_icon_shift_handle(Ewl_Filelist *fl,
						Ewl_Widget *clicked);

/**
 * @}
 */

#endif

