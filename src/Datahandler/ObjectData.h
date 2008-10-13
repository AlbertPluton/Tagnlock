//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//

#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <vector>

using namespace std;

#include "FieldData.h"


class ObjectData
{

	public:
	
		ObjectData( Category* categoryPointer );
		~ObjectData();	
	
	private:
		
		vector<FieldData*> fieldDataVec;

};


#endif
