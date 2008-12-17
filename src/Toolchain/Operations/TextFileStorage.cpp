//
//	Author: A.L. Hertog
//	Date: 17 December 2008
//	License: GPL
//
//

#include "TextFileStorage.h"

#include <sstream>

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
	
	this->setInput( this->getParentNode()->getOutput() );
	
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


void TextFileStorage::saveToSingleFile()
{

	string str = this->getLocation() + this->getFileName();

	ofstream file( str.c_str() );
  
  // Get the initial position of the internal iterator of the Datahandler.
  int pos = getInput()->getPosition();
  

  
  if( file.is_open() )
  {
    // Get the first data object.
  	ObjectData* objectData = getInput()->getFirstObject();  
    
    // Declare actual field data object.
    FieldData* data; 

		// Loop through all objectData elements in the Datahandler.
    for( int i = 0; i < (int)getInput()->getListSize(); i++ )
    {
			
			// Loop through all fieldData elements in an objectData object.
			for( int j = 0; j < objectData->getSize(); j++ )
			{
				data = objectData->getDataAt(j);
				
				// Start with a new line;
				cout << endl;
				
				switch( data->getType() )
				{
					case typeFieldDataInt:
						cout << data->getInt() << endl;
					break;
					
					case typeFieldDataFloat:
						cout << data->getFloat() << endl;
					break;
					
					case typeFieldDataDouble:
						cout << data->getDouble() << endl;
					break;
					
					case typeFieldDataString:
						cout << data->getString() << endl;
					break;
					
					case typeFieldDataBool:
						if( data->getBool() )
						{
							cout << "true" << endl;
						}
						else
						{
							cout << "false" << endl;
						}
					break;				
				}		
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

void TextFileStorage::saveToIndividualFile()
{

	string str;
	ofstream file;
	stringstream integerConvertor;

  // Declare actual field data object.
  FieldData* data; 

  // Get the initial position of the internal iterator of the Datahandler.
  int pos = getInput()->getPosition();

  // Get the first data object.
 	ObjectData* objectData= getInput()->getFirstObject();


	// Loop over all elements in the datahandler
	for( int i = 0; i < (int)getInput()->getListSize(); i++ )
	{

		// Create the file name.
		integerConvertor << i;
		str = this->getLocation() + this->getFileName() + integerConvertor.str();

		// Open the file;
		file.open( str.c_str() );
		
		if( file.is_open() )
		{
			
			// Loop through all fieldData elements in an objectData object.
			for( int j = 0; j < objectData->getSize(); j++ )
			{
				data = objectData->getDataAt(j);
				
				switch( data->getType() )
				{
					case typeFieldDataInt:
						cout << data->getInt() << endl;
					break;
					
					case typeFieldDataFloat:
						cout << data->getFloat() << endl;
					break;
					
					case typeFieldDataDouble:
						cout << data->getDouble() << endl;
					break;
					
					case typeFieldDataString:
						cout << data->getString() << endl;
					break;
					
					case typeFieldDataBool:
						if( data->getBool() )
						{
							cout << "true" << endl;
						}
						else
						{
							cout << "false" << endl;
						}
					break;				
				}		
			}			
			
			file.close();
		}
		else
		{
			//TODO throw
		}		
		
		
		// Get the next data object.
		objectData = getInput()->getNextObject(); 
		
	}

  // Resore the initial position of the internal Datahandler iterator. This is not as it is seposed to be. TODO alter the datahandler internal iterator.
  getInput()->getObjectAt( pos );

};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


