//
//	Author: A.L. Hertog
//	Date: 29 September 2008
//	License: GPL
//
//



#include "Datahandler.h"





//-----------------------------------------------------------------------------

Datahandler::Datahandler()
{
	it = objectDataList.begin();
	position = 0;
};

//-----------------------------------------------------------------------------

Datahandler::~Datahandler()
{

};

//-----------------------------------------------------------------------------

void Datahandler::addObject( ObjectData* data )
{

		if( (int)objectDataList.size() == 0 ) 			// If the list is empty add to the front.
		{
			objectDataList.push_front( data );
			it = objectDataList.begin();		
			position = 1;	
		}
		else if( it ==  objectDataList.end() ) 			// if it is the last item of the list, use push back
		{
			objectDataList.push_back( data );
			it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
			position = objectDataList.size();
		}
		else 																				// if it is the in the middel of the list, use insert
		{
			it++; 																		// Increment the it because insert puts the new object infront of the previous object
			objectDataList.insert( it, data );
			it--; 																		// Go back to the new data
			position++;
		}

};


//-----------------------------------------------------------------------------

void Datahandler::addNewObject( Category* category, string name )
{
		// TODO throw incase of memory shortage
		ObjectData* data = new ObjectData( category, name ); 

		
		if( (int)objectDataList.size() == 0 ) 			// If the list is empty add to the front.
		{
			objectDataList.push_front( data );
			it = objectDataList.begin();
			position = 1;			
		}
		else if( it ==  objectDataList.end() ) 			// if it is the last item of the list, use push back
		{
			objectDataList.push_back( data );
			it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
			position = objectDataList.size();
		}
		else 																				// if it is the in the middel of the list, use insert
		{
			it++;																			// Increment the it because insert puts the new object infront of the previous object
			objectDataList.insert( it, data );
			it--; 																		// Go back to the new data
			position++;																// The position should be incremented to the new data.
		}
		
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getFirstObject()
{
	this->it = objectDataList.begin();
	position = 1;
	return *(this->it);
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getLastObject()
{
	this->it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
	position = objectDataList.size();  
	return *(this->it);
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getCurrentObject()
{
	return (*(this->it));	// A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNextObject()
{
	incrementIT();
 	return (*(this->it));	// A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPreviousObject()
{
	decrementIT();
	return (*(this->it)); // A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getObjectAt( int index )
{
	// The number of steps required to reach the new object
	int fromBegin = index-1;
	int fromEnd 	= objectDataList.size() - index;
	int fromPos   = index - position;

	// Find the shortest way to reach the desired position.

	if( (fromBegin <= fromEnd) && (fromBegin*fromBegin <= fromPos*fromPos) ) // Use the square to lose possible minus sign of fromPos
	{
		this->it = objectDataList.begin();
		position = 1;
		for( int i = 0; i < fromBegin; i++ ) incrementIT();	
	}
	else if( fromEnd*fromEnd <= fromPos*fromPos )		// Starting from the end is the shortest way 
	{
		this->it = --objectDataList.end();	// end returns a past last element iterator thus decrement for last element
		position = objectDataList.size();
		for( int i = 0; i < fromEnd; i++ ) decrementIT();
	}
	else if( fromPos > 0 )	// Go up from the current position
	{
		for( int i = 0; i < fromPos; i++ ) incrementIT();
	}
	else if( fromPos < 0 ) // Go down from the current position
	{
		for( int i = fromPos; i < 0; i++ ) decrementIT();
	}
	
	return  (*this->it); // A bit strange notation to get the pointer from the list
};

//-----------------------------------------------------------------------------

int Datahandler::getListSize()
{
	return (int)objectDataList.size();
};

//-----------------------------------------------------------------------------

int Datahandler::getPosition()
{
	return position;
};

//-----------------------------------------------------------------------------

void Datahandler::incrementIT()
{
	if( position < objectDataList.size()-1 )	// To prevent invalid data acces
	{
		(this->it)++;
		position++;
	}
};

//-----------------------------------------------------------------------------

void Datahandler::


decrementIT()
{
	if( position > 1 )	// To prevent invalid data acces
	{
		(this->it)--;
		position--;
	}
};

//-----------------------------------------------------------------------------

string Datahandler::getNextFile()
{

};

//-----------------------------------------------------------------------------

vector<string> Datahandler::filesToDo()
{
	return todo;
};

//-----------------------------------------------------------------------------

vector<ObjectData*> Datahandler::filesBeingProcessed()
{
	return processing;
};

//-----------------------------------------------------------------------------

vector<string> Datahandler::filesDone()
{
	return done;
};

//-----------------------------------------------------------------------------


void Datahandler::fileFinished( ObjectData* object )
{

	bool found = false;

	for( int i = 0; i < (int)processing.size(); i++ )
	{
		if( object == processing[i] )
		{
			found = true;
			processing.erase( processing.begin() + i );
			done.push_back( object->getObjectName() );		
			break;		
		}
	};

	if( !found )
	{
// TODO throw error
		cout <<	"ERROR in Datahandler::fileFinished: Unable to find object in datahandler. Object is: " << object->getObjectName() << "\n";
	}
	
};


//-----------------------------------------------------------------------------

void Datahandler::updateFileList()
{
// TODO
};


//-----------------------------------------------------------------------------

bool Datahandler::save( string fileName )
{


	// Check to see if the category name is not equal to "". In that case throw an exception.
	if( name.compare("") == 0 )
	{
		// TODO throw
	}


	// Create file object.
	ofstream file;

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{

		// Write all the folders to the file and whether or not the folder should be searched recursively.
		for( int i = 0; i < folders.size(); i++ )
		{
			file << "Folder: " << folders[i] << "\n";
			file << "Recursive: "<< this->boolToString( Recursive[i] ) << "\n";
		};


		// Write the file types to the file.
		for( int i = 0; i < fileTypes.size(); i++ )
		{
			file << "Type: " << fileTypes[i] << "\n";
			file << "Category: " << categories[i]->getName() << "\n";
		}


		// Write the file names of the already processed files
		for( int i = 0; i < done.size(); i++ )
		{
			file << "Done: " << done[i] << "\n";
		}

		
		file.close();	
		
	}
	else
	{		
		// throw TODO 
		cout << "Unable to open file for writing in Datahandler::save.\n";
	}	

};

//-----------------------------------------------------------------------------

bool Datahandler::load( string fileName, Engine* engine )
{

	fstream file;								// Create file object.
	string inputString;					// This string is used to read the file line by line.
	size_t found;								// Used for the string function find.
	vector<string> description;	// All the lines containing information about the field.	
	
	// Open the file
	file.open( fileName.c_str() );

	if( file.is_open() )
	{
		
		while( !file.eof() )
		{
						
			// throw TODO
			getline(file, inputString);		
			
			// Delete comments
			string delimiter = "#";
			found = inputString.find_first_of( delimiter );
			if( found != string::npos ) inputString.erase( found, inputString.size() );

			// Delete whitespaces infront and after the data
			delimiter = " \t\n\r\v\f";
			found = inputString.find_first_not_of( delimiter );
			if( found != string::npos ) inputString.erase( 0, found );
			if( found == string::npos ) inputString.erase( 0, inputString.size() );
			found = inputString.find_last_not_of( delimiter );
			if( found != string::npos ) inputString.erase( found+1, inputString.size() );

			// If the string is empty continue with the next line.			
			if( inputString.empty() ) continue;	


			// Search for folders
			found = inputString.find("Folder:", 0);	
			if( found!=string::npos )
			{
				inputString.erase(0, 8);
				folders.push_back( inputString );
				continue;
			}	

			// Search for recursive booleans
			found = inputString.find("Recursive:", 0);	
			if( found!=string::npos )
			{
				inputString.erase(0, 11);
				recursive.push_back( stringToBool( inputString ) );
				continue;
			}	

			// Search for file types
			found = inputString.find("Type:", 0);	
			if( found!=string::npos )
			{
				inputString.erase(0, 6);
				fileType.push_back( inputString );
				continue;
			}	

			// Search for categories
			found = inputString.find("Category:", 0);	
			if( found!=string::npos )
			{
				inputString.erase(0, 10);
				for( int i = 0; i < engine->getCategoriesSize(); i++ )
				{
					if( engine->getCategory(i)->getName() == inputString )
					{					
						categories.push_back( engine->getCategory(i) );
						continue;				
					}
				};

				//TODO find category autmaticly if fails throw error.
				cout << "ERROR in Datahandler::load: Unable to fine category: " << inputString << "\n";	
				return false;	
			}	

			// Search for completed files
			found = inputString.find("Done:", 0);	
			if( found!=string::npos )
			{
				inputString.erase(0, 6);
				done.push_back( inputString );
				continue;
			}	


		}	


		file.close();	


		// Check if things went correct
		if( folders.size() != recursive.size() )
		{
// TODO Throw
			cout << "ERROR in Datahandler::load: the vectors folders and recursive do not have the same size."
			return false;
		}

		// Check if things went correct
		if( fileType.size() != categories.size() )
		{
// TODO Throw
			cout << "ERROR in Datahandler::load: the vectors fileType and categories do not have the same size."
			return false;
		}
		
		// Update the file list of all file still to be processed.
		updateFileList();


	}
	else
	{
		// throw TODO 
		cout << "Unable to open file for reading in Datahandler::load.\n";
		return false;
	}	

	return true;

};

//-----------------------------------------------------------------------------

void Datahandler::addFolder( string folder, bool searchRecursive )
{
	folders.push_back( folder );
	recursive.push_back( searchRecursive );
};


//-----------------------------------------------------------------------------

vector<string> Datahandler::getFolders()
{
	return folders;
};


//-----------------------------------------------------------------------------

vector<bool> Datahandler::getRecursive()
{
	return recursive;
};


//-----------------------------------------------------------------------------

void Datahandler::addFileType( string type, Category* cat );
{
	fileTypes.push_back( type );
	categories.push_back( cat );
};


//-----------------------------------------------------------------------------

vector<string> Datahandler::getFileTypes()
{
	return fileTypes;
};

//-----------------------------------------------------------------------------

vector<categories*> Datahandler::getCategories()
{
	return categories;
};

//-----------------------------------------------------------------------------

bool Datahandler::stringToBool( string input )
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
		throw FieldException( 4 ); 	//throw Error: invalid convertion from string to bool.
	}
	
	return output;
};



//-----------------------------------------------------------------------------


string Datahandler::boolToString( bool input )
{
	string output = "false";
	if( input ) output = "true";	
	
	return output;
};




//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------

