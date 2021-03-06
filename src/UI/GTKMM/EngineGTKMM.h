//
//	Author: A.L. Hertog
//	Date: 8 January 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//






#ifndef ENGINEGTKMM_H
#define ENGINEGTKMM_H

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




		// --- Functions relating to Category ------------------------------------
	
	
		//! Load a category by opening a dialog.
		virtual void loadCategory();	

		//! Save a category with the file name given in the object. If non is given a dialog is opened.
		virtual void saveCategory();
		
		//! Save a category by opening a dialog.
		virtual void saveAsCategory();
		
		
		
		
		// --- Functions relating to Datahandler ----------------------------------
		
		
		//! Load a datahandler by opening a dialog.
		virtual void loadDatahandler();	

		//! Save a datahandler with the file name given in the object. If non is given a dialog is opened.
		virtual void saveDatahandler();
		
		//! Save a datahandler by opening a dialog.
		virtual void saveAsDatahandler();
				
		
		
		
		// --- Functions relating to Toolchain ------------------------------------
		
		
		//! Load a toolchain by opening a dialog.
		virtual void loadToolchain();	
		
		//! Save the toolchain under the file name given in the object
		virtual void saveToolchain();
		
		//! A dialog to save as a toolchain.
		virtual void saveAsToolchain();
	



		// --- Functions relating to the general program flow ---------------------
		bool quit( GdkEventAny* event );

	



void on_toolbutton25_clicked(  );




	
	protected:

		//! This function connects signals to the corresponding functions
		virtual void connectSignals(){};
		
  	Glib::RefPtr<Gnome::Glade::Xml> refXml;

		Gtk::Main* kit;

		
	private:




};










#endif



