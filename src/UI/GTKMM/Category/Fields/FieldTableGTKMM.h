//
//	Author: A.L. Hertog
//	Date: 9 April 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef FIELDTABLEGTKMM_H
#define FIELDTABLEGTKMM_H

#include <gtkmm.h>

#include "FieldGTKMM.h"
#include "Category.h"
#include "ObjectData.h"

//#include <sigc++/sigc++.h>

//! This class holds all FieldGTKMM objects in a signle table.

class FieldTableGTKMM : public Gtk::VBox
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
		
		//! Delete all the fields this class holds.
		void clear();
		
		
		void fieldSelected( int fieldIndex );
		
  	typedef sigc::signal<void, int> type_signal_selectionChange;
  	
  	//! This is the signal to indicate a change of the selected field.
  	type_signal_selectionChange get_signal_selectionChange( void );
		
		
	private:
	
		ObjectData* objectData;

		type_signal_selectionChange signal_selectionChange;


		// An vector with all connection objects which this object has generated to receive signals from its children.
		vector<sigc::connection> connections;


};



#endif
