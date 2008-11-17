//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//

#ifndef FIELDDATA_H
#define FIELDDATA_H


//! An enumeration of the possible types (the different sub classes).
enum FieldDataType
{
	typeFieldDataInt,
	typeFieldDataFloat,
	typeFieldDataDouble,
	typeFieldDataString,
	typeFieldDataBool
};


#include <iostream>
using namespace std;


//! This class is used as a front end to the standard data types.
/*!
	By using this class it is possible to place different data types in the same list. 
*/ 

class FieldData
{


	public:

		//! The default constructor
		FieldData();
		
		//! The default destructor
		~FieldData();
		
		//! This function creates a new FieldDataInt object
		FieldData* newFieldData( int 		value );
		//! This function creates a new FieldDataFloat object
		FieldData* newFieldData( float 	value );
		//! This function creates a new FieldDataDouble object
		FieldData* newFieldData( double value );
		//! This function creates a new FieldDataString object
		FieldData* newFieldData( string value );
		//! This function creates a new FieldDataBool object
		FieldData* newFieldData( bool 	value );

		//! This function is implemented in FieldDataInt
		virtual int getInt();
		//! This function is implemented in FieldDataFloat
		virtual float getFloat();
		//! This function is implemented in FieldDataDouble
		virtual double getDouble();
		//! This function is implemented in FieldDataString
		virtual string getString();
		//! This function is implemented in FieldDataBool
		virtual bool getBool();
		
		//! This function is implemented in FieldDataInt
		virtual void set( int 		value );
		//! This function is implemented in FieldDataFloat
		virtual void set( float		value );
		//! This function is implemented in FieldDataDouble
		virtual void set( double	value );
		//! This function is implemented in FieldDataString
		virtual void set( string	value );
		//! This function is implemented in FieldDataBool
		virtual void set( bool		value );
		
		
		//! Returns the type of subclass is used to store the data.
		FieldDataType getType();
		
		
		//! Compare the value of two FieldData objects for equality
		bool operator== ( FieldData* data );
		
		//! Compare the value of two FieldData objects for inequality
		bool operator!= ( FieldData* data );


	protected:

		FieldDataType type;


	private:

		

};




#endif
