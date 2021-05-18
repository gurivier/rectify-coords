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

#include "DrawView.hh" 

/////////////////////////////////////////
//-- Constructeurs / Destructeur PUBLIC
/////////////////////////////////////////

DrawView::DrawView (int w, int h)
  : Draw (w, h),
    m_lines_color ("black"),
    m_points_size (2)
{
  /* Initialisation du cadre */

  m_origin.x = w / 4 ;
  m_origin.y = h / 4 ;

  m_width = w / 2 ;
  m_height = h / 2 ;

  m_point.x = 0 ;
  m_point.y = 0 ;
}


/////////////////////////
//-- Methodes PROTECTED
/////////////////////////

/**
 * Methode heritee de la classe Draw
 */
bool DrawView::on_expose_event(GdkEventExpose* event)
{
  Draw::on_expose_event(event) ;

  Glib::RefPtr<Gdk::Window> win = get_window () ;
  Glib::RefPtr<Gdk::GC> gc = get_style()->get_black_gc();

  /* Dessiner le cadre */
  gc->set_rgb_fg_color (m_lines_color) ;
  win->draw_line(gc,
		 m_origin.x, m_origin.y,
		 m_origin.x+m_width, m_origin.y) ;
  win->draw_line(gc,
		 m_origin.x+m_width, m_origin.y,
		 m_origin.x+m_width, m_origin.y+m_height) ;
  win->draw_line(gc,
		 m_origin.x+m_width, m_origin.y+m_height,
		 m_origin.x, m_origin.y+m_height) ;
  win->draw_line(gc,
		 m_origin.x, m_origin.y+m_height,
		 m_origin.x, m_origin.y) ;

  /* Dessiner le point */
  //win->draw_point(gc, m_point.x, m_point.y) ;
  draw_point(win, gc, m_point.x, m_point.y) ;
}

void DrawView::draw_point (Glib::RefPtr<Gdk::Window> win,
			   Glib::RefPtr<Gdk::GC> gc,
			   const int x, const int y)
{
  win->draw_line(gc, x-m_points_size, y, x+m_points_size, y);
  win->draw_line(gc, x, y-m_points_size, x, y+m_points_size);
}
