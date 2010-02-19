//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef TEXTFIELDGTKMM_H
#define TEXTFIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"
#include "TextField.h"
#include "FieldGTKMM.h"



//! Class to display a Text field in GTKMM.
class TextFieldGTKMM : public FieldGTKMM
{

	public:
		
		TextFieldGTKMM( Field* pField, FieldData* dat = NULL, int i = -1 );
	
		~TextFieldGTKMM();



		//! Updates the properties of the widgets.
		/*!
			This function should be called by the edit widget when the user has alterd some properties of a field.
		*/
		void updateProperties();

		//! Extracts data from the FieldData object specified for this field and displays it in the widget.
		void setData();

		//! Extracts the data which was entered in the widget and stores it in the FieldData object.
		void getData();
		
		Gtk::Widget* getEntry();
		
		//! Returns the edit widget.
		Gtk::Widget* getEditWidget();

		
	private:

		Gtk::Entry textEntry;

};

#endif

