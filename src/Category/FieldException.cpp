//
//	Author: A.L. Hertog
//	Date: 15 September 2008
//	License: GPL
//
//

#include "FieldException.h"

#include <iostream>


//-----------------------------------------------------------------------------

const string FieldException::errorString [] = { 	"Type undefined",																// 0
																									"Unknown item",														  		// 1
																									"Unknown combo type",														// 2
																									"Not a valid combo object",											// 3
																									"Invalid conversion from string to boolean",		// 4
																									"Size of combo field is invalid"  };						// 5


//-----------------------------------------------------------------------------
	
FieldException::FieldException( int errorNumber )
{
	error = errorNumber;
	fieldType = "UNKNOWN";
	fieldLabel = "UNKNOWN";
};



//-----------------------------------------------------------------------------

FieldException::FieldException( int errorNumber, string type, string label )
{
	error = errorNumber;
	fieldType = type;
	fieldLabel = label;
};




//-----------------------------------------------------------------------------


FieldException::FieldException( int errorNumber, string type, string label, string info )
{
	error = errorNumber;
	fieldType = type;
	fieldLabel = label;
	infoString = info;
};



//-----------------------------------------------------------------------------

FieldException::FieldException( const FieldException& fieldEx )
{
	error = fieldEx.error;
	fieldType = fieldEx.fieldType;
	fieldLabel = fieldEx.fieldLabel;
	infoString = fieldEx.infoString;
}



//-----------------------------------------------------------------------------

FieldException::~FieldException() throw()
{
	//cout << "Destroy fieldException\n";
};



//-----------------------------------------------------------------------------

void FieldException::setFieldType( string type )
{
	fieldType = type;
}



//-----------------------------------------------------------------------------

void FieldException::setFieldLabel( string label )
{
	fieldLabel = label;
}



//-----------------------------------------------------------------------------

string FieldException::getFieldType()
{
	return fieldType;
}


//-----------------------------------------------------------------------------


string FieldException::getFieldLabel()
{
	return fieldLabel;
}



//-----------------------------------------------------------------------------

string FieldException::getErrorString()
{
	return errorString[error];
}



//-----------------------------------------------------------------------------

string FieldException::getInfoString()
{
	return infoString;
}


//-----------------------------------------------------------------------------

int FieldException::getError()
{
	return error;
}



//-----------------------------------------------------------------------------

void FieldException::addInfo( const string& info )
{
	infoString += info;
}

//-----------------------------------------------------------------------------


const char* FieldException::what() const throw()
{
	string tmp = "Field exception: " + errorString[error] + " in field with label: " + fieldLabel + ", of type: " + fieldType + ".\n" + infoString;	
	return tmp.c_str();
}























