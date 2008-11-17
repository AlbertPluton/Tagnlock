//
//	Author: A.L. Hertog
//	Date: 10 November 2008
//	License: GPL
//
//

#include "ObjectData.h"

#include "FieldDataInt.h"
#include "FieldDataFloat.h"
#include "FieldDataDouble.h"
#include "FieldDataString.h"
#include "FieldDataBool.h"

#include <vector>
using namespace std;


//-----------------------------------------------------------------------------

ObjectData::ObjectData( Category* categoryPointer )
{
	category = categoryPointer;
	
	// Get a vector with all field types in this Category.
	vector<string> typeVector = category->getFieldTypeVector();
	
	// Reserve space for all data.
	fieldDataVec.resize((int)typeVector.size());
	
	// Iterate over all field types and create compatible FieldData objects.
	for( int i = 0; i < (int)typeVector.size(); i++ )
	{
		if( typeVector.at(i).compare("CheckField") == 0 )
		{
			fieldDataVec.at(i) = new FieldDataBool();
		}
		if( typeVector.at(i).compare("TextField") == 0 )
		{
			fieldDataVec.at(i) = new FieldDataString();
		}
		if( typeVector.at(i).compare("Combo") == 0 )
		{
			fieldDataVec.at(i) = new FieldDataString();
		}
		if( typeVector.at(i).compare("SpinField") == 0 )
		{
			fieldDataVec.at(i) = new FieldDataDouble();
		}
	}
	
};

//-----------------------------------------------------------------------------

ObjectData::~ObjectData()
{

};	

//-----------------------------------------------------------------------------

Category* ObjectData::getCategory()
{
	return category;
};

//-----------------------------------------------------------------------------

int ObjectData::getSize()
{
	return (int)fieldDataVec.size();
};

//-----------------------------------------------------------------------------

FieldData* ObjectData::getDataAt( int index )
{
	return fieldDataVec.at(index);
};

//-----------------------------------------------------------------------------

bool ObjectData::operator== ( ObjectData* data )
{
	// See if both object belong to the same category to beable to check there equality.
	if( this->compareCategory( data ) )
	{
		// Loop trough all fields
		for( int i = 0; i < this->getSize(); i++)
		{	
			// If one of the values is different return false.
			if( this->getDataAt(i) != data->getDataAt(i) ) return false;		// TODO Check if it compares the data values not the pointer values.
		}	
		// All of the values are the same.
		return true;
	}
	return false;
};

//-----------------------------------------------------------------------------

bool ObjectData::operator!= ( ObjectData* data )
{
	// See if both object belong to the same category to beable to check there equality.
	if( this->compareCategory( data ) )
	{
		// Loop trough all fields
		for( int i = 0; i < this->getSize(); i++)
		{	
			// If one of the values is different return false.
			if( this->getDataAt(i) != data->getDataAt(i) ) return true;		// TODO Check if it compares the data values not the pointer values.
		}	
		// All of the values are the same.
		return false;
	}
	return true;
};

//-----------------------------------------------------------------------------

bool ObjectData::compareCategory( ObjectData* data )
{

	// TODO Check and if necessary throw an exception if one or both names do not have a valid value. In other words the name of the category equals "".
	
	// Compare the names of the Categories the two ObjecData objects belong to.
	if( ((this->category)->getName()).compare( (data->category)->getName() ) ==  0)
	{
		return true;
	}
	else
	{
		return false;
	}
};


//-----------------------------------------------------------------------------



