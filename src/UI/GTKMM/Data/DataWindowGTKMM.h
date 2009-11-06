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
		void executeButton_clicked();


		// Functions to update combo lists
		void update_comboDatahandlers();
		void update_comboFilesTodo();
		void update_comboToolchains();


	protected:

		//! This function connects signals to the corresponding functions
		void connectSignals();


	private:
	
		// Virtual functions derived from the Configuration class
		virtual void parseToConfig();
		virtual void updateFromConfig();




		Gtk::Window* dataWindow;

		Gtk::ScrolledWindow* categoryScrolledWindow;

		Gtk::Alignment* displayWindow;
		DisplayFile* displayFile;

		CategoryGTKMM* category;


		DataAssistantGTKMM* datahandlerAssistant;
			
			
		Gtk::ComboBoxText* comboDatahandlers;
		Gtk::ComboBoxText* comboFilesTodo;
		Gtk::ComboBoxText* comboToolchains;
		
		// signal refrences to disable the combo signals
		sigc::connection comboSignalDatahandlers;
		sigc::connection comboSignalFilesTodo;
		sigc::connection comboSignalToolchains;
		
		// Signal functions for the combo's	
		void comboDatahandlers_changed();
		void comboFilesTodo_changed();
		void comboToolchains_changed();
		
		
		Gtk::Statusbar* statusbar;
		
};


#endif



