//
//	Author: A.L. Hertog
//	Date: 7 October 2009
//	License: GPL
//
//

#ifndef TOOLCHAINWINDOWGTKMM_H
#define TOOLCHAINWINDOWGTKMM_H



#include "EngineGTKMM.h"

#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "Datahandler.h"

#include "Toolchain.h"



#include <iostream>
#include <string>
using namespace std;




//! This class is an interface to the toolchain window and the engine. It is used to create new and alter exciting toolchains.

class ToolchainWindowGTKMM : public EngineGTKMM
{

	public:
		
		//! Default constructor
		ToolchainWindowGTKMM( int argc, char **argv, string gladeFileName );
		
		//! Default destructor
		~ToolchainWindowGTKMM();


		void dispalyToolchain( );
		void addToolchainOperation();
		void modifyToolchainNode();


	protected:
	
		//! This function connects signals to the corresponding functions
		void connectSignals();
		
		void newButton_clicked();
		void saveButton_clicked();
		void openButton_clicked();
		void addButton_clicked();
		void deleteButton_clicked();
		void upButton_clicked();
		void downButton_clicked();
		
	private:
		
		// Pointer to the main window
		Gtk::Window* toolchainWindow;

		Gtk::TreeView* treeView; 
		Gtk::TextView* textView;
		
		
		// The model used byt the treeview
		class ModelColumns : public Gtk::TreeModelColumnRecord
		{
		public:

			ModelColumns()
				{  add(col_number); add(col_name); add(col_description); add(col_nodePointer);}


			Gtk::TreeModelColumn<int> col_number;
			Gtk::TreeModelColumn<Glib::ustring> col_name;
			Gtk::TreeModelColumn<Glib::ustring> col_description;			
			Gtk::TreeModelColumn<ToolchainNode*> col_nodePointer;
			
		};

		ModelColumns treeViewColumns;
		Glib::RefPtr<Gtk::TreeStore> refTreeViewModel;
	
	
	
};

#endif

