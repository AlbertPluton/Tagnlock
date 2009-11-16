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


#include "Toolchain.h"

#include "EditToolchainNodeGTKMM.h"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;




//! This class is an interface to the toolchain window and the engine. It is used to create new and alter exciting toolchains.

class ToolchainWindowGTKMM : public EngineGTKMM
{

	public:
		
		//! Default constructor
		ToolchainWindowGTKMM( int argc, char **argv, string gladeFileName );
		
		//! Default destructor
		~ToolchainWindowGTKMM();


		void displayToolchain( );
		void addToolchainOperation();
		void addChildToolchainOperation();
		void modifyToolchainNode();


	protected:
	
		//! This function connects signals to the corresponding functions
		void connectSignals();
		
		
		//! Signal handlers relating to the toolbar buttons.
		void newButton_clicked();
		void openButton_clicked();
		
		void addButton_clicked();
		void addChildButton_clicked();
		void deleteButton_clicked();
		
		void upButton_clicked();
		void downButton_clicked();
		void leftButton_clicked();
		void rightButton_clicked();
		
		//! Signal handlers relating to the selection of rows in the treeview.
		void treeViewRowSelected( ); // const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
		
		
	private:
		
		// Pointer to the main window
		Gtk::Window* toolchainWindow;

		Gtk::TreeView* treeView; 
		Gtk::TextView* textView;
		Gtk::ScrolledWindow*	editView;		
		
		// The connection between a EditToolchainNodeGTKMM object and this object.
		// It is used to delete the connection just before removing the EditToolchainNodeGTKMM object
		sigc::connection editConnection1, editConnection2;
		
		// Used to update the text edit field
		void updateTextView();
		
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
		Glib::RefPtr<Gtk::TreeSelection> refTreeViewSelection; 

		
		//! Function to add childeren of a node to the treeview
		/*!
			\param parent is a pointer to the parent node.
			\param parentRow is the row of the parent in the tree view.
		*/
		void addChilderenToTree( ToolchainNode* parent, Gtk::TreeModel::Row* parentRow );
	
};

#endif

