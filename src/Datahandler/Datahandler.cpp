//
//	Author: A.L. Hertog
//	Date: 29 September 2008
//	License: GPL
//
//


#include "Datahandler.h"





//-----------------------------------------------------------------------------

Datahandler::Datahandler()
{

};

//-----------------------------------------------------------------------------

Datahandler::~Datahandler()
{

};

//-----------------------------------------------------------------------------

void Datahandler::addNewObject( ObjectData data )
{
		objectDataList.insert( it, data );
};


//-----------------------------------------------------------------------------

void Datahandler::addNewObject( Category* category )
{
		objectDataList.insert( it, new ObjectData( category ) );
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNextObject()
{
	(this->it)++;
 	return &(*(this->it));	// A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPreviousObject()
{
	(this->it)--;
	return &(*(this->it)); // A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getObjectAt( int index )
{
	list<ObjectData>::iterator iterator = objectDataList.begin();
	for( int i = 0; i <= index; i++ ) iterator++;
	return  &(*iterator); // A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

int Datahandler::getListSize()
{
	return (int)objectDataList.size();
};

//-----------------------------------------------------------------------------




