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

class FieldGTKMM : Gtk::HBox
{

	public:
		
		FieldGTKMM( Field* field );
		~FieldGTKMM();
	
	
	private:

		Gtk::Label label;
		Gtk::CheckButton required;
		Gtk::CheckButton reset;
		Gtk::Widget* entryField;


};

#endif

