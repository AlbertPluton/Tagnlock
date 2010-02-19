//
//	Author: A.L. Hertog
//	Date: 28 October 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//



#ifndef DIALOGFIELDCHOOSERGTKMM_H
#define DIALOGFIELDCHOOSERGTKMM_H



#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "Field.h"
#include "Category.h"

#include <iostream>
#include <string>
using namespace std;





//! This class represents a dialog used to choose the type of field be added to the category.

class DialogFieldChooserGTKMM : public Gtk::Dialog
{

	public:
		
		//! The default constructor
		DialogFieldChooserGTKMM( Gtk::Window* parent );
		
		//! The default destructor
		~DialogFieldChooserGTKMM();
		

		//! Function which will display the dialog and add the chosen field to the category
		bool chooseField( Category* cat );

	private:

		//! Radiobuttons representing teh choises
		Gtk::RadioButton	radioTextField;
		Gtk::RadioButton	radioSpinField;
		Gtk::RadioButton	radioCheckField;
		Gtk::RadioButton	radioComboField;
		Gtk::RadioButton	radioComboEntryField;
		Gtk::RadioButton	radioComboRadioField;

};


#endif



