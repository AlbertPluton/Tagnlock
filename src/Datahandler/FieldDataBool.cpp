//
//	Author: A.L. Hertog
//	Date: 10 Nobember 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "FieldDataBool.h"


//-----------------------------------------------------------------------------


FieldDataBool::FieldDataBool()
{
	type = typeFieldDataBool;
	data = false;
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


