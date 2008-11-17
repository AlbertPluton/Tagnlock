//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	License: GPL
//
//

#ifndef FIELDDATAINT_H
#define FIELDDATAINT_H

#include "FieldData.h"


//! This class is used to implement a integer

class FieldDataInt : public FieldData
{
	public:
	
		FieldDataInt();
		FieldDataInt( int value );
		~FieldDataInt();
		
		//! Derived virutal function from the FieldData class
		void set( int value);
	
		//! Simple get funtion
		int getInt();
	
	private:
	
		int data;

};




#endif
