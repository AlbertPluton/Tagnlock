//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
//
//


#ifndef COMBOFIELDGTKMM_H
#define COMBOFIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"
#include "ComboField.h"
#include "FieldGTKMM.h"



class ComboFieldGTKMM : public FieldGTKMM
{

	public:
		
		ComboFieldGTKMM( Field* pField, FieldData* dat = NULL, int i = -1 );
	
		~ComboFieldGTKMM();



		//! Returns a widget edit the properties of the base field.
		Gtk::Widget* getEditWidget();

		//! Updates the properties of the widgets.
		/*!
			This function should be called by the edit widget when the user has alterd some properties of a field.
		*/
		void updateProperties();

		//! Extracts data from the FieldData object specified for this field and displays it in the widget.
		void getData();

		//! Extracts the data which was entered in the widget and stores it in the FieldData object.
		void setData();
		
		Gtk::Widget* getEntry();
		
	private:

		ComboField* comboField;

		Gtk::ComboBoxText* 				comboBoxText;
		Gtk::ComboBoxEntryText* 	comboBoxEntry;
		Gtk::RadioButton*					radioButtons;
		Gtk::VBox*								radioBox;

};

#endif

