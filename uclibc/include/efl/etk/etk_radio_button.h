/** @file etk_radio_button.h */
#ifndef _ETK_RADIO_BUTTON_H_
#define _ETK_RADIO_BUTTON_H_

#include <Evas.h>
#include "etk_toggle_button.h"
#include "etk_types.h"

/**
 * @defgroup Etk_Radio_Button Etk_Radio_Button
 * @brief The Etk_Radio_Button widget is a toggle-button that belongs to a group in which only one button can be active
 * @{
 */

/** Gets the type of a radio button */
#define ETK_RADIO_BUTTON_TYPE       (etk_radio_button_type_get())
/** Casts the object to an Etk_Radio_Button */
#define ETK_RADIO_BUTTON(obj)       (ETK_OBJECT_CAST((obj), ETK_RADIO_BUTTON_TYPE, Etk_Radio_Button))
/** Checks if the object is an Etk_Radio_Button */
#define ETK_IS_RADIO_BUTTON(obj)    (ETK_OBJECT_RADIO_TYPE((obj), ETK_RADIO_BUTTON_TYPE))


/**
 * @brief @widget A toggle-button that belongs to a group in which only one button can be active
 * @structinfo
 */
struct Etk_Radio_Button
{
   /* private: */
   /* Inherit from Etk_Toggle_Button */
   Etk_Toggle_Button toggle_button;

   Evas_List **group;
   Etk_Bool can_uncheck;
};


Etk_Type    *etk_radio_button_type_get(void);
Etk_Widget  *etk_radio_button_new(Evas_List **group);
Etk_Widget  *etk_radio_button_new_from_widget(Etk_Radio_Button *radio_button);
Etk_Widget  *etk_radio_button_new_with_label(const char *label, Evas_List **group);
Etk_Widget  *etk_radio_button_new_with_label_from_widget(const char *label, Etk_Radio_Button *radio_button);

void        etk_radio_button_group_set(Etk_Radio_Button *radio_button, Evas_List **group);
Evas_List **etk_radio_button_group_get(Etk_Radio_Button *radio_button);

/** @} */

#endif
