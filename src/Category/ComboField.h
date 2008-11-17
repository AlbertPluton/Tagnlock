//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	License: GPL
//
//



#ifndef COMBOFIELD_H
#define COMBOFIELD_H


#include "Field.h"
#include <vector>

//! This is an enumeration of all possible field combo types.
enum ComboType
{
	Combo,
	ComboEntry,
	ComboRadio
};


//! A child class of Field defining a check field.


class ComboField : public Field
{

	public:

		//! The constructor 
		/*!
			\sa Field::Field()
			\param fieldCobo an array with different combo options.
			\param fieldType defines the different types of field combos: Combo, ComboEntry, ComboRadio.
		*/	
		ComboField( string fieldLabel, bool fieldRequired, bool fieldReset, vector<string> * fieldCombo, ComboType fieldType );


		
		//! A Construct which creates a ComboField from a description.
		/*!
			This constructor is used by Field::newField( vector<string> * description )
			\param description vector containing strings from a category definition file
		*/
		ComboField( vector<string> * description );

			
	
		//! The destructor
		~ComboField();



			
		//! Get function
		/*!
			\return The type of this field: 0 = "ComboField", 1 = "ComboEntryField", 2 = "ComboRadioField".
		*/
		string getType();
		
		
		
		//! A virtual function to get a full description of the field with all its options.
		/*!
			This function returns information about this field. This can be used to generate a category definition file. 
			\return A pointer to a vector of strings. These strings contain all information of this field: type, label, required, reset, the number of combo elements and all combo elements. 
		*/
		vector<string> getDescription();		



		//! Get function for the size of the combo vector.
		/*!
			\return This function returns an integer containing the number of elements in the combo vector.
		*/
		int getComboSize();

	
	
		//! Get function to obtain an element from the combo vector.
		/*!
			\param n is the index number of the desired element starting from 0.
			\return A string is returend containing the contents element n. An empty string, "", is returned when n is out of range. 
		*/
		string getComboElement( int n );
		

	
	private:
	
		//! This variable holds the type of this combo field
		ComboType type;
		
		//! This vector holds all combo options
		vector<string> * combo;

};


#endif










