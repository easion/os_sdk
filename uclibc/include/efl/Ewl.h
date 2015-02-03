/* vim: set sw=8 ts=8 sts=8 noexpandtab: */
#ifndef EWL_H
#define EWL_H

/**
 * @file Ewl.h
 * @brief The file that should be included by any project using EWL.
 * Provides all the necessary headers and includes to work with EWL.
 * It is discouraged to include each header file individually.
 */

/**
 * @mainpage The Enlightened Widget Library
 *
 * @section intro Introduction
 *
 * The Enlightened Widget Library (EWL) is a widget toolkit based on the
 * libraries developed for Enlightenment 17. Rendering is performed
 * using Evas, a fast abstracted canvas library that supports multiple
 * backends. The appearance of the widgets are described by Edje files,
 * which are essentially files containing a collection of images and
 * descriptions for laying out those images. The goal of EWL is to abstract
 * the use of these backends and to present an easy to use object model to the
 * end programmer.
 *
 * Overall, EWL is similar in design and functionality to other common
 * toolkits such as GTK+ and QT. The API's differ, but the overall concepts
 * and ideas are similar. If you are familiar with these other toolkits
 * getting into EWL should be relatively simple.
 *
 * EWL uses the concept of inheritance for describing its widgets. When a
 * class inherits from another class, the functions that operated on the base
 * class can also operate on the inheriting class. For example, in EWL the
 * class Ewl_Button inherits from Ewl_Box, which inherits from Ewl_Container.
 * This means you can add widgets to the button, just like you could to the
 * box or any other container by using ewl_container functions. Since EWL is
 * written in C, it uses a very simple single inheritance system. The first
 * field of the inheriting struct must be the inherited struct, and note, it's
 * not a pointer to the inherited struct. For example:
 *
 * @code
 * struct Ewl_Foo
 * {
 * 	Ewl_Bar bar;
 * 	int baz;
 * };
 * @endcode
 *
 * Creates a new class of object, Foo, which inherits from the Bar class and
 * extends it by adding an integer baz. If the first line of the struct had
 * been Ewl_Bar *bar; it would most likely result in some buffer overflows
 * when initializing the widget.
 *
 * @section model The Object Model
 *
 * The basis for all widgets in EWL is Ewl_Object. Ewl_Objects are never
 * allocated outside of another widget, it provides size and position
 * information for the widget as well as info about the widgets padding and
 * insets. There are also fields for indicating object alignment and fill
 * policies.
 *
 * The next step above Ewl_Object is Ewl_Widget. Again, Ewl_Widgets are
 * usually not allocated by themselves, but are part of all the other widgets
 * available in EWL. The Ewl_Widget class provides the necessary information about
 * a widget that relates to its appearance, its parent container, event
 * handling, as well as a few miscellaneous tasks common to all widgets. The
 * Ewl_Widget structure also contains information on the inheritance of any
 * given widget. This is useful if you need to check the type of a widget in
 * your code.
 *
 * A necessary class that some widgets inherit from is Ewl_Container. This is
 * used for holding collections of widgets and specifiying their layout. Containers
 * are the building blocks of the widget set. They allow for creating heirarchies
 * of widgets that are bounded within their parent containers. Ewl_Container
 * inherits from Ewl_Widget, so any container can also be treated as a
 * widget, and thus you can put containers within other containers. Examples
 * of inheriting classes are Ewl_Window and Ewl_Box. In the case of
 * Ewl_Window, widgets inside the window are given any position they request
 * within the insets of the window. For Ewl_Box, contained widgets are
 * layed out either from top to bottom, or from left to right, depending on
 * the box orientation.
 *
 * @section callbacks Callbacks
 *
 * To do work in a GUI, it is necessary to know when certain actions occur.
 * EWL handles notification of actions using a common technique called
 * callbacks. When the end programmer wants to know when a specific event
 * occurs to a widget, they can add a callback to it using ewl_callback_append()
 * or one of the similar functions. One of the arguments to these functions is
 * a pointer to a function. This function will get called when EWL receives
 * the specified event on that widget. You can attach callbacks to any widget,
 * and with containers you can even mark them to intercept events to their
 * child widgets.
 *
 * One feature of EWL that is different from other toolkits is that it makes
 * extensive use of internal callbacks. In fact, almost all appearance changes
 * for widgets are actually callbacks, and most of the ewl_widget calls
 * actually do very little work, but trigger specific callbacks. This feature
 * allows for overriding specific actions on a widget, or for ordering user
 * specified callbacks relative to internal ones.
 *
 * @section example Example Application Walk-through
 *
 * One of the easiest applications to build for EWL is a simple image viewer.
 * The basic image viewer needs a window and an image widget. The following
 * app is a fully functional simple image viewer based on code written by Ben
 * Rockwood of Cuddletech. The first part necessary for creating an EWL
 * application is to include the necessary header Ewl.h. Following the include
 * statements are global variable declarations.
 *
 * @code
 * #include <Ewl.h>
 *
 * Ewl_Widget *main_win;
 * Ewl_Widget *main_box;
 * Ewl_Widget *image;
 * @endcode
 *
 * Now declarations of function callbacks are
 * made, normally when writing an application
 * these are added after the GUI code is written.
 * The next piece of code is common to most apps,
 * the windows in EWL are not closed unless they
 * are destroyed, so a callback must be attached
 * for the windows delete callback.
 *
 * @code
 * void
 * __destroy_main_window(Ewl_Widget *main_win, void *ev_data, void *user_data)
 * {
 * 	ewl_widget_destroy(main_win);
 * 	ewl_main_quit();
 *
 * 	return;
 * }
 * @endcode
 *
 * For this application that is the only callback, now we
 * have the main function.  This is where EWL is initialized,
 * widgets are created, and the main EWL loop is started.  First,
 * declare the main function and check to be sure that an image
 * file was specified. Then, initialize EWL.
 *
 * @code
 * int main (int argc, char **argv)
 * {
 * 	if (argc < 2) {
 *		fprintf(stderr, "Usage: %s <image>\n", argv[0]);
 *		return 1;
 * 	}
 *	if (!ewl_init(&argc, argv)) {
 * 		fprintf(stderr, "Unable to initialize EWL.\n");
 * 		return 1;
 *	}
 * @endcode
 *
 * Next allocate the window, set its title and attach a callback to catch its
 * delete event.  Also, set a minimum size on the window, mark it to be
 * auto-sized, and set visible.  Marking it auto-sized will cause the widget to
 * resize to fit the contents.
 *
 * @code
 * 	main_win = ewl_window_new();
 * 	ewl_window_title_set(EWL_WINDOW(main_win), "EWL Simple Image Viewer");
 * 	ewl_callback_append(main_win, EWL_CALLBACK_DELETE_WINDOW,
 *			    __destroy_main_window, NULL);
 * 	ewl_object_minimum_size_set(EWL_OBJECT(main_win), 100, 100);
 * 	ewl_widget_show(main_win);
 * @endcode
 *
 * Next we create a box to hold the image. This isn't really necessary for
 * this app but demonstrates further how to use containers and makes it
 * easier to add more widgets later.
 *
 * @code
 * 	main_box = ewl_vbox_new();
 * 	ewl_container_child_append(EWL_CONTAINER(main_win), main_box);
 * 	ewl_widget_show(main_box);
 * @endcode
 *
 * Next, create the image widget. We just attempt to load the image
 * file that was specified on the command line and add it to the
 * box in the window. The second argument is NULL for normal images but can
 * be set to the name of the group to load for an Edje file.
 *
 * @code
 * 	image = ewl_image_new();
 *	ewl_image_file_set(EWL_IMAGE(image), argv[1], NULL);
 * 	ewl_container_child_append(EWL_CONTAINER(main_box), image);
 * 	ewl_widget_show(image);
 * @endcode
 *
 * Finally, we call the main function that starts the EWL event
 * processing loop. With that, our app is complete.
 *
 * @code
 * 	ewl_main();
 *
 * 	return 0;
 * }
 * @endcode
 *
 * Now that the application source has been written, it must be
 * compiled. This is fairly simple with EWL, if you name the app
 * simple_viewer.c just use the command:
 *
 * @code
 * gcc -o simple_viewer `pkg-config --cflags --libs ewl` simple_viewer.c
 * @endcode
 *
 * @section conclusion Conclusion
 *
 * Obviously, creating a simple image viewer doesn't take much
 * effort but it's a good basis for understanding the
 * basics of EWL.  Hopefully, readers will extend this app, and
 * possibly create more robust image viewers, and with any luck,
 * other applications to demonstrate EWLs capabilities.
 *
 * If you have questions, corrections, or improvements, please send
 * them to <a href="mailto: enlightenment-devel@lists.sourceforge.net">enlightenment-devel at lists dot sourceforge dot net</a>.
 */

/**
 * @page layering Layering Scheme
 *
 * As widgets are placed inside containers, there becomes the issue of
 * specifying which widget gets drawn on top. It's important that the widgets placed
 * inside of a container are above the containers background, or the user
 * would be unable to view the placed widgets.
 *
 * EWL handles the layering so the programmer dosen't need to worry about
 * it. In some cases it is necessary for a widget to overlap another widget
 * with the same parent. In this case you set the layer priority of the
 * widget to a higher value (negitive values are possible).
 *
 * If you want a widget to be placed over top of all other widgets, like
 * floater for example, you can set the widget to be 'top layered'. This
 * setting will also effect the children of that widget.
 */

/**
 * @page images Documentation Images
 *
 * Diagram describing Ewl_Object fields
 *
 * @image html object_fields.png
 *
 * Diagram describing how Ewl_Object fields affect sizing.
 *
 * @image html object_sizing.png
 */

#ifdef __cplusplus
extern"C" {
#endif

/* Include the core functionality wrapped in the proper order */
#include <ewl_base.h>

/* IO and MVC helper functionality, MVC must be here for widgets to provide
 * default views */
#include <ewl_io_manager.h>

#include <ewl_model.h>
#include <ewl_view.h>

/* Base widgets and containers */
#include <ewl_box.h>
#include <ewl_border.h>

#include <ewl_cell.h>
#include <ewl_row.h>

#include <ewl_grid.h>
#include <ewl_table.h>

#include <ewl_label.h>
#include <ewl_stock.h>
#include <ewl_button.h>
#include <ewl_floater.h>
#include <ewl_dialog.h>
#include <ewl_popup.h>

#include <ewl_text.h>
#include <ewl_text_trigger.h>
#include <ewl_entry.h>

#include <ewl_colorpicker.h>
#include <ewl_colordialog.h>
#include <ewl_password.h>
#include <ewl_range.h>
#include <ewl_seeker.h>
#include <ewl_scrollbar.h>
#include <ewl_spacer.h>
#include <ewl_spinner.h>
#include <ewl_image.h>
#include <ewl_highlight.h>
#include <ewl_histogram.h>
#include <ewl_spectrum.h>
#include <ewl_menu_item.h>
#include <ewl_menu.h>
#include <ewl_menubar.h>
#include <ewl_context_menu.h>
#include <ewl_toolbar.h>
#include <ewl_check.h>
#include <ewl_checkbutton.h>
#include <ewl_radiobutton.h>
#include <ewl_separator.h>
#include <ewl_calendar.h>
#include <ewl_datepicker.h>
#include <ewl_icon.h>
#include <ewl_icon_theme.h>
#include <ewl_notebook.h>
#include <ewl_progressbar.h>
#include <ewl_paned.h>
#include <ewl_scrollpane.h>
#include <ewl_statusbar.h>
#include <ewl_shadow.h>

/* MVC definitions and containers */
#include <ewl_mvc.h>

#include <ewl_combo.h>

#include <ewl_tree.h>
#include <ewl_tree2.h>
#include <ewl_tree2_view.h>
#include <ewl_tree2_view_plain.h>
#include <ewl_tree2_view_scrolled.h>
#include <ewl_list.h>

#include <ewl_freebox.h>

#include <ewl_filelist.h>
#include <ewl_filelist_list.h>
#include <ewl_filelist_icon.h>
#include <ewl_filelist_column.h>
#include <ewl_filelist_tree.h>
#include <ewl_filepicker.h>
#include <ewl_filedialog.h>

#include <ewl_media.h>

#ifdef __cplusplus
}
#endif
#endif
