//
// "$Id: MenuBar.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Menu bar, each submenu is a pull-down menu. Any items act like
// a button in the menu bar.
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#ifndef fltk_MenuBar_h
#define fltk_MenuBar_h

#include "Menu.h"

namespace fltk {

class FL_API MenuBar : public Menu {
public:
  MenuBar(int x,int y,int w,int h,const char *l=0);
  static NamedStyle* default_style;
  int handle(int);
protected:
  void draw();
private:
  int highlight_, last_;
  Widget *lastfocus_;
};

}
#endif

//
// End of "$Id: MenuBar.h 4886 2006-03-30 09:55:32Z fabien $".
//
