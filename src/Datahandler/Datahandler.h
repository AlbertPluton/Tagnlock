//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//

#ifndef DATAHANDLER_H
#define DATAHANDLER_H


#include <iostream>
#include <vector>
#include <list>

#include "Category.h"

#include "ObjectData.h"


using namespace std;



public class Datahandler
{

	public:
	
		Datahandler( );

		~Datahandler();
	
	
		void addObject( Category* category );
		ObjectData* getNextObject();
		ObjectData* getPreviousObject();
		ObjectData* getObjectAt( int index );
		int getListSize();
	

	
	private:
	
		list<ObjectData> objectDataList;


};

#endif




