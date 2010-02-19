//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "FieldDataString.h"


//-----------------------------------------------------------------------------


FieldDataString::FieldDataString( )
{
	type = typeFieldDataString;
	data = "";
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


