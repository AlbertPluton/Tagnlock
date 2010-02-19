//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef CATEGORYWINDOWGTKMM_H
#define CATEGORYWINDOWGTKMM_H

#include "EngineGTKMM.h"



#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class is an interface to the data window and the engine. It is used to process user input among other relevant things.

class CategoryWindowGTKMM : public EngineGTKMM
{

	public:
	
		//! The default constructor.
		CategoryWindowGTKMM( int argc, char **argv, string gladeFileName );
		
		//! The default destructor.
		~CategoryWindowGTKMM();

		// Callback functions
		void onButton_new();
		void onButton_open();

		void onButton_back();
		void onButton_forward();
		
		void onButton_add();
		void onButton_delete();
		void onButton_up();
		void onButton_down();



		void modifyField();
		void displayCategory( int index );

		// Used to set the field selected by the user in the tree or table view.		
		void fieldSelected( int select );



	protected:

		//! This function connects signals to the corresponding functions
		void connectSignals();


	private:

		Gtk::Window* categoryWindow;
		
		
		// Variables specifically required for the category window
		Gtk::ScrolledWindow* categoryFieldsWindow;
		CategoryGTKMM* categoryGTKMM;
		
	  
	  // Variables used in the tree view of the category window
	  Gtk::ScrolledWindow* categoryTreeWindow;
		
		// Variables used for the edit window of the category window
		Gtk::ScrolledWindow* categoryFieldEditWindow;




};

#endif



