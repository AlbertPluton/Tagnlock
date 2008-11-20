//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	License: GPL
//
//

#include "FieldDataBool.h"


//-----------------------------------------------------------------------------


FieldDataBool::FieldDataBool()
{
	type = typeFieldDataBool;
};


//-----------------------------------------------------------------------------


FieldDataBool::FieldDataBool( bool value)
{
	type = typeFieldDataBool;
	data = value;
};


//-----------------------------------------------------------------------------


FieldDataBool::~FieldDataBool()
{

};


//-----------------------------------------------------------------------------

void FieldDataBool::set( bool value )
{
	data = value;
}


//-----------------------------------------------------------------------------

bool FieldDataBool::getBool()
{
	return data;
}

//-----------------------------------------------------------------------------


