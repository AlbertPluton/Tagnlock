//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef FIELDDATADOUBLE_H
#define FIELDDATADOUBLE_H

#include "FieldData.h"


//! This class is used to implement a double

class FieldDataDouble : public FieldData
{
	public:
	
		//! The default constructor
		FieldDataDouble();
		//! Constructor which converts integers to doubles
		FieldDataDouble( int value );
		//! Constructor which converts floats to doubles
		FieldDataDouble( float value );
		//! Constructor with parameter
		FieldDataDouble( double value );
		~FieldDataDouble();

		//! Derived virutal function from the FieldData class, converts integers to doubles.
		void set( int value);

		//! Derived virutal function from the FieldData class, converts floats to doubles.
		void set( float value);
		
		//! Derived virutal function from the FieldData class.
		void set( double value);
	
		//! Simple get funtion	
		double getDouble();
	
	private:
	
		double data;

};




#endif
