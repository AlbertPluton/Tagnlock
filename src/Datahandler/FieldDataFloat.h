//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef FIELDDATAFLOAT_H
#define FIELDDATAFLOAT_H

#include "FieldData.h"


//! This class is used to implement a float

class FieldDataFloat : public FieldData
{
	public:
		
		//! Default constructor.
		FieldDataFloat();
		//! Constructor with the data value as a parameter, it converts integers to floats.
		FieldDataFloat( int value );		
		//! Constructor with the data value as a parameter.
		FieldDataFloat( float value );
		~FieldDataFloat();
		
		//! Derived virutal function from the FieldData class, it converts integers to floats. 
		void set( int value);

		//! Derived virutal function from the FieldData class.
		void set( float value);
	
		//! Simple get funtion	
		float getFloat();
	
	private:
	
		float data;

};




#endif
