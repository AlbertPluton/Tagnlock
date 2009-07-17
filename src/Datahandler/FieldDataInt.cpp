//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	License: GPL
//
//


#include "FieldDataInt.h"


//-----------------------------------------------------------------------------

FieldDataInt::FieldDataInt( )
{
	type = typeFieldDataInt;
	data = 0;
};


//-----------------------------------------------------------------------------


FieldDataInt::FieldDataInt( int value)
{
	type = typeFieldDataInt;
	data = value;
};


//-----------------------------------------------------------------------------


FieldDataInt::~FieldDataInt()
{

};


//-----------------------------------------------------------------------------

void FieldDataInt::set( int value )
{
	data = value;
}


//-----------------------------------------------------------------------------

int FieldDataInt::getInt()
{
	return data;
}

//-----------------------------------------------------------------------------


