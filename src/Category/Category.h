//
//	Author: A.L. Hertog
//	Date: 27 August 2008
//	License: GPL
//
//


#include "Field.h"
#include "TextField.h"
#include "CheckField.h"
#include "ComboField.h"

//! A class defining a catagory.

class Category
{

	public:
	
		//! The constructor
		Category();
		
		//! The destructor
		~Category();
	

	
			//! Adds a new field to the back of the fields vector.
		/*!
			\param newField pointer a new field.
			\sa Category::addFieldAt
		*/
		void addField( Field * newField );


		//! Adds a new field to the back of the fields vector.
		/*!
			\param newField pointer to a new field.
			\param possition index for the new field.
			\sa Category::addFieldAt
		*/		
		void addFieldAt( Field * newField, int possition );
		
		
		//! Load a definition from a file
		/*!
			\param fileName the path and name the definition file. 
		*/
		void loadCategory( string fileName );
	
	
		//! Save the current category to a definition file
		/*!
			\param fileName the path and name the definition file. 
			\param overwrite defines whether if the file alread exists it is overwritten. 
		*/	
		void saveCategory( string fileName, bool overwrite );
		
		
		//! Return the size of the fields vector
		int getFieldsSize();
		
		
		//! Return the type of a specific field
		/*!
			\param The index number of the desired field.
			\return The type of field in string form.
		*/
		string getFieldTypeAt( int index );
		
		
		//! Return a vector holding the types of all fields.
		/*!
			/return A vector of strings is returned. Each holding the type of the corresponding (the same index) field in string form.
		*/
		vector<string> getFieldTypeVector();
		
		
	
	private:

		//! This is a vector of pointer to Field ojects.
		vector<Field*> fields;

};