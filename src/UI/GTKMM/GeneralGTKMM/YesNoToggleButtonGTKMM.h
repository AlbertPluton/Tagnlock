//
//	Author: A.L. Hertog
//	Date: 18 june 2009
//	License: GPL
//
//

#ifndef YESNOTOGGLEBUTTONGTKMM_H
#define YESNOTOGGLEBUTTONGTKMM_H


#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class is a modification of the standart toggle button.
/*!
	The label of this button changes from No to Yes when the button is cliced.
*/

class YesNoToggleButtonGTKMM : public Gtk::ToggleButton
{

	public:
	
		YesNoToggleButtonGTKMM();
		~YesNoToggleButtonGTKMM();	
	
	private:
	
		void switchLabel();



};

#endif

