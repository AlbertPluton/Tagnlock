//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	License: GPL
//
//


#ifndef DATAWINDOWGTKMM_H
#define DATAWINDOWGTKMM_H

#include "EngineGTKMM.h"



#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class is an interface to the data window and the engine. It is used to process user input among other relevant things.

class DataWindowGTKMM : public EngineGTKMM
{

	public:
	
		//! The default constructor.
		/*!
			\param data is a pointer to the data window.
		*/
		DataWindowGTKMM( int argc, char **argv, string gladeFileName );
		
		//! The default destructor.
		~DataWindowGTKMM();



		void displayDatahandlerObject();
		void displayNextDatahandler();
		void displayPreviousDatahandler();
		void displayNextObjectData();
		void displayPreviousObjectData();
		void readDataFromUI();



	protected:

		//! This function connects signals to the corresponding functions
		void connectSignals();


	private:
	
			Gtk::Window* dataWindow;


};


#endif



