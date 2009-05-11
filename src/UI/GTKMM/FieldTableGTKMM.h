//
//	Author: A.L. Hertog
//	Date: 9 April 2009
//	License: GPL
//
//

#ifndef FIELDTABLEGTKMM_H
#define FIELDTABLEGTKMM_H

#include <gtkmm.h>

#include "FieldGTKMM.h"
#include "Category.h"
#include "ObjectData.h"

//! This class holds all FieldGTKMM objects in a signle table.

class FieldTableGTKMM : Gtk::VBox
{

	public:
		FieldTableGTKMM();
		~FieldTableGTKMM();
	
		//! Add a signle field to the current table.
		void addField( Gtk::Widget* field );
		//! Delete the field at index.
		void deleteField( int index );

		//! Create a new table from the given category.
		void makeNewTable( Category* category );
		//! Create a new empty table from the given object.
		void makeNewTable( ObjectData* object );
	
		//! Fill the current table with the data from the given object.
		void fillTable( ObjectData* object );
		
		//! Renew the table if some field has changed. 
		void renewTable( );
		
	private:
	
		ObjectData* objectData;

};



#endif
