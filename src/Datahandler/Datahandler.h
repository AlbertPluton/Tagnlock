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


//! This class holds all data of the "physical" objects being categorised.
/*!
	Each "physical" object is stored in an object of the class ObjectData. All these objects are added to a list named objectDataList. The iterator it, is used to cycle trough this list.
*/

class Datahandler
{

	public:
	
		//! The default constructor
		Datahandler();

		//! The default destructor
		~Datahandler();
	
	
		void addObject( OjbectData data );
	
	
		//! Create and add a new ObjectData object to the list. This new object has a data structure according to the given category.
		void addNewObject( Category* category );
		
		//! Get the next data object referring to the internal index.
		ObjectData* getNextObject();
		//! Get the previous data object referring to the internal index.
		ObjectData* getPreviousObject();
		//! Get the data object at a certain position in the list.
		ObjectData* getObjectAt( int index );
		//! Get the size of the list.
		int getListSize();
	

	
	private:
	
		//! A list with all data of every object which is being categorized. 
		/*!
			This list holds objects from the class ObjectData. This class holds the data of each individual object which is being categorized.
		*/
		list<ObjectData> objectDataList;
		
		//! An iterator to loop trough the list.
		list<ObjectData>::iterator it;

};

#endif




