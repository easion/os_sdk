/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef EWL_RADIOBUTTON_H
#define EWL_RADIOBUTTON_H

#include "ewl_checkbutton.h"

/**
 * @addtogroup Ewl_Radiobutton Ewl_Radiobutton: A Radio Button Widget and Grouping System
 * Provides for a simple radiobutton with label, and to group radio buttons
 * for selecting a single option.
 *
 * @remarks Inherits from Ewl_Checkbutton.
 * @image html Ewl_Radiobutton_inheritance.png
 *
 * @{
 */

/**
 * @themekey /radiobutton/file
 * @themekey /radiobutton/group
 */

/**
 * @def EWL_RADIOBUTTON_TYPE
 * The type name for the Ewl_Radiobutton widget
 */
#define EWL_RADIOBUTTON_TYPE "radiobutton"

/**
 * @def EWL_RADIOBUTTON_IS(w)
 * Returns TRUE if the widget is an Ewl_Radiobutton, FALSE otherwise
 */
#define EWL_RADIOBUTTON_IS(w) (ewl_widget_type_is(EWL_WIDGET(w), EWL_RADIOBUTTON_TYPE))

/**
 * The radio button provides a means for selecting a single item from a group
 * of options.
 */
typedef struct Ewl_Radiobutton Ewl_Radiobutton;

/**
 * @def EWL_RADIOBUTTON(button)
 * Typecasts a pointer to an Ewl_Radiobutton pointer.
 */
#define EWL_RADIOBUTTON(button) ((Ewl_Radiobutton *) button)

/**
 * @brief Inherits from Ewl_Checkbutton and extends it to provide grouping buttons
 * to limit to a single selection in a group at a given time.
 */
struct Ewl_Radiobutton
{
	Ewl_Checkbutton button; /**< Inherit from Ewl_Checkbutton */
	Ecore_List *chain; /**< List of members of the group */
};

Ewl_Widget 	*ewl_radiobutton_new(void);
int 		 ewl_radiobutton_init(Ewl_Radiobutton *cb);

void 		 ewl_radiobutton_chain_set(Ewl_Radiobutton *w, Ewl_Radiobutton *c);

/**
 * @def ewl_radiobutton_checked_set(r, c)
 * Shortcut for setting the checked status on the inherited Ewl_Checkbutton
 * fields.
 */
#define ewl_radiobutton_checked_set(r, c) \
	ewl_checkbutton_checked_set(EWL_CHECKBUTTON(r), c)

/**
 * @def ewl_radiobutton_is_checked(r)
 * Shortcut for checking the checked status on the inherited Ewl_Checkbutton
 * fields.
 */
#define ewl_radiobutton_is_checked(r) \
	ewl_checkbutton_is_checked(EWL_CHECKBUTTON(r))

/*
 * Internally used callbacks, override at your own risk.
 */
void ewl_radiobutton_cb_clicked(Ewl_Widget *w, void *ev_data, void *user_data);
void ewl_radiobutton_cb_destroy(Ewl_Widget *w, void *ev_data, void *user_data);

/**
 * @}
 */

#endif
