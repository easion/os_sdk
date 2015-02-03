// Standard dialog header file for the UTF-8 Fast Light Tool Kit (FLTK-UTF8).
//
// Copyright 2003-2005 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version
// with exceptions that allow sub-classing and static linking in
// non-LGPL compliant software. These exceptions are subject to
// conditions, see the FLTK License for more details.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the FLTK
// License for more details.
//
// You should have received a copy of the FLTK License along with
// this library; if not, write to  OksiD Software, Jean-Marc Lienher,
// Rue de la Cheminee 1, CH-2065 Savagnier, Switzerland.
//
// Please report all bugs and problems to "oksid@bluewin.ch".
//

#ifndef FL_TREE_H
#define FL_TREE_H
#include <FL/Fl.H>

#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

class  Fl_Tree : public Fl_Group {

  int pos;
  int hpos;
  int opos;
  int ohpos;
  int nb_alloc_lines;
  int top_line;
  int top_liney;
  int otop_y;

protected:
  char was_key;
  int height;
  int width;
  int level;
  int nb_lines;
  int *widths;
  int *heights; 
  int *flags;
  int *levels;
  void **datas;
  int sel;
  Fl_Scrollbar *scrollbar;	
  Fl_Scrollbar *hscrollbar;	
  Fl_Box *scrollbox;
  
  void draw_scroll();
  void draw_clip(int,int,int,int);
  static void draw_clipped(void*,const fltk::Rectangle& myr);
  void set_scroll();
  void draw_lines(int = 0);
  int find_below();
  void grow_lines(int l = 1);
  void dot_rect(int,int,int,int);

public:
  enum {
    FLAG_OPEN	= 0x0001,
    FLAG_FOLDER = 0x0002,
    FLAG_REDRAW = 0x0004,
    FLAG_SELECTED = 0x0008,
  };

  Fl_Tree(int, int, int, int, const char* = 0);
  ~Fl_Tree();

  int handle(int);
  void resize(int,int,int,int);
  void draw();
  void position(int);
  void hposition(int);
  int position() {return pos;}
  int hposition(){return hpos;}
  void *item_data(int);
  int get_selection(void) {return sel;}
  int item_max() {return nb_lines;}
  void *get_item(int n) {return datas[n];}
  int item_flags(int n) {return flags[n];}
  void item_set_flags(int n, int f) {flags[n] |= f;}
  void item_clear_flags(int n, int f) {flags[n] &= ~f;}
  void item_set(int n, void *d) {datas[n] = d; flags[n] = FLAG_REDRAW;}
  void item_size(int n, int w, int h) {widths[n] = w; heights[n] = h;}
  int item_width(int n) {return widths[n];} 
  int item_height(int n) {return heights[n];}

  // these functions _must_ be implemented in sub-classes :
  virtual void item_draw(int,int,int, int,int,int,int);
  virtual void item_measure(int);
  virtual int item_nb_children(int);
  virtual int item_has_children(int);
  virtual void *item_get_child(int, int);
  virtual void item_free(int);

  // optional 
  virtual int item_handle(int, int);
  virtual void item_open(int);
  virtual void item_close(int);
  virtual void item_select(int,int=1);
  virtual int item_selected(int);
  virtual void item_damage(int);
  virtual void root(void *);
  virtual void *root(void); 
  virtual void draw_begin(int);
  virtual void draw_end(void);
};

#endif

//
// End of "$Id: $".
//
