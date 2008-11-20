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
	it = objectDataList.begin();
	position = 0;
};

//-----------------------------------------------------------------------------

Datahandler::~Datahandler()
{

};

//-----------------------------------------------------------------------------

void Datahandler::addObject( ObjectData* data )
{

		if( (int)objectDataList.size() == 0 ) 			// If the list is empty add to the front.
		{
			objectDataList.push_front( data );
			it = objectDataList.begin();		
			position = 1;	
		}
		else if( it ==  objectDataList.end() ) 			// if it is the last item of the list, use push back
		{
			objectDataList.push_back( data );
			it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
			position = objectDataList.size();
		}
		else 																				// if it is the in the middel of the list, use insert
		{
			it++; 																		// Increment the it because insert puts the new object infront of the previous object
			objectDataList.insert( it, data );
			it--; 																		// Go back to the new data
			position++;
		}

};


//-----------------------------------------------------------------------------

void Datahandler::addNewObject( Category* category )
{
		// TODO throw incase of memory shortage
		ObjectData* data = new ObjectData( category ); 

		
		if( (int)objectDataList.size() == 0 ) 			// If the list is empty add to the front.
		{
			objectDataList.push_front( data );
			it = objectDataList.begin();
			position = 1;			
		}
		else if( it ==  objectDataList.end() ) 			// if it is the last item of the list, use push back
		{
			objectDataList.push_back( data );
			it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
			position = objectDataList.size();
		}
		else 																				// if it is the in the middel of the list, use insert
		{
			it++;																			// Increment the it because insert puts the new object infront of the previous object
			objectDataList.insert( it, data );
			it--; 																		// Go back to the new data
			position++;																// The position should be incremented to the new data.
		}
		
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getFirstObject()
{
	this->it = objectDataList.begin();
	position = 1;
	return *(this->it);
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getLastObject()
{
	this->it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
	position = objectDataList.size();  
	return *(this->it);
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getCurrentObject()
{
	return (*(this->it));	// A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNextObject()
{
	incrementIT();
 	return (*(this->it));	// A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPreviousObject()
{
	decrementIT();
	return (*(this->it)); // A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getObjectAt( int index )
{
	// The number of steps required to reach the new object
	int fromBegin = index-1;
	int fromEnd 	= objectDataList.size() - index;
	int fromPos   = index - position;

	// Find the shortest way to reach the desired position.

	if( (fromBegin <= fromEnd) && (fromBegin*fromBegin <= fromPos*fromPos) ) // Use the square to lose possible minus sign of fromPos
	{
		this->it = objectDataList.begin();
		position = 1;
		for( int i = 0; i < fromBegin; i++ ) incrementIT();	
	}
	else if( fromEnd*fromEnd <= fromPos*fromPos )		// Starting from the end is the shortest way 
	{
		this->it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
		position = objectDataList.size();
		for( int i = 0; i < fromEnd; i++ ) decrementIT();
	}
	else if( fromPos > 0 )	// Go up from the current position
	{
		for( int i = 0; i < fromPos; i++ ) incrementIT();
	}
	else if( fromPos < 0 ) // Go down from the current position
	{
		for( int i = fromPos; i < 0; i++ ) decrementIT();
	}
	
	return  (*this->it); // A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

int Datahandler::getListSize()
{
	return (int)objectDataList.size();
};

//-----------------------------------------------------------------------------

int Datahandler::getPosition()
{
	return position;
};

//-----------------------------------------------------------------------------

void Datahandler::incrementIT()
{
	if( position < objectDataList.size() )	// To prevent invalid data acces
	{
		(this->it)++;
		position++;
	}
};

//-----------------------------------------------------------------------------

void Datahandler::decrementIT()
{
	if( position > 1 )	// To prevent invalid data acces
	{
		(this->it)--;
		position--;
	}
};

//-----------------------------------------------------------------------------






















