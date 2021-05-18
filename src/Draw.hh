/**   -=- Rectify-Coords "Rectify Points Coordinates" -=-
 *    
 *    Let P be a 2D point expressed in a plane area defined by
 *    four 2D points A,B,C,D. The aim of the class called
 *    "Cadre(.hh|.cc)" is to express the coordinates of P in
 *    order to match when A,B,C,D is rectified as a rectangle.
 *    
 *    This program is a demo application which shows the use
 *    of the "Cadre" C++ class. The window is divided in two
 *    parts. On the left, a drawing area shows the source
 *    quadrilateral, which can be modified using four handles.
 *    On the right, a drawing area shows the destination
 *    rectangle. The position of the mouse cursor on the left
 *    area is mapped on the right view after rectification to
 *    match with the rectangle.
 *
 *
 *    Copyright (C) 2007 Guillaume RIVIERE
 *
 *
 *    This file is part of Rectify-Coords "Rectify Points Coordinates"
 *
 *    Rectify-Coords is free software: you can redistribute it
 *    and/or modify it under the terms of the GNU Lesser General
 *    Public License as published by the Free Software Foundation,
 *    either version 3 of the License, or (at your option) any
 *    later version.
 *
 *    Rectify-Coords is distributed in the hope that it will be
 *    useful, but WITHOUT ANY WARRANTY; without even the implied
 *    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *    PURPOSE.  See the GNU Lesser General Public License for
 *    more details.
 *
 *    You should have received a copy of the GNU Lesser General
 *    Public License along with Rectify-Coords.  If not, see 
 *    <http://www.gnu.org/licenses/>
 **/

/**
 * Class Draw
 * - - - - - -
 * Une zone de dessin qui herite de DrawingArea en GTKmm.
 * 
 * Inspire des exemples suivants :
 *    http://www-lil.univ-littoral.fr/~quesnel/cplusplus/gtkmm/gtkmmse7.html
 *    http://www.sm.u-bordeaux2.fr/%7Eparisy/C++/gtkmm-exemples/exemples-gtkmm.tgz (lunarPhases)
 *
 * Guillaume Riviere 21-06-2006
 */

#ifndef DRAW_H
#define DRAW_H

#include <vector>

#include <gtkmm/drawingarea.h>

class Draw : public Gtk::DrawingArea  
{  
public:  

  //-- Constructeurs / Destructeur PUBLIC

  Draw (int w, int h);

  //-- Methodes PUBLIC

  void set_image_from_file (const char* filename) ;

protected:

  //-- Methodes PROTECTED

  void draw_image () ;

 /**
   * Methode heritee de Gtk::Widget
   */
  bool on_expose_event(GdkEventExpose* event);

  //-- Attributs PROTECTED

  Glib::RefPtr<Gdk::Pixbuf> m_pixbuf ;

private:

  //-- Attributs PRIVATE

};  

#endif /* DRAW_H */
