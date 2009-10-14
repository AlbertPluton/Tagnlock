//
//	Author: A.L. Hertog
//	Date: 8 January 2009
//	License: GPL
//
//






#ifndef ENGINEGTK_H
#define ENGINEGTK_H

#include "Engine.h"

#include "Category.h"
#include "FieldGTKMM.h"
#include "CategoryGTKMM.h"
#include "CategoryTreeGTKMM.h"
#include "FieldEditWidgetGTKMM.h"


#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;



//! This is the engine for the GTK GUI.

class EngineGTKMM : public Engine
{

	public:
		
		//! The default constructor
		/*!
			\param argc arguments/parameters from the main function.
			\param argv arguments/parameters from the main function.
			\param gladeFileName location and name of the glade xml file describing the GUI.
		*/
		EngineGTKMM( int argc, char **argv, string gladeFileName );
		
		~EngineGTKMM();
	
		//! Load a category by opening a dialog.
		/*!
			\returns true if all was succesfull.
		*/
		virtual bool loadCategory();	
	
	
		// === The following functions are implementations of the virtual functions in the Engine class ====================


		// --- Functions relating to the general program flow ---------------------
		void quit();

	
		
		
		// --- Functions relating to Toolchain ------------------------------------
		



void on_toolbutton25_clicked(  );




	
	protected:

		//! This function connects signals to the corresponding functions
		virtual void connectSignals(){};
		
  	Glib::RefPtr<Gnome::Glade::Xml> refXml;

		Gtk::Main* kit;

		
	private:


		Gtk::Window* toolchainWindow;

		



};










#endif



