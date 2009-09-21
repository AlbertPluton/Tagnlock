//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	License: GPL
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
		/*!
			\param data is a pointer to the data window.
		*/
		CategoryWindowGTKMM( int argc, char **argv, string gladeFileName );
		
		//! The default destructor.
		~CategoryWindowGTKMM();


		void loadShowCategory();
		bool saveCategory();
		void newField();
		void modifyField();
		void displayCategory( int index );
		
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



