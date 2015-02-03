/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef EWL_FILELIST_TREE_H
#define EWL_FILELIST_TREE_H

#include "ewl_filelist.h"
#include "ewl_view.h"

/**
 * @addtogroup Ewl_Filelist_Tree Ewl_Filelist_Tree: A treeview of the files
 * Provides a tree view of the files giving name, size, etc information
 *
 * @remarks Inherits from Ewl_Filelist.
 * @image html Ewl_Filelist_Tree_inheritance.png
 *
 * @{
 */

/**
 * @def EWL_FILELIST_TREE_TYPE
 * The type name for the Ewl_Filelist_Tree widget
 */
#define EWL_FILELIST_TREE_TYPE "filelist_tree"

/**
 * @def EWL_FILELIST_TREE_IS(w)
 * Returns TRUE if the widget is an Ewl_Filelist_Tree, FALSE otherwise
 */
#define EWL_FILELIST_TREE_IS(w) (ewl_widget_type_is(EWL_WIDGET(w), EWL_FILELIST_TREE_TYPE))

/**
 * The Ewl_Filelist_Tree widget provides a tree view of the files
 */
typedef struct Ewl_Filelist_Tree Ewl_Filelist_Tree;

/**
 * @def EWL_FILELIST_TREE(fl)
 * Typecasts a pointer to an Ewl_Filelist_Tree pointer.
 */
#define EWL_FILELIST_TREE(fl) ((Ewl_Filelist_Tree *)fl)

/**
 * @brief Inherits from Ewl_Filelist and extends to provide a tree view.
 */
struct Ewl_Filelist_Tree
{
	Ewl_Filelist list;	/**< Inherit from filelist */
	Ewl_Widget *tree; 	/**< Tree to hold icons */
};

Ewl_View	*ewl_filelist_tree_view_get(void);

Ewl_Widget	*ewl_filelist_tree_new(void);
int		 ewl_filelist_tree_init(Ewl_Filelist_Tree *fl);

void		 ewl_filelist_tree_dir_change(Ewl_Filelist *fl);
void 		 ewl_filelist_tree_selected_file_add(Ewl_Filelist *fl,
							const char *file);
const char 	*ewl_filelist_tree_filename_get(Ewl_Filelist *fl,
							void *item);
void		 ewl_filelist_tree_selected_unselect(Ewl_Filelist *fl);
void		 ewl_filelist_tree_shift_handle(Ewl_Filelist *fl,
						Ewl_Widget *clicked);

/**
 * @}
 */

#endif

