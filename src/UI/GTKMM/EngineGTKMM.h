//
//	Author: A.L. Hertog
//	Date: 8 January 2009
//	License: GPL
//
//


#ifndef ENGINEGTK_H
#define ENGINEGTK_H


#include "Engine.h"

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
	
	
		// === The following functions are implementations of the virtual functions in the Engine class ====================
	
		// --- Functions relating to Category -------------------------------------
	
		void newField( int indexCategory );
		void modifyField();
		void displayCategory( int index );

		// --- Functions relating to Datahandler ----------------------------------
		
		void displayDatahandlerObject( );
		void displayNextDatahandler();
		void displayPreviousDatahandler();
		void displayNextObjectData();
		void displayPreviousObjectData();
		void readDataFromUI();
		
		// --- Functions relating to Toolchain ------------------------------------
		
		void dispalyToolchain( );
		void addToolchainOperation();
		void modifyToolchainNode();



void on_toolbutton25_clicked(  );




	
	private:

		void connectSignalsToToolButtons();




		Gtk::Main* kit;
		Gtk::Window* dataWindow;
		
  	Glib::RefPtr<Gnome::Glade::Xml> refXml;		



};










#endif

