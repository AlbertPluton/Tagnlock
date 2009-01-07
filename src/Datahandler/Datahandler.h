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
	
	
		//! Add a predefined object to the list after the current position. This functions updates the value of the internal iterator.
		/*!
			All the data in the object is preserved.
		*/
		void addObject( ObjectData* data );
	
	
		//! Create and add a new ObjectData object to the list after the current position. This functions updates the value of the internal iterator.
		/*!
			 This new object has a data structure according to the given category. There is no data in this object, it is empty.
		*/
		void addNewObject( Category* category );

		
		//! Get the first data object in the list. This functions updates the value of the internal iterator.
		ObjectData* getFirstObject();
		//! Get the last data object in the list. This functions updates the value of the internal iterator.
		ObjectData* getLastObject();		
		//! Get the current data object referring to the internal index.
		ObjectData* getCurrentObject();
		//! Get the next data object referring to the internal index. This functions updates the value of the internal iterator.
		ObjectData* getNextObject();
		//! Get the previous data object referring to the internal index. This functions updates the value of the internal iterator.
		ObjectData* getPreviousObject();
		//! Get the data object at a certain position in the list. This functions updates the value of the internal iterator.
		ObjectData* getObjectAt( int index );
		//! Get the size of the list.
		int getListSize();
		//! Returns the current position in the list
		int getPosition();

	
	private:
	
		//! A list with all data of every object which is being categorized. 
		/*!
			This list holds objects from the class ObjectData. This class holds the data of each individual object which is being categorized.
		*/
		list<ObjectData*> objectDataList;
		
		//! An iterator to loop trough the list.
		list<ObjectData*>::iterator it;
		
		//! An integer representation of the list iterator it. Starts from 1.
		int position;
		
		//! Increments the iterator and position. The function also checks that no invalid iterators (greater or smaller than the list) are tried to be made.
		void incrementIT();
		//! Decrements the iterator and position. The function also checks that no invalid iterators (greater or smaller than the list) are tried to be made.
		void decrementIT();
		

};

#endif




