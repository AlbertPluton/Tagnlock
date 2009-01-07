//
//	Author: A.L. Hertog
//	Date: 6 Nobember 2008
//	License: GPL
//
//


#include "FieldData.h"


#include "FieldDataInt.h"
#include "FieldDataFloat.h"
#include "FieldDataDouble.h"
#include "FieldDataString.h"
#include "FieldDataBool.h"


FieldData::FieldData()
{

};


//-----------------------------------------------------------------------------


FieldData::~FieldData()
{

};


//-----------------------------------------------------------------------------

FieldData* FieldData::newFieldData( int 		value )
{
	return new FieldDataInt(value);
};


//-----------------------------------------------------------------------------

FieldData* FieldData::newFieldData( float 	value )
{
	return new FieldDataFloat(value);
};


//-----------------------------------------------------------------------------

FieldData* FieldData::newFieldData( double value )
{
	return new FieldDataDouble(value);
};


//-----------------------------------------------------------------------------

FieldData* FieldData::newFieldData( string value )
{
	return new FieldDataString(value);
};


//-----------------------------------------------------------------------------

FieldData* FieldData::newFieldData( bool 	value )
{
	return new FieldDataBool(value);
};


//-----------------------------------------------------------------------------

FieldDataType FieldData::getType()
{
	return type;
};


//-----------------------------------------------------------------------------
	
bool FieldData::operator== ( FieldData* data )
{
	// Check if the type is the same
	if( this->getType() == data->getType() )
	{
		// Compare the values
		switch( this->getType() )
		{
			case 0:		// typeFieldDataInt
				if( this->getInt() == data->getInt() ) return true;
				break;
				
			case 1:		// typeFieldDataFloat
				if( this->getFloat() == data->getFloat() ) return true;			
				break;
				
			case 2:		// typeFieldDataDouble
				if( this->getDouble() == data->getDouble() ) return true;		
				break;
				
			case 3:		// typeFieldDataString
				if( this->getString().compare( data->getString() ) == 0 ) return true;
				break;
				
			case 4:		// typeFieldDataBool
				if( this->getBool() == data->getBool() ) return true;	
				break;	
		}
	}
	
	return false;
}


//-----------------------------------------------------------------------------

bool FieldData::operator!= ( FieldData* data )
{
	// Check if the type is the same
	if( this->getType() == data->getType() )
	{
		// Compare the values
		switch( this->getType() )
		{
			case 0:		// typeFieldDataInt
				if( this->getInt() == data->getInt() ) return false;
				break;
				
			case 1:		// typeFieldDataFloat
				if( this->getFloat() == data->getFloat() ) return false;			
				break;
				
			case 2:		// typeFieldDataDouble
				if( this->getDouble() == data->getDouble() ) return false;		
				break;
				
			case 3:		// typeFieldDataString
				if( this->getString().compare( data->getString() ) == 0 ) return false;
				break;
				
			case 4:		// typeFieldDataBool
				if( this->getBool() == data->getBool() ) return false;	
				break;	
		}
	}
	
	return true;
}


//-----------------------------------------------------------------------------



