//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
//
//


#ifndef SPINFIELDGTKMM_H
#define SPINFIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"
#include "SpinField.h"
#include "FieldGTKMM.h"



class SpinFieldGTKMM : public FieldGTKMM
{

	public:
		
		SpinFieldGTKMM( Field* pField, FieldData* dat = NULL, int i = -1 );
	
		~SpinFieldGTKMM();



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
		
		
		
	private:

		Gtk::SpinButton spinButton;

		// These are to configure the spinbuttons at some maximum and minimum
		static const int defaultMaximum = 1000000;
		static const int defaultMinimum = -1000000;
	

};


#endif

