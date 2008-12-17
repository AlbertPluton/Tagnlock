//
//	Author: A.L. Hertog
//	Date: 17 December 2008
//	License: GPL
//
//

#include "TextFileStorage.h"



//-----------------------------------------------------------------------------

TextFileStorage::TextFileStorage( ToolchainNode* parent ) : ToolchainOperation<Datahandler*, string>( parent )
{

};

//-----------------------------------------------------------------------------

TextFileStorage::TextFileStorage( ToolchainNode* parent, string loc, string name, bool individual ) : ToolchainOperation<Datahandler*, string>( parent )
{
	location = loc;
	fileName = name;
	individualFiles = individual;
};

//-----------------------------------------------------------------------------

TextFileStorage::~TextFileStorage()
{

};

//-----------------------------------------------------------------------------

void TextFileStorage::execute()
{

	if( individualFiles )
	{
		saveToIndividualFile();
	}
	else
	{
		saveToSingleFile();
	}	
	
};

//-----------------------------------------------------------------------------

void TextFileStorage::setLocation( string loc )
{
		location = loc;
};

//-----------------------------------------------------------------------------

void TextFileStorage::setFileName( string name )
{
	fileName = name;
};

//-----------------------------------------------------------------------------

void TextFileStorage::SetIndividualFiles( bool ind )
{
	individualFiles = ind;
};

//-----------------------------------------------------------------------------

string TextFileStorage::getLocation( )
{
	return location;
};

//-----------------------------------------------------------------------------

string TextFileStorage::getFileName( )
{
	return fileName;
};

//-----------------------------------------------------------------------------

bool TextFileStorage::getIndividualFiles( )
{
	return individualFiles;
};

//-----------------------------------------------------------------------------


void saveToSingleFile()
{
	ofstream file ( getLocation() + getFileName() );
  
  // Get the initial position of the internal iterator of the Datahandler.
  int pos = getInput()->getPosition();
  

  
  if (file.is_open())
  {
    // Get the first data object
  	ObjectData* objectData = getInput()->getFirstObject();  
    
    // Declare actual field data object.
    FieldData* data; 

    for( int i = 0; i < getInput()->getListSize(); i++ )
    {
			
			for( int j = 0; j < objectData->getSize(); j++ )
			{
				data = objectData->getDataAt(j);
				
			}
		
			// Get the next data object.
			objectData = getInput()->getNextObject();    	
    }
    

	  // Resore the initial position of the internal Datahandler iterator. This is not as it is seposed to be. TODO alter the datahandler internal iterator.
	  getInput()->getObjectAt( pos );
    
    // Close the file.
    file.close();

  }
  else
	{
		//TODO throw
	}




};


//-----------------------------------------------------------------------------

void saveToIndividualFile()
{

};

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------


