//
//	Author: A.L. Hertog
//	Date: 12 May 2009
//	License: GPL
//
//



#ifndef CATEGORYTREEGTKMM_H
#define CATEGORYTREEGTKMM_H


#include "Category.h"
#include "Field.h"

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


#include <sigc++/sigc++.h>



//! This is a GTKMM widget derived from Gtk::TreeView to display an overview of a category.

class CategoryTreeGTKMM : public Gtk::TreeView
{

	public:
	
		//! The default constructor.
		CategoryTreeGTKMM( Category* cat = NULL );

		//! The default destructor.
		~CategoryTreeGTKMM();

		//! Generates a TreeModel from the category.
		void makeTreeModel( Category* cat );

		
		//! Clear the model.
		void clearTreeModel( void );
		
		
		//! Update the properties of the category in this tree.
		void updateProperties();
		
		
  	typedef sigc::signal<void, int> type_signal_selectionChange;
  	
  	//! This is the signal to indicate a change of the selected field.
  	type_signal_selectionChange get_signal_selectionChange( void );


	private:

		void selectionChange( void );
		
		type_signal_selectionChange signal_selectionChange;
		
		
		Glib::RefPtr<Gtk::TreeStore> 			categoryTreeModel;
	  Gtk::TreeModel::ColumnRecord 			categoryColumns;
		Glib::RefPtr<Gtk::TreeSelection> 	categoryTreeSelection; 
	  
	  Gtk::TreeModelColumn<int> 						columnIndex;
	  Gtk::TreeModelColumn<Glib::ustring> 	columnFieldType;
	  Gtk::TreeModelColumn<Glib::ustring> 	columnFieldLabel;
		Gtk::TreeModelColumn<bool> 						columnFieldRequired;
		Gtk::TreeModelColumn<bool> 						columnFieldReset;

		Category* category;

};

#endif


