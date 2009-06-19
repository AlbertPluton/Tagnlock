//
//	Author: A.L. Hertog
//	Date: 13 May 2009
//	License: GPL
//
//

#ifndef FIELDEDITWINDOWGTKMM_H
#define FIELDEDITWINDOWGTKMM_H



#include "Category.h"
#include "Field.h"
#include "YesNoToggleButtonGTKMM.h"


#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class represents a window in which field properties can be edited.
/*!
		The class is derived from Gtk::Table to house the different widgets representing the properties of the field. 
*/

class FieldEditWindowGTKMM : public Gtk::Table
{

	public:
		
		FieldEditWindowGTKMM( Field* pField );
		~FieldEditWindowGTKMM();
		
		static FieldEditWindowGTKMM* newEditWindow( Field* pField );
		
		
	private:

		Gtk::Label typeLabel, labelLabel, requiredLabel, resetLabel;
		
		Gtk::Label type;
		Gtk::Entry label;
		YesNoToggleButtonGTKMM required;
		YesNoToggleButtonGTKMM reset;

	protected:
	
		Gtk::AttachOptions attachX;
		Gtk::AttachOptions attachY;

		int rows, columns;

		// Pointer to the field this widget was generated for.
		Field* baseField;

};






#endif










