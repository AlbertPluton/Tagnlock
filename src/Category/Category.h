//
//	Author: A.L. Hertog
//	Date: 27 August 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//




#ifndef CATEGORY_H
#define CATEGORY_H


#include "Field.h"
#include "TextField.h"
#include "CheckField.h"
#include "ComboField.h"
#include "SpinField.h"

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
		
		//! Save the current category to a definition file. Uses the file name specified in this class and overwrites any excisting files with this name.
		void saveCategory( );
	
		
		
		//! Return the size of the fields vector
		int getFieldsSize();
		
		//! Return a pointer to the field at index.
		Field* getFieldAt( int index );
		
		//! Move the field at index i to index i+1. It swaps place with the field at index i+1, which goes to index i.
		void increaseFieldIndex( int i );
		
		//! Move the field at index i to index i-1. It swaps place with the field at index i-1, which goes to index i.
		void decreaseFieldIndex( int i );
		
		//! Deletes the specified field from the category.
		void deleteField( int i );
		
		//! Deletes the specified field from the categogry.
		void deleteField( Field* field );
		
		//! Returns the index of the specified field. Will return -1 if the field is not found.
		int getIndex( Field* field );
		
		
		
		//! Return the type of a specific field
		/*!
			\param index The index number of the desired field.
			\return The type of field in string form.
		*/
		string getFieldTypeAt( int index );
		
		
		//! Return a vector holding the types of all fields.
		/*!
			\return A vector of strings is returned. Each holding the type of the corresponding (the same index) field in string form.
		*/
		vector<string> getFieldTypeVector();
		
		
		//! Returns the name of the category.
		string getName();
		
		//! Changes the name of the category.
		void setName( string categoryName );
		
	
		//! Set the file name.
		void setFileName( string name );
		
		//! Get the file name. Returns "" if non is set.
		string getFileName();
		
	private:

		//! This is a vector of pointer to Field ojects.
		vector<Field*> fields;

		//! The name of the category. This name is used to identify the category
		string name;
		
		//! The name of the file in which this category is saved.
		string fileName;
};

#endif
