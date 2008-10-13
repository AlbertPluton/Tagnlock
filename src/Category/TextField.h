//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	License: GPL
//
//

#include "Field.h"

//! A child class of Field defining a text field.

class TextField : public Field
{

	public:
	
		//! The constructor 
		/*!
			\sa Field::Field()
		*/
		TextField( string fieldLabel, bool fieldRequired, bool fieldReset );

		
		//! A Construct which creates a TextField from a description.
		/*!
			This constructor is used by Field::newField( vector<string> * description )
			\param description vector containing strings from a category definition file
		*/
		TextField( vector<string> * description );
		

		//! The destructor
		~TextField();



		//! Get function, the implementation of the virtual function in the Field class. 
		/*!
			\sa Field::getType()
			\return The type of this field: TextField.
		*/
		string getType();






};
