//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	License: GPL
//
//


#include "FieldDataDouble.h"


//-----------------------------------------------------------------------------

FieldDataDouble::FieldDataDouble( )
{
	type = typeFieldDataDouble;
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


