//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef SPINFIELDGTKMM_H
#define SPINFIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"
#include "SpinField.h"
#include "FieldGTKMM.h"


//! Class to display a Spin field in GTKMM.
class SpinFieldGTKMM : public FieldGTKMM
{

	public:
		
		SpinFieldGTKMM( Field* pField, FieldData* dat = NULL, int i = -1 );
	
		~SpinFieldGTKMM();



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

		Gtk::SpinButton spinButton;

		// These are to configure the spinbuttons at some maximum and minimum
		static const int defaultMaximum = 1000000;
		static const int defaultMinimum = -1000000;
	

};


#endif

