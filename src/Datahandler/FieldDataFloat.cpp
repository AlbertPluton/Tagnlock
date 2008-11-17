//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	License: GPL
//
//

#include "FieldDataFloat.h"


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


