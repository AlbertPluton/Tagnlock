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
#include "FieldTableGTKMM.h"

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


		// --- Functions relating to the general program flow ---------------------
		void quit();

	
		// --- Functions relating to Category -------------------------------------
		void loadCategory();
		void saveCategory();
		void newField();
		void modifyField();
		void displayCategory( int index );
		
		void fieldSelectionChange( void );
		

		// --- Functions relating to Datahandler ----------------------------------
		
		void displayDatahandlerObject();
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

		//! This function connects signals to the corresponding functions
		void connectSignals();
		

		//! Functions secifically required for teh cateory window
		void makeCategoryTreeModel( Category* cat );


		Gtk::Main* kit;
		Gtk::Window* dataWindow;
		Gtk::Window* toolchainWindow;
		Gtk::Window* categoryWindow;
		
		
		// Variables specifically required for the category window
		Gtk::ScrolledWindow* categoryFieldsWindow;
		FieldTableGTKMM* fieldTableGTKMM;
		
	  
	  // Variables used in the tree view of the category window
	  Gtk::TreeView* categoryTreeView;
	  Glib::RefPtr<Gtk::ListStore> categoryTreeModel;
	  Gtk::TreeModel::ColumnRecord categoryColumns;
		Glib::RefPtr<Gtk::TreeSelection> categoryTreeSelection; 
	  
	  Gtk::TreeModelColumn<Glib::ustring> columnFieldType;
	  Gtk::TreeModelColumn<Glib::ustring> columnFieldLabel;
		Gtk::TreeModelColumn<bool> columnFieldRequired;
		Gtk::TreeModelColumn<bool> columnFieldReset;



		
		
  	Glib::RefPtr<Gnome::Glade::Xml> refXml;		



};










#endif

