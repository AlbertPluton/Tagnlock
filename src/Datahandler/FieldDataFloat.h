//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	License: GPL
//
//

#ifndef FIELDDATAFLOAT_H
#define FIELDDATAFLOAT_H

#include "FieldData.h"


//! This class is used to implement a float

class FieldDataFloat : public FieldData
{
	public:
	
		FieldDataFloat();
		FieldDataFloat( float value );
		~FieldDataFloat();
		
		//! Derived virutal function from the FieldData class
		void set( float value);
	
		//! Simple get funtion	
		float getFloat();
	
	private:
	
		float data;

};




#endif
