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
 * Une zone de dessin qui herite de DrawingArea.
 * 
 * Inspire des exemples suivants :
 *    http://www-lil.univ-littoral.fr/~quesnel/cplusplus/gtkmm/gtkmmse7.html
 *    http://www.sm.u-bordeaux2.fr/%7Eparisy/C++/gtkmm-exemples/exemples-gtkmm.tgz (lunarPhases)
 *
 * Guillaume Riviere 21-06-2006
 */

#include <iostream>

#include <gtkmm/drawingarea.h>

#include "Draw.hh" 

using namespace std ;

/////////////////////////////////////////
//-- Constructeurs / Destructeur PUBLIC
/////////////////////////////////////////

Draw::Draw(int w, int h)
  : Gtk::DrawingArea ()
{  
  /* Set the minimum size of the widget */
  set_size_request(w, h);  
}

//////////////////////
//-- Methodes PUBLIC
//////////////////////

void Draw::set_image_from_file (const char* filename)
{
  m_pixbuf = Gdk::Pixbuf::create_from_file(filename) ;
}

/////////////////////////
//-- Methodes PROTECTED
/////////////////////////

/**
 * Dessine une image dans la zone de dessin a partir d'un fichier.
 */
void Draw::draw_image ()
{
  int x = 0 ;
  int y = 0 ;
  int width = m_pixbuf->get_width () ;
  int height = m_pixbuf->get_height () ;

  //cout << "pixbuf size = " << width << " x " << height << endl ;

  this->set_size_request (width, height) ;

  const int rowstride = m_pixbuf->get_rowstride();
  const size_t offset = rowstride * y + 3 * x;

  this->get_window()->draw_rgb_image_dithalign(this->get_style()->get_black_gc(),
					       x, y, width, height,
					       Gdk::RGB_DITHER_NORMAL,
					       &m_pixbuf->get_pixels()[offset], rowstride,
					       x, y);

}

/**
 * Redessine la zone lors de l'appel d'évènement expose_event.
 */
bool Draw::on_expose_event(GdkEventExpose* event)  
{  
  /* Draw image */
  this->draw_image () ;

  return true;  
}  
