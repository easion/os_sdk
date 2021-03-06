/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * GtkAccelLabel: GtkLabel with accelerator monitoring facilities.
 * Copyright (C) 1998 Tim Janik
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-1999.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GTK_ACCEL_LABEL_H__
#define __GTK_ACCEL_LABEL_H__


#include <gtk/gtklabel.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_ACCEL_LABEL		(gtk_accel_label_get_type ())
#define GTK_ACCEL_LABEL(obj)		(GTK_CHECK_CAST ((obj), GTK_TYPE_ACCEL_LABEL, GtkAccelLabel))
#define GTK_ACCEL_LABEL_CLASS(klass)	(GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_ACCEL_LABEL, GtkAccelLabelClass))
#define GTK_IS_ACCEL_LABEL(obj)		(GTK_CHECK_TYPE ((obj), GTK_TYPE_ACCEL_LABEL))
#define GTK_IS_ACCEL_LABEL_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ACCEL_LABEL))


typedef struct _GtkAccelLabel	    GtkAccelLabel;
typedef struct _GtkAccelLabelClass  GtkAccelLabelClass;

struct _GtkAccelLabel
{
  GtkLabel label;

  guint	     queue_id;
  guint	     accel_padding;
  GtkWidget *accel_widget;
  gchar     *accel_string;
  guint16     accel_string_width;
};

struct _GtkAccelLabelClass
{
  GtkLabelClass	 parent_class;

  gchar		*signal_quote1;
  gchar		*signal_quote2;
  gchar		*mod_name_shift;
  gchar		*mod_name_control;
  gchar		*mod_name_alt;
  gchar		*mod_separator;
  gchar		*accel_seperator;
  guint		 latin1_to_char : 1;
};


GtkType	   gtk_accel_label_get_type	     (void);
GtkWidget* gtk_accel_label_new		     (const gchar   *string);
guint	   gtk_accel_label_get_accel_width   (GtkAccelLabel *accel_label);
void	   gtk_accel_label_set_accel_widget  (GtkAccelLabel *accel_label,
					      GtkWidget	    *accel_widget);
gboolean   gtk_accel_label_refetch           (GtkAccelLabel *accel_label);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_ACCEL_LABEL_H__ */
