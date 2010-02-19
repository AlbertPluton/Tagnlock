//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef CHECKFIELD_H
#define CHECKFIELD_H

#include "Field.h"


//! A child class of Field defining a check field.

class CheckField : public Field
{

	public:

		//! The constructor 
		/*!
			\sa Field::Field()
		*/	
		CheckField( string fieldLabel, bool fieldRequired, bool fieldReset );


		//! A Construct which creates a CheckField from a description.
		/*!
			This constructor is used by Field::newField( vector<string> * description )
			\param description vector containing strings from a category definition file
		*/
		CheckField( vector<string> * description );

	
		//! The destructor	
		~CheckField();
	
	
	
		//! Get function
		/*!
			\return The type of this field: CheckField.
		*/
		string getType();





};


#endif
