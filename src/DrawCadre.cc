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

#include "DrawCadre.hh" 

/////////////////////////////////////////
//-- Constructeurs / Destructeur PUBLIC
/////////////////////////////////////////

DrawCadre::DrawCadre (int w, int h)
  : Draw (w, h),
    m_A_isMoving (false),
    m_B_isMoving (false),
    m_C_isMoving (false),
    m_D_isMoving (false),
    m_handles_size (2),
    m_handles_color_border ("black"),
    m_handles_color_fill ("white"),
    m_lines_color ("black")
{
  /* Initialisation des points */
  m_A.x = w / 4 ;
  m_A.y = h / 4 ;

  m_B.x = 3 * w / 4 ;
  m_B.y = h / 4 ;

  m_C.x = w / 4 ;
  m_C.y = 3 * h / 4 ;

  m_D.x = 3 * w / 4 ;
  m_D.y = 3 * h / 4 ;

  /* Activer l'ecoute des evenements de la souris */
  Gdk::EventMask flags = get_events();
  flags |= (Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK);
  set_events(flags);
}


/////////////////////////
//-- Methodes PROTECTED
/////////////////////////

/**
 * Methode heritee de la classe Draw
 */
bool DrawCadre::on_expose_event(GdkEventExpose* event)
{
  Draw::on_expose_event(event) ;

  Glib::RefPtr<Gdk::Window> win = get_window () ;
  Glib::RefPtr<Gdk::GC> gc = get_style()->get_black_gc();

  /* Dessiner le cadre */
  gc->set_rgb_fg_color (m_lines_color) ;
  win->draw_line(gc,
		 m_A.x, m_A.y,
		 m_B.x, m_B.y) ;
  win->draw_line(gc,
		 m_B.x, m_B.y,
		 m_D.x, m_D.y) ;
  win->draw_line(gc,
		 m_D.x, m_D.y,
		 m_C.x, m_C.y) ;
  win->draw_line(gc,
		 m_C.x, m_C.y,
		 m_A.x, m_A.y) ;

  /* Dessiner les poignees */
  draw_handle (win, gc, m_A) ;
  draw_handle (win, gc, m_B) ;
  draw_handle (win, gc, m_C) ;
  draw_handle (win, gc, m_D) ;
}

bool DrawCadre::on_button_press_event (GdkEventButton* event)
{
  if (event->button == 1) { // Left button
    if ((int)event->x > 0 && (int)event->x <= m_pixbuf->get_width()
	&& (int)event->y > 0 && (int)event->y <= m_pixbuf->get_height()) {

      if (is_in_handle ((int)event->x, (int)event->y, m_A)) { 
	/* Si le clic est sur A */

	// m_A.x = (int)event->x ;
	// m_A.y = (int)event->y ;

	m_A_isMoving = true ;
      }
      else if (is_in_handle ((int)event->x, (int)event->y, m_B)) { 
	/* Si le clic est sur B */
	m_B_isMoving = true ;
      }
      else if (is_in_handle ((int)event->x, (int)event->y, m_C)) { 
	/* Si le clic est sur C */
	m_C_isMoving = true ;
      }
      else if (is_in_handle ((int)event->x, (int)event->y, m_D)) { 
	/* Si le clic est sur D */
	m_D_isMoving = true ;
      }
    }
  }
}

bool DrawCadre::on_motion_notify_event (GdkEventMotion* event)
{
  if (m_A_isMoving) {
    /* Si le clic de depart etait sur A */
    m_A.x = (int)event->x ;
    m_A.y = (int)event->y ;
   }
  else if (m_B_isMoving) {
    /* Si le clic de depart etait sur B */
    m_B.x = (int)event->x ;
    m_B.y = (int)event->y ;
   }
  else if (m_C_isMoving) {
    /* Si le clic de depart etait sur C */
    m_C.x = (int)event->x ;
    m_C.y = (int)event->y ;
   }
  else if (m_D_isMoving) {
    /* Si le clic de depart etait sur D */
    m_D.x = (int)event->x ;
    m_D.y = (int)event->y ;
   }
  else {
    /* Move point in the view zone */
    Cadre::point A, B, C, D, Psrc, Pdst ;
    Cadre::point_set (&A, m_A.x, m_A.y) ;
    Cadre::point_set (&B, m_B.x, m_B.y) ;
    Cadre::point_set (&C, m_C.x, m_C.y) ;
    Cadre::point_set (&D, m_D.x, m_D.y) ;
    Cadre::point_set (&Psrc, (int)event->x, (int)event->y) ;

    m_cadre.setZone (A, B, C, D) ;
    m_cadre.redresser (Psrc,
		       m_zoneView->getOriginX(), m_zoneView->getOriginY(),
		       m_zoneView->getWidth(), m_zoneView->getHeight(),
		       &Pdst) ;

    m_zoneView->setPoint ((int)Pdst.x, (int)Pdst.y) ;
  }

  this->queue_draw () ;
}

bool DrawCadre::on_button_release_event (GdkEventButton* event)
{
  if (m_A_isMoving) {
    /* Si le clic de depart etait sur A */
    m_A.x = (int)event->x ;
    m_A.y = (int)event->y ;
    m_A_isMoving = false ;
  }
  else if (m_B_isMoving) {
    /* Si le clic de depart etait sur B */
    m_B.x = (int)event->x ;
    m_B.y = (int)event->y ;
    m_B_isMoving = false ;
  }
  else if (m_C_isMoving) {
    /* Si le clic de depart etait sur C */
    m_C.x = (int)event->x ;
    m_C.y = (int)event->y ;
    m_C_isMoving = false ;
  }
  else if (m_D_isMoving) {
    /* Si le clic de depart etait sur D */
    m_D.x = (int)event->x ;
    m_D.y = (int)event->y ;
    m_D_isMoving = false ;
  }

  this->queue_draw () ;
}

bool DrawCadre::is_in_handle (int X, int Y, struct point2D handle)
{
  return X >= handle.x - m_handles_size
    && X <= handle.x + m_handles_size
    && Y >= handle.y - m_handles_size
    && Y <= handle.y + m_handles_size ;
}

void DrawCadre::draw_handle (Glib::RefPtr<Gdk::Window> win, Glib::RefPtr<Gdk::GC> gc, struct point2D handle)
{
  gc->set_rgb_fg_color (m_handles_color_border) ;

  win->draw_rectangle (gc, false,
		       handle.x - m_handles_size,
		       handle.y - m_handles_size,
		       m_handles_size + m_handles_size,
		       m_handles_size + m_handles_size) ;

  gc->set_rgb_fg_color (m_handles_color_fill) ;

  win->draw_rectangle (gc, true,
		       handle.x - m_handles_size + 1,
		       handle.y - m_handles_size + 1,
		       m_handles_size + m_handles_size - 1,
		       m_handles_size + m_handles_size - 1) ;
}

void DrawCadre::queue_draw_area_optimizedForHandle (struct point2D handle)
{
  this->queue_draw_area(handle.x - m_handles_size-1,
			handle.y - m_handles_size-1,
			m_handles_size + m_handles_size + 2,
			m_handles_size + m_handles_size + 2) ;
}
