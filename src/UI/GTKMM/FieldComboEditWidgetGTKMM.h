//
//	Author: A.L. Hertog
//	Date: 19 Juni 2009
//	License: GPL
//
//

#ifndef FIELDCOMBOEDITWIDGETGTKMM_H
#define FIELDCOMBOEDITWIDGETGTKMM_H



#include "Category.h"
#include "Field.h"
#include "ComboField.h"
#include "FieldEditWidgetGTKMM.h"

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class represents a window in which the properties of a combo field can be edited.

class FieldComboEditWidgetGTKMM : public FieldEditWidgetGTKMM
{
	public:
	
		FieldComboEditWidgetGTKMM( Field* pField, int i );
		~FieldComboEditWidgetGTKMM();
		
	private:


		Gtk::Label labelOptions;
		Gtk::HBox hBoxOptions;
		Gtk::VBox vBoxButtons;


		Gtk::ScrolledWindow treeScrolledWindow;
		Gtk::TreeView treeView;
		Glib::RefPtr<Gtk::ListStore> treeModel;

		Gtk::Button addButton, delButton, upButton, downButton;
		
		
		void addedOption();
		void removedOption();
		void changedOption();
		
		
		// Pointer to the base class.
		ComboField* comboField;
	
	
		//Tree model columns:
		class ModelColumns : public Gtk::TreeModel::ColumnRecord
		{
		public:

		  ModelColumns()
		  { add( columnOption ); }

		  Gtk::TreeModelColumn<Glib::ustring> columnOption;

		};

		ModelColumns m_Columns;

	
	
	
	
};



#endif
