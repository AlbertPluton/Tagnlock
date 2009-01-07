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
	typeFieldDataInt			= 0,
	typeFieldDataFloat		= 1,
	typeFieldDataDouble		= 2,
	typeFieldDataString		= 3,
	typeFieldDataBool			= 4
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
		virtual int getInt(){ cout << "Not sepose to happen Int\n"; };																						//TODO throw if not the correct data type
		//! This function is implemented in FieldDataFloat
		virtual float getFloat(){ cout << "Not sepose to happen Float\n"; };																			//TODO throw if not the correct data type
		//! This function is implemented in FieldDataDouble
		virtual double getDouble(){ cout << "Not sepose to happen Double\n"; };																	//TODO throw if not the correct data type
		//! This function is implemented in FieldDataString
		virtual string getString(){ cout << "Not sepose to happen String\n"; };																	//TODO throw if not the correct data type
		//! This function is implemented in FieldDataBool
		virtual bool getBool(){ cout << "Not sepose to happen Bool\n"; };																				//TODO throw if not the correct data type
		
		//! This function is implemented in FieldDataInt
		virtual void set( int 		value ){ cout << "Not sepose to happen Int\n"; };															//TODO throw if not the correct data type
		//! This function is implemented in FieldDataFloat
		virtual void set( float		value ){ cout << "Not sepose to happen Float\n"; };														//TODO throw if not the correct data type
		//! This function is implemented in FieldDataDouble
		virtual void set( double	value ){ cout << "Not sepose to happen Double\n"; };														//TODO throw if not the correct data type
		//! This function is implemented in FieldDataString
		virtual void set( string	value ){ cout << "Not sepose to happen String\n"; };														//TODO throw if not the correct data type
		//! This function is implemented in FieldDataBool
		virtual void set( bool		value ){ cout << "Not sepose to happen Bool\n"; };															//TODO throw if not the correct data type
		
		
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
