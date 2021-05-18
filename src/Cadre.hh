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
 * Classe Cadre
 * """"""""""""
 * Guillaume RIVIERE
 * 28 Fevrier 2007
 *
 * Cette classe permet de representer un cadre
 * definit par 4 points point quelconques : A, B, C, D.
 *
 * En particulier une fonction permet de redresser les
 * coordonnees d'un point P definit dans cadre quelconque
 * vers une zone rectangulaire othonormee.
 */

#ifndef CADRE_HH
#define CADRE_HH

#include <sstream>
#include <math.h>

using namespace std ;

class Cadre {
  
public:

  struct droite {
    double a ;
    double b ;
    bool asymptote ;
    double x ;
  } ;


  struct point {
    double x ;
    double y ;
  } ;

  //-- Fonctions statiques

  static void point_set (point *p, double x, double y) ;

  //-- Constructeur / Destructeur

  Cadre () ;

  Cadre (const Cadre& source) ;

  Cadre (const point A, const point B, const point C, const point D) ;

  ~Cadre () ;

  //-- Accesseurs

  void setZone (const point A, const point B, const point C, const point D) ;

  //-- Methodes

  /**
   * Redresse les coordonnees d'un point du cadre vers une zone rectangulaire.
   *
   * @param P_src  Le point a redresser (Coordonnees dans le cadre).
   * @param X_dest Abscisse du point haut gauche de la zone rectangulaire.
   * @param Y_dest Ordonnee du point haut gauche de la zone rectangulaire.
   * @param W_dest Largeur de la zone rectangulaire.
   * @param H_dest Hauteur de la zone rectangulaire.
   * @param P_dest Le point redresse (Coordonnees dans la zone rectangulaire).
   */
  void redresser (const point P_src,
		  const double X_dest, const double Y_dest,
		  const double W_dest, const double H_dest,
		  point *P_dest) ;

  void serialize (ofstream& out) ;

  void unserialize (ifstream& in) ;

protected:

  //-- Methodes

  void setup () ;

  //-- Fonctions statiques

  void point_serialize (const point p, ofstream& out) ;
  void point_unserialize (point *p, ifstream& in) ;
  void droite_serialize (const droite d, ofstream& out) ;
  void droite_unserialize (droite *d, ifstream& in) ;

  /**
   * Calculer l'equation affine d : y = ax + b
   * passant par les points p1 et p2.
   */
  static void equation_affine (point p1, point p2, droite *d) ;

  /**
   * Cette fonction calcule la droite d2 perpendiculaire a d1 passant par P.
   */
  static void equation_affine_perpendiculaire (droite d1, point P, droite *d2) ;

  /**
   * Cette fonction calcule P2 la projection orthogonale de P1 sur d.
   */
  static void projection_orthogonale (droite d, point P1, point *P2) ;

  /**
   * Cette fonction calcule la distance entre p1 et p2
   */
  static double distance (point p1, point p2) ;

  /**
   * Cette fonction calcule le point d'intersection p entre d1 et d2
   */
  static void intersection (droite d1, droite d2, point *p) ;

  /**
   * Cette fonction verifie si deux droites sont paralleles.
   * Retourne vrai si d1 et d2 sont paralleles, faux sinon.
   */
  static bool paralleles (droite d1, droite d2) ;

  /**
   * Soient deux vecteurs orientes U = (Ud, Uf) et V = (Vd, Vf).
   * Cette fonction verifie le sens entre les deux vecteurs U et V.
   * Retourne vrai si U et V vont dans le meme sens, faux sinon.
   */
  static bool meme_sens (point Ud, point Uf, point Vd, point Vf) ;

  static double produit_scalaire (point Ud, point Uf, point Vd, point Vf) ;

private:

  //-- Attributs

  point m_A ;
  point m_B ;
  point m_C ;
  point m_D ;

  droite m_AC ;
  droite m_BD ;
  droite m_AB ;
  droite m_CD ;

  bool m_parallel1 ;
  bool m_parallel2 ;
  point m_I1 ;
  point m_I2 ;
} ;

#endif /* CADRE_HH */
