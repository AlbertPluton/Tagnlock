//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	License: GPL
//
//

#ifndef FIELD_H
#define FIELD_H


#include <vector>
#include <string>

using namespace std;


//! A class which defines the basic information about a categorisation field.

class Field
{

	public:


		//! The default constructor.
		Field();

		//! The constructor with parameters.
		/*!
			\param fieldLabel is a description of the field which is presented to the user via the UI.
			\param fieldRequired indicates if the user is required to fill in this field.
			\param fieldReset indicates whether the contents of this field is deleted when continuing with the next item.
		*/
		Field( string fieldLabel, bool fieldRequired, bool fieldReset );


		//! The destructor
		/*!
		*/
		~Field();

		//! A function to create a new Field object or one of its childeren.
		/*
			\param description data about the field.
			\return a pointer to the new Field object.
		*/
		static Field* newField( vector<string>* description );
		
				
		//! A virtual function to get the type of field.
		/*!	
			\return A string is returned which contains the field type.
		*/
		virtual string getType();



		//! A virtual function to get a full description of the field with all its options.
		/*!
			This function returns information about this field. This can be used to generate a category definition file. 
			\return A pointer to a vector of strings. These strings contain all information of this field: type, label, required, reset and any additional information implemented in the child of this class. 
		*/
		virtual vector<string> getDescription();



		//! A function which returns the field type.
		/*!
			\return A string is returned containing the field type.
		*/
		string getLabel();
				

		
		//! A get function for required.
		/*!
			\return A boolean which indicates whether or not the user is required to fill in this field.
		*/
		bool getRequired();
		
		
		
		//! A get function for reset.
		/*!
			\return A boolean which indicates whether the contents of this field is deleted when continuing with the next item.
		*/
		bool getReset();
		
	
		//! A set function for label.
		void setLabel( string fieldLabel );

		//! A set function for required		.
		void setRequired( bool fieldRequired );
		
		//! A set function for reset.
		void setReset( bool fieldReset );
		
		 
		
	protected:
			
		//! A function to convert strings to booleans.
		bool stringToBool( string input );
		
		//! A function to convert booleans to strings.
		string boolToString( bool input );
		
		
		//! Converts a string to a double.
		double stringToDouble( string input );
		
		
		//! Converts a double to a string.
		string doubleToString( double input );
		
		
	private:
	
		string label;
		bool required;
		bool reset;
	

		


};

#endif


