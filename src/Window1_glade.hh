// generated 2007/4/17 18:33:40 CEST by guillaume@pc-ludo-max2.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/guillaume/GEOTUI/DEVEL_v3/redressement/redressement_demo/redressement_demo.glade
// for gtk 2.4.13 and gtkmm 2.2.12
//
// Please modify the corresponding derived classes in ./src/Window1.hh and./src/Window1.cc

#ifndef _WINDOW1_GLADE_HH
#  define _WINDOW1_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/window.h>
#include <gtkmm/viewport.h>

class Window1_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
protected:
        class Gtk::Viewport * viewport1;
        class Gtk::Viewport * viewport2;
        
        Window1_glade();
        
        ~Window1_glade();
};
#endif