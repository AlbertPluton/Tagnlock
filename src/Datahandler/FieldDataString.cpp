//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	License: GPL
//
//

#include "FieldDataString.h"


//-----------------------------------------------------------------------------


FieldDataString::FieldDataString( )
{
	type = typeFieldDataString;
};


//-----------------------------------------------------------------------------


FieldDataString::FieldDataString( string value)
{
	type = typeFieldDataString;
	data = value;
};


//-----------------------------------------------------------------------------


FieldDataString::~FieldDataString()
{

};


//-----------------------------------------------------------------------------

void FieldDataString::set( string value )
{
	data = value;
}


//-----------------------------------------------------------------------------

string FieldDataString::getString()
{
	return data;
}

//-----------------------------------------------------------------------------


