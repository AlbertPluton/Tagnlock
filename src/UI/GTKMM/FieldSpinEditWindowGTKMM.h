//
//	Author: A.L. Hertog
//	Date: 19 Juni 2009
//	License: GPL
//
//

#ifndef FIELDSPINEDITWINDOWGTKMM_H
#define FIELDSPINEDITWINDOWGTKMM_H



#include "Category.h"
#include "Field.h"
#include "SpinField.h"
#include "FieldEditWindowGTKMM.h"
#include "YesNoToggleButtonGTKMM.h"

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class represents a window in which the properties of a combo field can be edited.

class FieldSpinEditWindowGTKMM : public FieldEditWindowGTKMM
{

	public:
	
		FieldSpinEditWindowGTKMM( Field* pField );
		~FieldSpinEditWindowGTKMM();


	private:
	
		Gtk::Label labelMax, labelMin, labelStepsize, labelAdhereStep, labelDec, labelAdhereDec;
		Gtk::CheckButton checkMax, checkMin;
		Gtk::SpinButton spinMax, spinMin, spinStepsize, spinDec;
		YesNoToggleButtonGTKMM toggleAdhereStep, toggleAdhereDec;
		Gtk::HBox hBoxMax, hBoxMin;

};



#endif
