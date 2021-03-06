//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "FieldDataDouble.h"


//-----------------------------------------------------------------------------

FieldDataDouble::FieldDataDouble( )
{
	type = typeFieldDataDouble;
	data = 0.0;
};


//-----------------------------------------------------------------------------


FieldDataDouble::FieldDataDouble( int value )
{
	type = typeFieldDataDouble;
	data = (double)value;
};


//-----------------------------------------------------------------------------


FieldDataDouble::FieldDataDouble( float value )
{
	type = typeFieldDataDouble;
	data = (double)value;
};


//-----------------------------------------------------------------------------


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


void FieldDataDouble::set( int value )
{
	data = (double)value;
}


//-----------------------------------------------------------------------------


void FieldDataDouble::set( float value )
{
	data = (double)value;
}


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


