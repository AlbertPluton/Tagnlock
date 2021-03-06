//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef FIELDDATABOOL_H
#define FIELDDATABOOL_H

#include "FieldData.h"


//! This class is used to implement a boolean

class FieldDataBool : public FieldData
{
	public:
		
		FieldDataBool();
		FieldDataBool( bool value );
		~FieldDataBool();
		
		//! Derived virutal function from the FieldData class
		void set( bool value);
	
		//! Simple get funtion	
		bool getBool();
	
	private:
	
		bool data;

};




#endif
