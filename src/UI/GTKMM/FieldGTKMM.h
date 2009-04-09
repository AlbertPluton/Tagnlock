//
//	Author: A.L. Hertog
//	Date: 30 January 2009
//	License: GPL
//
//

#ifndef FIELDGTKMM_H
#define FIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"

//! This class holds pointer to the GTKMM opjects for a field.

class FieldGTKMM : Gtk::HBox
{

	public:
		
		//! The default constructor requires a pointer to a Field object to beable to determine what kind of entry field should be created.
		FieldGTKMM( Field* field );
		
		//! The default destructor.
		~FieldGTKMM();

		//! Returns a pointer to the label widget.
		Gtk::Widget* getLabel();
		//! Returns a pointer to the required check button widget.
		Gtk::Widget* getRequired();
		//! Returns a pointer to the reset check button widget.		
		Gtk::Widget* getReset();
		//! Returns a pointer to the entry field widget.
		Gtk::Widget* getEntryField();
	
	
	private:

		Gtk::Widget* label; 		//Gtk::Label label;
		Gtk::Widget* required; 	// Gtk::CheckButton required;
		Gtk::Widget* reset;			//Gtk::CheckButton reset;
		Gtk::Widget* entryField;


};

#endif

