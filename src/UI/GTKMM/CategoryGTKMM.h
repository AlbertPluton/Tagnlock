//
//	Author: A.L. Hertog
//	Date: 24 June 2009
//	License: GPL
//
//

#ifndef CATEGORYGTKMM_H
#define CATEGORYGTKMM_H

#include <gtkmm.h>

#include "FieldGTKMM.h"
#include "Category.h"
#include "ObjectData.h"
#include "CategoryTreeGTKMM.h"


#define defaultTableAttachX Gtk::FILL|Gtk::EXPAND
#define defaultTableAttachY Gtk::FILL

#define defaultColumns 10
#define defaultPaddingX 5
#define defaultPaddingY 5



//! This class holds all FieldGTKMM objects in a signle table.

class CategoryGTKMM : public Gtk::Table
{

	public:
		CategoryGTKMM( Gtk::ScrolledWindow* catTreeWindow, Gtk::ScrolledWindow* editWindow = NULL);
		~CategoryGTKMM();
	
		
		//! Add a signle field to the current table.
		void addField( FieldGTKMM* field );
		
		//! Delete the field at index.
		void deleteField( int index );

		//! Create a new table from the given category.
		void makeNewTable( Category* category );
		//! Create a new empty table from the given object.
		void makeNewTable( ObjectData* object );
	
		//! Fill the current table with the data from the given object.
		virtual void fillTable( ObjectData* object );
		
		//! Read the data from the table and put it in the given object.
		/*!
			\param object is a pointer in which the function writes all data from the table.
		*/		
		virtual void readFromTable( ObjectData* object );

		//! Renew the table if some field has changed. 
		void renewTable( );
		
		//! Delete all the fields this class holds.
		void clear();
		

		//! Set the current data object.
		void setObjectData( ObjectData* data );

		//! Set the number of columns in the table.
		void setColumns( int c = defaultColumns );
		
		//! Get the number of columns in the table.
		int getColumns();

		
		void fieldSelected( int fieldIndex );
		
  	typedef sigc::signal<void, int> type_signal_selectionChange;
  	
  	//! This is the signal to indicate a change of the selected field.
  	type_signal_selectionChange get_signal_selectionChange( void );
		
		
	private:
	
		ObjectData* objectData;


		CategoryTreeGTKMM* categoryTree;
		Gtk::Widget* categoryFieldEditWidget;
		Gtk::ScrolledWindow* categoryTreeWindow;
		Gtk::ScrolledWindow* categoryFieldEditWindow;
		
		
		type_signal_selectionChange signal_selectionChange;

		// An vector with all connection objects which this object has generated to receive signals from its children.
		vector<sigc::connection> connections;


		// An vector with all fields in this class
		vector<FieldGTKMM*> fields;

		// Attach options for the table.
		static Gtk::AttachOptions tableAttachX;
		static Gtk::AttachOptions tableAttachY;
		
		static int columns; 
		static int tablePaddingX;
		static int tablePaddingY;	

};



#endif
