
# Rectify Points Coordinates (rectify-coords)

This program demonstrates the use of the C++ class called "Cadre" that can be used to rectify coordinates from a deformed quadrilateral shape to a rectangular shape.

This class is useful, for example, in vision-projection tabletops. When the projected image is deformed into a trapezoid, the coordinates of the points captured in the video must be recalculated to match the initial data model (i.e. before projection). This class then allows to find the coordinates relative to the pre-projection model.

## Principle

Let P be a 2D point expressed in a plane area defined by four 2D points A,B,C,D. The aim of our C++ class is to express the coordinates of P in order to match when A,B,C,D is rectified as a rectangle. A demo application in GTKmm shows the use of the C++ class.

![Calculation from distorted to corrected coordinates](https://user-images.githubusercontent.com/83834659/118980304-a4ae4d80-b979-11eb-9644-8c22e7ea003c.png)


The demo application shows the use of the "Cadre" C++ class. The window is divided in two parts. On the left, a drawing area shows the source quadrilateral, which can be modified using four handles. On the right, a drawing area shows the destination rectangle. The position of the mouse cursor on the left area is mapped on the right view after rectification to match with the rectangle.

![The window shows the rectified point on the right corresponding to the mouse cursor on the left](https://user-images.githubusercontent.com/83834659/118980518-d6271900-b979-11eb-90e9-bce7fc2844fe.jpg)

## Source code

The source code was writen in C++ under Debian GNU/Linux, using g++ and GTKmm 2.2.

## References

This project was first hosted on sourceforge:
https://sourceforge.net/projects/rectify-coords/

This work has been published in Chapter 5 of:
Guillaume Rivière, Tangible Interaction on Tabletops: applied in geoscience. Ph.D. thesis, Bordeaux University, September 9th, 2009. https://tel.archives-ouvertes.fr/tel-01086092

## Author
Guillaume Rivière, 2007.

