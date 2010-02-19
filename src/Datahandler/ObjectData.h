//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef OBJECTDATA_H
#define OBJECTDATA_H


#include <vector>
#include <string>
using namespace std;


#include "FieldData.h"
#include "Category.h"

#include "URIobject.h"

//! This class is used to hold data about a specific catogery.

class ObjectData
{

	public:
	
		//! The constructor
		/*!
			\param categoryPointer it is required to give a pointer to a Category object, this to beable to generate a data structure.
			\param name is an uri object of the file/folder under consideration.
		*/
		ObjectData( Category* categoryPointer, URIobject* name );
		
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
	
	
		//! Returns the file/folder name and or directory of the object under consideration.
		URIobject* getObjectName();
		
		//! Set the name and or directory of the file/folder under consideration.
		void setObjectName( URIobject* name );
	
	
	private:
		
		vector<FieldData*> fieldDataVec;
		
		Category* category;
		URIobject* objectName;

};


#endif
