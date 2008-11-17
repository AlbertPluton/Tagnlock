//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	License: GPL
//
//

#include "FieldDataDouble.h"


FieldDataDouble::FieldDataDouble( double value )
{
	type = typeFieldDataDouble;
	data = value;
};


//-----------------------------------------------------------------------------


FieldDataDouble::~FieldDataDouble()
{

};


//-----------------------------------------------------------------------------

void FieldDataDouble::set( double value )
{
	data = value;
}


//-----------------------------------------------------------------------------

double FieldDataDouble::getDouble()
{
	return data;
}

//-----------------------------------------------------------------------------


