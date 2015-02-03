/** @file etk_box.h */
#ifndef _ETK_BOX_H_
#define _ETK_BOX_H_

#include "etk_container.h"
#include <Evas.h>
#include "etk_types.h"

/**
 * @defgroup Etk_Box Etk_Box
 * @brief The Etk_Box widget is a container that can contain several children
 * packed in one direction (horizontal or vertical)
 * @{
 */

/** Gets the type of a box */
#define ETK_BOX_TYPE       (etk_box_type_get())
/** Casts the object to an Etk_Box */
#define ETK_BOX(obj)       (ETK_OBJECT_CAST((obj), ETK_BOX_TYPE, Etk_Box))
/** Checks if the object is an Etk_Box */
#define ETK_IS_BOX(obj)    (ETK_OBJECT_CHECK_TYPE((obj), ETK_BOX_TYPE))

/** Gets the type of a hbox */
#define ETK_HBOX_TYPE       (etk_hbox_type_get())
/** Casts the object to an Etk_HBox */
#define ETK_HBOX(obj)       (ETK_OBJECT_CAST((obj), ETK_HBOX_TYPE, Etk_HBox))
/** Checks if the object is an Etk_HBox */
#define ETK_IS_HBOX(obj)    (ETK_OBJECT_CHECK_TYPE((obj), ETK_HBOX_TYPE))

/** Gets the type of a vbox */
#define ETK_VBOX_TYPE       (etk_vbox_type_get())
/** Casts the object to an Etk_VBox */
#define ETK_VBOX(obj)       (ETK_OBJECT_CAST((obj), ETK_VBOX_TYPE, Etk_VBox))
/** Checks if the object is an Etk_VBox */
#define ETK_IS_VBOX(obj)    (ETK_OBJECT_CHECK_TYPE((obj), ETK_VBOX_TYPE))


/** @brief The two groups where the children can be packed: the start-group and the end-group */
typedef enum
{
   ETK_BOX_START,    /**< The start-group of children: the children in this group are displayed
                      * at the start (left or top) of the box */
   ETK_BOX_END       /**< The end-group of children: the children in this group are displayed
                      * at the end (right or bottom) of the box */
} Etk_Box_Group;

/** @brief Describes how a child of the box expands and fills the space */
typedef enum
{
   ETK_BOX_NONE = 0,                  /**< The child does not fill or expand */
   ETK_BOX_EXPAND = 1 << 0,           /**< The cell containing the child will expand to take all the available space */
   ETK_BOX_FILL = 1 << 1,             /**< The child will fill all the available space in its cell */
   ETK_BOX_EXPAND_FILL = ETK_BOX_EXPAND | ETK_BOX_FILL,   /**< Equivalent to ETK_BOX_EXPAND | ETK_BOX_FILL */
   ETK_BOX_SHRINK_OPPOSITE = 1 << 2   /**< The child will shrink in the opposite direction of the box
                                       * (i.e the child will shrink vertically for an Etk_HBox, and
                                       * horizontally for an Etk_VBox) */
} Etk_Box_Fill_Policy;


/**
 * @internal
 * @brief A column of a combobox: a combobox should have at least a column,
 * and each column contains a specific type of widget (see Etk_Combobox_Column_Type)
 */
struct Etk_Box_Cell
{
   /* private: */
   Etk_Box_Cell *prev;
   Etk_Box_Cell *next;

   Etk_Widget *child;
   Evas_List *focus_node;
   Etk_Box_Group group;
   Etk_Box_Fill_Policy fill_policy;
   int padding;
};

/**
 * @brief @widget An abstract class for a box
 * @structinfo
 */
struct Etk_Box
{
   /* private: */
   /* Inherit from Etk_Container */
   Etk_Container container;

   int spacing;
   Etk_Bool homogeneous;
   Etk_Box_Cell *first_cell[2];
   Etk_Box_Cell *last_cell[2];
   int cells_count[2];
   int *request_sizes[2];
};

/**
 * @brief @widget A box in which the children are packed horizontally
 * @structinfo
 */
struct Etk_HBox
{
   /* private: */
   /* Inherit from Etk_Box */
   Etk_Box box;
};

/**
 * @brief @widget A box in which the children are packed vertically
 * @structinfo
 */
struct Etk_VBox
{
   /* private: */
   /* Inherit from Etk_Box */
   Etk_Box box;
};


Etk_Type   *etk_box_type_get(void);
Etk_Type   *etk_hbox_type_get(void);
Etk_Type   *etk_vbox_type_get(void);

Etk_Widget *etk_hbox_new(Etk_Bool homogeneous, int spacing);
Etk_Widget *etk_vbox_new(Etk_Bool homogeneous, int spacing);

void        etk_box_prepend(Etk_Box *box, Etk_Widget *child, Etk_Box_Group group, Etk_Box_Fill_Policy fill_policy, int padding);
void        etk_box_append(Etk_Box *box, Etk_Widget *child, Etk_Box_Group group, Etk_Box_Fill_Policy fill_policy, int padding);
void        etk_box_insert(Etk_Box *box, Etk_Widget *child, Etk_Box_Group group, Etk_Widget *after, Etk_Box_Fill_Policy fill_policy, int padding);
void        etk_box_insert_at(Etk_Box *box, Etk_Widget *child, Etk_Box_Group group, int pos, Etk_Box_Fill_Policy fill_policy, int padding);

Etk_Widget *etk_box_child_get_at(Etk_Box *box, Etk_Box_Group group, int pos);
void        etk_box_child_position_set(Etk_Box *box, Etk_Widget *child, Etk_Box_Group group, int pos);
Etk_Bool    etk_box_child_position_get(Etk_Box *box, Etk_Widget *child, Etk_Box_Group *group, int *pos);
void        etk_box_child_packing_set(Etk_Box *box, Etk_Widget *child, Etk_Box_Fill_Policy fill_policy, int padding);
Etk_Bool    etk_box_child_packing_get(Etk_Box *box, Etk_Widget *child, Etk_Box_Fill_Policy *fill_policy, int *padding);

void        etk_box_spacing_set(Etk_Box *box, int spacing);
int         etk_box_spacing_get(Etk_Box *box);
void        etk_box_homogeneous_set(Etk_Box *box, Etk_Bool homogeneous);
Etk_Bool    etk_box_homogeneous_get(Etk_Box *box);

/** @} */

#endif
