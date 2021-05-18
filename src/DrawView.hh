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

#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include "Draw.hh"
#include "point2D.hh"

class DrawView : public Draw
{
public:

  //-- Constructeurs / Destructeur PUBLIC

  DrawView (int w, int h);

  //-- Accesseurs / Modifieurs PUBLIC

  inline int getOriginX () const
  { return m_origin.x ; }

  inline int getOriginY () const
  { return m_origin.y ; }

  inline int getWidth () const
  { return m_width ; }

  inline int getHeight () const
  { return m_height ; }

  inline void setPoint (const int X, const int Y)
  { m_point.x = X ; m_point.y = Y ; queue_draw() ; }

protected:

  //-- Methodes PROTECTED

 /**
  * Methode heritee de la classe Draw
  */
  bool on_expose_event(GdkEventExpose* event);

  void draw_point (Glib::RefPtr<Gdk::Window> win,
		   Glib::RefPtr<Gdk::GC> gc,
		   const int x, const int y) ;
private:

  point2D m_point ;

  point2D m_origin ;
  int     m_width ;
  int     m_height ;

  Gdk::Color  m_lines_color ;
  int         m_points_size ;

};

#endif /* DRAWVIEW_H*/
