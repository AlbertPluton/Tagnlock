//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "FieldDataFloat.h"


//-----------------------------------------------------------------------------

FieldDataFloat::FieldDataFloat(  )
{
	type = typeFieldDataFloat;
	data = 0.0;
};


//-----------------------------------------------------------------------------


FieldDataFloat::FieldDataFloat( int value )
{
	type = typeFieldDataFloat;
	data = (float)value;
};


//-----------------------------------------------------------------------------


FieldDataFloat::FieldDataFloat( float value )
{
	type = typeFieldDataFloat;
	data = value;
};


//-----------------------------------------------------------------------------


FieldDataFloat::~FieldDataFloat()
{

};


//-----------------------------------------------------------------------------

void FieldDataFloat::set( int value )
{
	data = (float)value;
}


//-----------------------------------------------------------------------------

void FieldDataFloat::set( float value )
{
	data = value;
}


//-----------------------------------------------------------------------------

float FieldDataFloat::getFloat()
{
	return data;
}

//-----------------------------------------------------------------------------


