//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	License: GPL
//
//


#ifndef DATAWINDOWGTKMM_H
#define DATAWINDOWGTKMM_H

#include "EngineGTKMM.h"

#include "DisplayFile.h"

#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "DataAssistantGTKMM.h"

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



		//! Display the current data object of the current datahandler.
		void displayDatahandlerObject();
		
		//! Go to the next datahandler and display its current data object.
		void displayNextDatahandler();
		//! Go to the previous datahandler and display its current data object.
		void displayPreviousDatahandler();
		
		//! Display the next object in the current datahandler.
		void displayNextObjectData();
		//! Display the previous object in the current datahandler.
		void displayPreviousObjectData();

		//! Read data from the UI and store it in a objectData object.
		void readDataFromUI();


		// Functions for buttons
		
		void newButton_clicked();
		void openButton_clicked();
		void saveButton_clicked();
		void saveAsButton_clicked();


	protected:

		//! This function connects signals to the corresponding functions
		void connectSignals();


	private:
	
			Gtk::Window* dataWindow;

			Gtk::ScrolledWindow* categoryScrolledWindow;

			Gtk::Alignment* displayWindow;
			DisplayFile* displayFile;

			CategoryGTKMM* category;


			DataAssistantGTKMM* datahandlerAssistant;


};


#endif



