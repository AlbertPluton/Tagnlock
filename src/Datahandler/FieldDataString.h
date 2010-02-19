//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef FIELDDATASTRING_H
#define FIELDDATASTRING_H

#include "FieldData.h"


//! This class is used to implement a string

class FieldDataString : public FieldData
{
	public:
	
		FieldDataString();
		FieldDataString( string value );
		~FieldDataString();
		
		//! Derived virutal function from the FieldData class
		void set( string value);
	
		//! Simple get funtion	
		string getString();
	
	private:
	
		string data;

};




#endif
