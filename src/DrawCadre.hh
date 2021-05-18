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

#ifndef DRAWCADRE_H
#define DRAWCADRE_H

#include "Draw.hh"
#include "point2D.hh"
#include "Cadre.hh"
#include "DrawView.hh"

class DrawCadre : public Draw
{
public:

  //-- Constructeurs / Destructeur PUBLIC

  DrawCadre (int w, int h);

  //-- Accesseurs

  inline void set_zoneView (DrawView *zoneView)
  { m_zoneView = zoneView ; }

protected:

  //-- Methodes PROTECTED

 /**
  * Methode heritee de la classe Draw
  */
  bool on_expose_event(GdkEventExpose* event);

  /**
   * Methode heritee de Gtk::Widget
   */
  bool on_button_press_event (GdkEventButton* event) ;

  /**
   * Methode heritee de Gtk::Widget
   */
  bool on_button_release_event (GdkEventButton* event) ;

  bool on_motion_notify_event (GdkEventMotion* event) ;

  bool is_in_handle (int X, int Y, struct point2D handle) ;

  void draw_handle (Glib::RefPtr<Gdk::Window> win, Glib::RefPtr<Gdk::GC> gc, struct point2D handle) ;

  void queue_draw_area_optimizedForHandle (struct point2D handle) ;

private:

  Cadre m_cadre ;

  DrawView *m_zoneView ;

  point2D m_A ;
  point2D m_B ;
  point2D m_C ;
  point2D m_D ;

  bool m_A_isMoving ;
  bool m_B_isMoving ;
  bool m_C_isMoving ;
  bool m_D_isMoving ;

  int         m_handles_size ;
  Gdk::Color  m_handles_color_border ;
  Gdk::Color  m_handles_color_fill ;
  Gdk::Color  m_lines_color ;

};

#endif /* DRAWCADRE_H*/
