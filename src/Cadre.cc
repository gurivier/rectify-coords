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

#include <iostream>
#include <fstream>

#include "Cadre.hh"

/////////////////////////////////
//-- Fonctions statiques PUBLIC
/////////////////////////////////

void Cadre::point_set (Cadre::point *p, double x, double y)
{
  p->x = x ;
  p->y = y ;
}

////////////////////////////////////////
//-- Constructeur / Destructeur PUBLIC
////////////////////////////////////////

Cadre::Cadre ()
{
  // Rien
}

Cadre::Cadre (const Cadre& source)
  : m_A (source.m_A),
    m_B (source.m_B),
    m_C (source.m_C),
    m_D (source.m_D),
    m_AC (source.m_AC),
    m_BD (source.m_BD),
    m_AB (source.m_AB),
    m_CD (source.m_CD),
    m_parallel1 (source.m_parallel1),
    m_parallel2 (source.m_parallel2),
    m_I1 (source.m_I1),
    m_I2 (source.m_I2)
{
}

Cadre::Cadre (const point A, const point B, const point C, const point D)
  : m_A (A),
    m_B (B),
    m_C (C),
    m_D (D)
{
  setup () ;
}

Cadre::~Cadre ()
{
  // Rien
}

////////////////////////
//-- Accesseurs PUBLIC
////////////////////////

void Cadre::setZone (const point A, const point B, const point C, const point D)
{
  m_A = A ;
  m_B = B ;
  m_C = C ;
  m_D = D ;
  
  setup () ;
}

//////////////////////
//-- Methodes PUBLIC
//////////////////////

void Cadre::redresser (const point P_src,
		       const double X_dest, const double Y_dest,
		       const double W_dest, const double H_dest,
		       point *P_dest)
{

  /* --------------- */

  double P_percentY ;
  point Pab_src, Pcd_src ;

  if (m_parallel1) {
    projection_orthogonale (m_AB, P_src, &Pab_src) ;
    projection_orthogonale (m_CD, P_src, &Pcd_src) ;
  }
  else {
    droite PI1_src ;
    equation_affine (P_src, this->m_I1, &PI1_src) ;
    intersection (PI1_src, this->m_AB, &Pab_src) ;
    intersection (PI1_src, this->m_CD, &Pcd_src) ;
  }
  
  P_percentY = distance (Pab_src, P_src) * 100.0 / distance (Pab_src, Pcd_src) ;
  if (!meme_sens (Pab_src, P_src, Pab_src, Pcd_src))
    P_percentY *= -1 ;

  /* --------------- */

  double P_percentX ;
  point Pac_src, Pbd_src ;
  
  if (m_parallel2) {
    projection_orthogonale (m_AC, P_src, &Pac_src) ;
    projection_orthogonale (m_BD, P_src, &Pbd_src) ;
  }
  else {
    droite PI2_src ;
    equation_affine (P_src, this->m_I2, &PI2_src) ;  
    intersection (PI2_src, this->m_AC, &Pac_src) ;
    intersection (PI2_src, this->m_BD, &Pbd_src) ;
  }
  
  P_percentX = distance (Pac_src, P_src) * 100.0 / distance (Pac_src, Pbd_src) ;
  if (!meme_sens (Pac_src, P_src, Pac_src, Pbd_src))
    P_percentX *= -1 ;
  
  /* --------------- */

  P_dest->x = X_dest + P_percentX * W_dest / 100.0 ;
  P_dest->y = Y_dest + P_percentY * H_dest / 100.0 ;
}

void Cadre::serialize (ofstream& out)
{
  point_serialize (m_A, out) ;
  point_serialize (m_B, out) ;
  point_serialize (m_C, out) ;
  point_serialize (m_D, out) ;

  droite_serialize (m_AC, out) ;
  droite_serialize (m_BD, out) ;
  droite_serialize (m_AB, out) ;
  droite_serialize (m_CD, out) ;

  out << m_parallel1 << endl ;
  out << m_parallel2 << endl ;

  point_serialize (m_I1, out) ;
  point_serialize (m_I2, out) ;
}

void Cadre::unserialize (ifstream& in)
{
  point_unserialize (&m_A, in) ;
  point_unserialize (&m_B, in) ;
  point_unserialize (&m_C, in) ;
  point_unserialize (&m_D, in) ;

  droite_unserialize (&m_AC, in) ;
  droite_unserialize (&m_BD, in) ;
  droite_unserialize (&m_AB, in) ;
  droite_unserialize (&m_CD, in) ;

  in >> m_parallel1 ;
  in >> m_parallel2 ;

  point_unserialize (&m_I1, in) ;
  point_unserialize (&m_I2, in) ;
}

/////////////////////////
//-- Methodes PROTECTED
/////////////////////////

void Cadre::setup ()
{
  equation_affine (m_A, m_C, &m_AC) ;
  equation_affine (m_B, m_D, &m_BD) ;
  equation_affine (m_A, m_B, &m_AB) ;
  equation_affine (m_C, m_D, &m_CD) ;  

  if (paralleles (m_AC, m_BD)) {
    m_parallel1 = true ;
  }
  else {
    m_parallel1 = false ;
    intersection (m_AC, m_BD, &m_I1) ;
  }

  if (paralleles (m_AB, m_CD)) {
    m_parallel2 = true ;
  }
  else {
    m_parallel2 = false ;
    intersection (m_AB, m_CD, &m_I2) ;
  }
}

////////////////////////////////////
//-- Fonctions statiques PROTECTED
////////////////////////////////////

void Cadre::point_serialize (const point p, ofstream& out)
{
  out << p.x << endl ;
  out << p.y << endl ;
}

void Cadre::point_unserialize (point *p, ifstream& in)
{
  in >> p->x ;
  in >> p->y ;
}

void Cadre::droite_serialize (const droite d, ofstream& out)
{
  out << d.a << endl ;
  out << d.b << endl ;
  out << d.asymptote << endl ;
  out << d.x << endl ;
}

void Cadre::droite_unserialize (droite *d, ifstream& in)
{
  in >> d->a ;
  in >> d->b ;
  in >> d->asymptote ;
  in >> d->x ;
}

void Cadre::equation_affine (Cadre::point p1, Cadre::point p2, Cadre::droite *d)
{
  if (p1.x == p2.x) {
    d->asymptote = true ;
    d->x = p1.x ;
  }
  else {
    d->a = (p1.y - p2.y) / (p1.x - p2.x) ;
    d->b = p2.y - (d->a * p2.x) ;
    d->asymptote = false ;
  }
}

void Cadre::equation_affine_perpendiculaire (Cadre::droite d1, Cadre::point P, Cadre::droite *d2)
{
  if (d1.asymptote) {
    d2->a = 0 ;
    d2->b = P.y ;
    d2->asymptote = false ;
  }
  else if (d1.a == 0) {
    d2->asymptote = true ;
    d2->x = P.x ;
  }
  else {
    d2->a = -1 / d1.a ;
    d2->b = P.y + P.x / d1.a ;
    d2->asymptote = false ;
  }
}

void Cadre::projection_orthogonale (Cadre::droite d, Cadre::point P1, Cadre::point *P2)
{
  Cadre::droite d2 ;
  equation_affine_perpendiculaire (d, P1, &d2) ;
  intersection (d, d2, P2) ;
}

double Cadre::distance (Cadre::point p1, Cadre::point p2)
{
  return sqrt ((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)) ;
}

void Cadre::intersection (Cadre::droite d1, Cadre::droite d2, Cadre::point *p)
{
  if (d1.asymptote) {
    p->x = d1.x ;
    p->y = d2.a * p->x + d2.b ;
  }
  else if (d2.asymptote) {
    p->x = d2.x ;
    p->y = d1.a * p->x + d1.b ;
  }
  else {
    p->x = (d2.b - d1.b) / (d1.a - d2.a) ;
    p->y = d1.a * p->x + d1.b ;
  }
}

bool Cadre::paralleles (Cadre::droite d1, Cadre::droite d2)
{
  return (d1.a == d2.a) || (d1.asymptote && d2.asymptote) ;
}

// bool Cadre::meme_sens (point Ud, point Uf, point Vd, point Vf)
// {
//   /* ----------- */

//   double U_sens_x (Uf.x - Ud.x) ;
//   if (U_sens_x > 0)
//     U_sens_x = 1 ;
//   else if (U_sens_x < 0)
//     U_sens_x = -1 ;

//   /* ----------- */

//   double U_sens_y (Uf.y - Ud.y) ;
//   if (U_sens_y > 0)
//     U_sens_y = 1 ;
//   else if (U_sens_y < 0)
//     U_sens_y = -1 ;

//   /* ----------- */

//   double V_sens_x (Vf.x - Vd.x) ;
//   if (V_sens_x > 0)
//     V_sens_x = 1 ;
//   else if (V_sens_x < 0)
//     V_sens_x = -1 ;

//   /* ----------- */

//   double V_sens_y (Vf.y - Vd.y) ;
//   if (V_sens_y > 0)
//     V_sens_y = 1 ;
//   else if (V_sens_y < 0)
//     V_sens_y = -1 ;

//   /* ----------- */
  
//   if (U_sens_x == 0 && U_sens_y == V_sens_y)
//     return true ;

//   if (U_sens_y == 0 && U_sens_x == V_sens_x)
//     return true ;

//   if (V_sens_x == 0 && U_sens_y == V_sens_y)
//     return true ;
  
//   if (V_sens_y == 0 && U_sens_x == V_sens_x)
//     return true ;
  
//   if (U_sens_x == V_sens_x && U_sens_y == V_sens_y)
//     return true ;

//   return false ;
// }

bool Cadre::meme_sens (point Ud, point Uf, point Vd, point Vf) {
  return produit_scalaire (Ud, Uf, Vd, Vf) > 0 ;
}

double Cadre::produit_scalaire (point Ud, point Uf, point Vd, point Vf)
{
  double Ux = Uf.x - Ud.x ;
  double Uy = Uf.y - Ud.y ;

  double Vx = Vf.x - Vd.x ;
  double Vy = Vf.y - Vd.y ;

  return Ux * Vx + Uy * Vy ;
}
