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

// generated 2007/4/16 18:00:32 CEST by guillaume@pc-ludo-max2.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to Window1.cc_new

// This file is for your program, I won't touch it again!

#include <iostream>

#include "config.h"
#include "Window1.hh"

using namespace std ;

Window1::Window1 ()
{

 /* --- Zone de dessin du cadre --- */

  /* Creation du zone de dessin de la classe Draw (herite de Gtk::DrawingArea) */
  m_zoneCadre = Gtk::manage (new class DrawCadre (256, 256)) ;

  /* Placement de la zone de dessin */
  viewport1->add(*m_zoneCadre);

  /* Le widget est pret */
  m_zoneCadre->show() ;
 
  /* Chargement d'une image */
  m_zoneCadre->set_image_from_file ("white.jpg") ;

 /* --- Zone de dessin du cadre --- */

  /* Creation du zone de dessin de la classe Draw (herite de Gtk::DrawingArea) */
  m_zoneView = Gtk::manage (new class DrawView (256, 256)) ;

  /* Placement de la zone de dessin */
  viewport2->add(*m_zoneView);

  /* Le widget est pret */
  m_zoneView->show() ;
 
  /* Chargement d'une image */
  m_zoneView->set_image_from_file ("white.jpg") ;

  /* ----------------------------- */


  m_zoneCadre->set_zoneView (m_zoneView) ;

  /* Raffraichissement de l'affichage (Ask for an expose event) */
  queue_draw () ;
}

Window1::~Window1 ()
{
  
}
