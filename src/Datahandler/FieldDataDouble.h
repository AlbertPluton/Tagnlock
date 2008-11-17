//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	License: GPL
//
//

#ifndef FIELDDATADOUBLE_H
#define FIELDDATADOUBLE_H

#include "FieldData.h"


//! This class is used to implement a double

class FieldDataDouble : public FieldData
{
	public:
	
		FieldDataDouble();
		FieldDataDouble( double value );
		~FieldDataDouble();
		
		//! Derived virutal function from the FieldData class
		void set( double value);
	
		//! Simple get funtion	
		double getDouble();
	
	private:
	
		double data;

};




#endif
