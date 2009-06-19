//
//	Author: A.L. Hertog
//	Date: 19 Juni 2009
//	License: GPL
//
//

#ifndef FIELDCOMBOEDITWINDOWGTKMM_H
#define FIELDCOMBOEDITWINDOWGTKMM_H



#include "Category.h"
#include "Field.h"
#include "FieldEditWindowGTKMM.h"

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class represents a window in which the properties of a combo field can be edited.

class FieldComboEditWindowGTKMM : public FieldEditWindowGTKMM
{
	public:
		FieldComboEditWindowGTKMM( Field* pField );
		~FieldComboEditWindowGTKMM();
		
	private:
	
};



#endif
