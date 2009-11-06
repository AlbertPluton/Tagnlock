//
//	Author: A.L. Hertog
//	Date: 17 December 2008
//	License: GPL
//
//

#include "TextFileStorage.h"

#include "Datahandler.h"
#include <sstream>

//-----------------------------------------------------------------------------

TextFileStorage::TextFileStorage( ToolchainNode* parent ) : ToolchainOperation<Datahandler*, string>( parent )
{
	
	// Set the input to a default value.
	this->setInput( NULL );

	// Set the output to a default value.
	this->setOutput( (string)("") );


};

//-----------------------------------------------------------------------------

TextFileStorage::TextFileStorage( ToolchainNode* parent, int index ) : ToolchainOperation<Datahandler*, string>( parent, index )
{
	
	// Set the input to a default value.
	this->setInput( NULL );

	// Set the output to a default value.
	this->setOutput( (string)("") );


};

//-----------------------------------------------------------------------------
TextFileStorage::TextFileStorage( ToolchainNode* parent, string loc, string name, bool individual ) : ToolchainOperation<Datahandler*, string>( parent )
{
	location = loc;
	fileName = name;
	individualFiles = individual;

	// Set the input to a default value.
	this->setInput( NULL );

	// Set the output to a default value.
	this->setOutput( (string)("") );

};

//-----------------------------------------------------------------------------

TextFileStorage::~TextFileStorage()
{

};

//-----------------------------------------------------------------------------

void TextFileStorage::execute()
{
	
	// Check to see if there is input.
	if( this->getInput() == NULL )
	{
		// TODO throw
	}
	
	if( individualFiles )
	{
		saveToIndividualFile();
	}
	else
	{
		saveToSingleFile();
	}	

	this->executeChildren();
	
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

void TextFileStorage::setIndividualFiles( bool ind )
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
  int pos = this->getInput()->getPosition();
  

  
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
				file << endl;
				
				switch( data->getType() )
				{
					case typeFieldDataInt:
						file << data->getInt() << endl;
					break;
					
					case typeFieldDataFloat:
						file << data->getFloat() << endl;
					break;
					
					case typeFieldDataDouble:  
						file << data->getDouble() << endl;
					break;
					
					case typeFieldDataString:
						file << data->getString() << endl;
					break;
					
					case typeFieldDataBool:
						if( data->getBool() )
						{
							file << "true" << endl;
						}
						else
						{
							file << "false" << endl;
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


  // Resore the initial position of the internal Datahandler iterator. This is not as it is seposed to be. TODO alter the datahandler internal iterator.
  (this->getInput())->getObjectAt( pos );


	// Set the output to the full file name.
	this->setOutput( this->getLocation() + this->getFileName() );


};


//-----------------------------------------------------------------------------

void TextFileStorage::saveToIndividualFile()
{

	string str;
	ofstream file;


  // Declare actual field data object.
  FieldData* data; 

  // Get the initial position of the internal iterator of the Datahandler.
  int pos = this->getInput()->getPosition();

  // Get the first data object.
 	ObjectData* objectData= getInput()->getFirstObject();


	// Loop over all elements in the datahandler
	for( int i = 0; i < (int)getInput()->getListSize(); i++ )
	{

		// Create the file name.
		stringstream integerConvertor;
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
						file << data->getInt() << endl;
					break;
					
					case typeFieldDataFloat:
						file << data->getFloat() << endl;
					break;
					
					case typeFieldDataDouble:
						file << data->getDouble() << endl;
					break;
					
					case typeFieldDataString:
						file << data->getString() << endl;
					break;
					
					case typeFieldDataBool:
						if( data->getBool() )
						{
							file << "true" << endl;
						}
						else
						{
							file << "false" << endl;
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
  (this->getInput())->getObjectAt( pos );


	// Set the output to the location of the files.
	this->setOutput( this->getLocation() );

};


//-----------------------------------------------------------------------------

string TextFileStorage::toString()
{
	string loc = this->getLocation();
	if( loc.compare("") == 0 )
	{
		// TODO throw error
	}
	
	string name = this->getFileName();
	if( name.compare( "" ) == 0 )
	{
		// TODO throw error
	}
	
	string output = this->ToolchainNode::toString() + "Location: \"\"" + loc + "\"\"\nFile name: \"\"" + name + "\"\"\nIndividual: \"\"" + this->boolToString(this->getIndividualFiles()) + "\"\"\n"; 
	return output;
};		

//-----------------------------------------------------------------------------

void TextFileStorage::fromString( string input )
{
	size_t found_location, found_file, found_indi, found_quote1, found_quote2, found_quote3, found_quote4, found_quote5, found_quote6;

	// Read the base class variables from the string
	this->ToolchainNode::fromString( input );

	// Search for the location identifier
  found_location = input.find("Location: ");
  if( found_location != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote1 = input.find("\"\"", found_location+10 );
  	if( found_quote1 != string::npos )
  	{
  		// Search for the end quote
  		found_quote2 = input.find("\"\"", found_quote1+2 );
			if( found_quote2 != string::npos )
			{
				// Set the name of this object
				this->setLocation( input.substr( found_quote1+2, found_quote2-(found_quote1+2) ) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in TextFileStorage::fromString, line " << __LINE__ << ": unable to find quote 2 for location.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in TextFileStorage::fromString, line " << __LINE__ << ": unable to find quote 1 for location.\n";
  	} 	
  }
  else
  {
  	// TODO throw
  	cout << "ERROR in TextFileStorage::fromString line " << __LINE__ << ": no location found for object with input: \n\"" << input << "\"\n";
  }
  
  
	// Search for the file name identifier
  found_file = input.find("File name: ");
  if( found_file != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote3 = input.find("\"\"", found_file+11 );
  	if( found_quote3 != string::npos )
  	{
  		// Search for the end quote
  		found_quote4 = input.find("\"\"", found_quote3+2 );
			if( found_quote4 != string::npos )
			{
				// Set the description of this object
				this->setFileName( input.substr( found_quote3+2, found_quote4-(found_quote3+2) ) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in TextFileStorage::fromString, line " << __LINE__ << ": unable to find quote 4 for file name.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in TextFileStorage::fromString, line " << __LINE__ << ": unable to find quote 3 for file name.\n";
  	} 	
  }	
  else
  {
  	// TODO throw
  	cout << "ERROR in TextFileStorage::fromString line " << __LINE__ << ": no file name found for object with input: \n\"" << input << "\"\n";
  }
  
  
	// Search for the Individual files identifier
  found_indi = input.find("Individual: ");
  if( found_indi != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote5 = input.find("\"\"", found_indi+12 );
  	if( found_quote5 != string::npos )
  	{
  		// Search for the end quote
  		found_quote6 = input.find("\"\"", found_quote5+2 );
			if( found_quote6 != string::npos )
			{
				// Set the description of this object
				this->setIndividualFiles( this->stringToBool(input.substr( found_quote5+2, found_quote6-(found_quote5+2) )) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in TextFileStorage::fromString, line " << __LINE__ << ": unable to find quote 6 for individual files.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in TextFileStorage::fromString, line " << __LINE__ << ": unable to find quote 5 for file individual files.\n";
  	} 	
  }	
  else
  {
  	// TODO throw
  	// This might nog be a problem as the command does not need any arguments.
  	cout << "Warning in TextFileStorage::fromString line " << __LINE__ << ": no individual files boolean found for object with input: \n\"" << input << "\"\n";
  }  
  
};

//-----------------------------------------------------------------------------


bool TextFileStorage::stringToBool( string input )
{
	bool output;
	
	if( input.compare(0, 4, "true") == 0 || input.compare(0, 4, "TRUE") == 0 || input.compare(0, 4, "True") == 0 )
	{ 
		output = true;
	}
	else if( input.compare(0, 5, "false") == 0 || input.compare(0, 5, "FALSE") == 0 || input.compare(0, 5, "False") == 0 )
	{
	 output = false;
	}
	else
	{
		// TODO
		//throw Error: invalid convertion from string to bool.
	}
	
	return output;
};



//-----------------------------------------------------------------------------


string TextFileStorage::boolToString( bool input )
{
	string output = "false";
	if( input ) output = "true";	
	
	return output;
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


