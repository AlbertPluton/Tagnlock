//
//	Author: A.L. Hertog
//	Date: 19 Juni 2009
//	License: GPL
//
//

#ifndef FIELDCOMBOEDITWIDGETGTKMM_H
#define FIELDCOMBOEDITWIDGETGTKMM_H



#include "Category.h"
#include "Field.h"
#include "FieldEditWidgetGTKMM.h"

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class represents a window in which the properties of a combo field can be edited.

class FieldComboEditWidgetGTKMM : public FieldEditWidgetGTKMM
{
	public:
		FieldComboEditWidgetGTKMM( Field* pField, int i );
		~FieldComboEditWidgetGTKMM();
		
	private:
	
};



#endif
