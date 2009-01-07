//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//


///21

#ifndef OBJECTDATA_H
#define OBJECTDATA_H


#include <vector>
using namespace std;


#include "FieldData.h"
#include "Category.h"

//! This class is used to hold data about a specific catogery.

class ObjectData
{

	public:
	
		//! The constructor
		/*!
			\param categoryPointer it is required to give a pointer to a Category object, this to beable to generate a data structure.
		*/
		ObjectData( Category* categoryPointer );
		
		//! The default destructor
		~ObjectData();	
	
	
		//! Get a pointer to a Category object. This class makes use of this Category to derive its data structure from.
		Category* getCategory();
	
	
		//! Get the number of data fields this object holds.
		int getSize();
		
		
		//! Get a pointer to the data at number index.
		FieldData* getDataAt( int index );
		

		//! Compare the contents of the two ObjecData objects for equality.
		bool operator== ( ObjectData* data );
		
		//! Compare the contents of the two ObjecData objects for inequality.
		bool operator!= ( ObjectData* data );
	
		//! Compare only the type of category the two objects have
		bool compareCategory( ObjectData* data );
	
	
	
	private:
		
		vector<FieldData*> fieldDataVec;
		
		Category* category;

};


#endif
