//
//	Author: A.L. Hertog
//	Date: 29 September 2008
//	License: GPL
//
//



#include "Datahandler.h"


#include <iostream>
#include <fstream>
#include <sstream>



//-----------------------------------------------------------------------------

Datahandler::Datahandler() : name("")
{

	this->it = objectMap.begin();
	position = 0;
//	name = "";
};

//-----------------------------------------------------------------------------

Datahandler::~Datahandler()
{

};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNext()
{
	incrementIT();
	if( this->it->second.state == TODO_NO_DATAOBJECT )
	{
		addObjectData();
	}
	return this->it->second.objectData;
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPrevious()
{
	decrementIT();
	if( this->it->second.state == TODO_NO_DATAOBJECT )
	{
		addObjectData();
	}
	return this->it->second.objectData;
}

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getFirst()
{

	this->it = objectMap.begin();
	position = 0;
	if( this->it->second.state == TODO_NO_DATAOBJECT )
	{
		addObjectData();
	}
	return this->it->second.objectData;
	
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getLast()
{

	this->it = (objectMap.end())--;
	position = objectMap.size()-1;
	if( this->it->second.state == TODO_NO_DATAOBJECT )
	{
		addObjectData();
	}
	return this->it->second.objectData;

};

//-----------------------------------------------------------------------------



ObjectData* Datahandler::getFirstObject()
{
	this->it = objectMap.begin();
	position = 0;
	
	// Check to see if this file name has the correct state.
	if( (it->second.state == TODO_HAS_DATAOBJECT) || (it->second.state == COMPLETED_ALL_REQUIRED) )
	{
		return it->second.objectData;
	}
	else
	{
		// If the first filename in the map has no ObjectData object go en check the next one.
		return getNextObject();
	}
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getLastObject()
{
	this->it = --objectMap.end();	// end returns a past last element iterator thus decrement for last element
	position = objectMap.size()-1;  

	// Check to see if this file name has the correct state.
	if( (it->second.state == TODO_HAS_DATAOBJECT) || (it->second.state == COMPLETED_ALL_REQUIRED) )
	{
		return it->second.objectData;
	}
	else
	{
		// If the last filename in the map has no ObjectData object go en check the previous one.
		return getPreviousObject();
	}

};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getCurrentObject()
{
	// See if there are objects in the list.
	if( objectMap.size() > 0 )	
	{
		return this->it->second.objectData;
	}
	return NULL;
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNextObject()
{

	incrementIT();
	
	// See if the new position has a ObjectData object
	if( (this->it->second.state == TODO_HAS_DATAOBJECT) || (this->it->second.state == COMPLETED_ALL_REQUIRED) )
	{
	 	return this->it->second.objectData;
	}
	else if( position == objectMap.size()-1 ) // If the last object in the map has no object 
	{
		return NULL; 
	}
	else // Go search the next file name
	{
		return getNextObject();
	}

};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPreviousObject()
{

	decrementIT();

	// See if the new position has a ObjectData object
	if( (this->it->second.state == TODO_HAS_DATAOBJECT) || (this->it->second.state == COMPLETED_ALL_REQUIRED) )
	{
	 	return this->it->second.objectData;
	}
	else if( position == 0 ) // If the last object in the map has no object 
	{
		return NULL; 
	}
	else // Go search the previous file name
	{
		return getPreviousObject();
	}	
	
};
		
//-----------------------------------------------------------------------------

ObjectData* Datahandler::getObjectAt( int index )
{
	
	// See if index is within the current range of object
	if( (index >= 0) &&  (index < objectMap.size())  )
	{
	
		// The number of steps required to reach the new object
		int fromBegin = index;
		int fromEnd 	= objectMap.size() - 1 - index;
		int fromPos   = index - position;

		// Find the shortest way to reach the desired position.

		if( (fromBegin <= fromEnd) && (fromBegin*fromBegin <= fromPos*fromPos) ) // Use the square to lose possible minus sign of fromPos
		{
			this->it = objectMap.begin();
			position = 0;
			for( int i = 0; i < fromBegin; i++ ) incrementIT();	
		}
		else if( fromEnd*fromEnd <= fromPos*fromPos )		// Starting from the end is the shortest way 
		{
			this->it = --objectMap.end();	// end returns a past last element iterator thus decrement for last element
			position = objectMap.size()-1;
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
	
	}
	else 
	{
		return NULL;
	}
	
	// Make new object if it does not have one.
	if( this->it->second.state == TODO_NO_DATAOBJECT ) addObjectData();
	
	return this->it->second.objectData;

};


//-----------------------------------------------------------------------------


ObjectData* Datahandler::getNextObjectTodo()
{

	// Obtain the current position in the map
	map<string, fileStateObject>::iterator localIT = this->it;
	int pos = this->position;		
		
	// Go one up
	++localIT;
	++pos;
		
			
		
	while( localIT != objectMap.end() )
	{
		if( localIT->second.state == TODO_NO_DATAOBJECT ) // Add an object if it has non
		{
			this->it = localIT;
			setPosToIT();
			addNewObject( localIT->second.category, localIT->second.uri );
			return this->it->second.objectData;
		}
		else if( localIT->second.state == TODO_HAS_DATAOBJECT ) // Set it as current object if not all required fields are filled out.
		{
			this->it = localIT;
			setPosToIT();		
			return this->it->second.objectData;
		}
		++localIT;
		++pos;			
	}
	
	// No object todo was found.
	return NULL;

	
};

//-----------------------------------------------------------------------------


ObjectData* Datahandler::getPreviousObjectTodo()
{

	// Obtain the current position in the map
	map<string, fileStateObject>::iterator localIT = this->it;
	int pos = this->position;		
		
	// Go one down
	--localIT;
	--pos;
		
			
		
	while( pos > -1 )
	{
		if( localIT->second.state == TODO_NO_DATAOBJECT ) // Add an object if it has non
		{
			this->it = localIT;
			setPosToIT();
			addNewObject( localIT->second.category, localIT->second.uri );
			return this->it->second.objectData;
		}
		else if( localIT->second.state == TODO_HAS_DATAOBJECT ) // Set it as current object if not all required fields are filled out.
		{
			this->it = localIT;
			setPosToIT();		
			return this->it->second.objectData;
		}
		--localIT;
		--pos;			
	}
	
	// No object todo was found.
	return NULL;

	
};


//-----------------------------------------------------------------------------

ObjectData* Datahandler::getFirstObjectCompleted()
{

	// Obtain the current position in the map
	map<string, fileStateObject>::iterator localIT = objectMap.begin();
	int pos = this->position;		
		
	// Go one up
	++localIT;
	++pos;
		
			
		
	while( localIT != objectMap.end() )
	{
		if( localIT->second.state == COMPLETED_ALL_REQUIRED ) // If it completed all the required fields return it.
		{
			this->it = localIT;
			setPosToIT();
			return this->it->second.objectData;
		}
		++localIT;
		++pos;			
	}
	
	// No completed object was found
	return NULL;

};


//-----------------------------------------------------------------------------

ObjectData* Datahandler::getLastObjectCompleted()
{

	// Obtain the current position in the map
	map<string, fileStateObject>::iterator localIT = objectMap.end();
	int pos = this->position;		
		
	// Go one down
	--localIT;
	--pos;
		
			
		
	while( pos > -1 )
	{
		if( localIT->second.state == COMPLETED_ALL_REQUIRED ) // If it completed all the required fields return it.
		{
			this->it = localIT;
			setPosToIT();
			return this->it->second.objectData;
		}
		--localIT;
		--pos;			
	}
	
	// No completed object was found
	return NULL;

};


//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNextObjectCompleted()
{

	// Obtain the current position in the map
	map<string, fileStateObject>::iterator localIT = this->it;
	int pos = this->position;		
		
	// Go one up
	++localIT;
	++pos;
		
			
		
	while( localIT != objectMap.end() )
	{
		if( localIT->second.state == COMPLETED_ALL_REQUIRED ) // If it completed all the required fields return it.
		{
			this->it = localIT;
			setPosToIT();
			return this->it->second.objectData;
		}
		++localIT;
		++pos;			
	}
	
	// No completed object was found
	return NULL;

};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPreviousObjectCompleted()
{

	// Obtain the current position in the map
	map<string, fileStateObject>::iterator localIT = this->it;
	int pos = this->position;		
		
	// Go one down
	--localIT;
	--pos;
		
			
		
	while( pos > -1 )
	{
		if( localIT->second.state == COMPLETED_ALL_REQUIRED ) // If it completed all the required fields return it.
		{
			this->it = localIT;
			setPosToIT();
			return this->it->second.objectData;
		}
		--localIT;
		--pos;			
	}
	
	// No completed object was found
	return NULL;

};


//-----------------------------------------------------------------------------

void Datahandler::addNewObject( Category* category, URIobject* name )
{

	string fileName = name->getUriString();
	map<string, fileStateObject>::iterator it = objectMap.find( fileName );
	
	// If the object is not found, add it.
	if( it == objectMap.end() )
	{
		addKey( name );	
	}
	else
	{
		// TODO throw
		cout << "ERROR in Datahandler::addNewObject: object already in map.\n";
	}

	

};


//-----------------------------------------------------------------------------

int Datahandler::getMapSize()
{
	return (int)objectMap.size();
};

//-----------------------------------------------------------------------------

int Datahandler::getPosition()
{
	return position;
};

//-----------------------------------------------------------------------------

void Datahandler::setPosition( int pos )
{
	if( pos > 0 )
	{
		if( pos < objectMap.size() )	
		{
			this->it = objectMap.begin();
			position = 0;
			while( pos != position ) { incrementIT(); }; // Loop till the desired position is reached.
		}
		else	// If index exceeds the size of the map, set the position to the end of the map.
		{
			this->it = objectMap.end();
			position = objectMap.size()-1;
		}
	}
	else	// If index is below equal or below zero set it to zero.
	{
		this->it = objectMap.begin();
		position = 0;
	}

};

//-----------------------------------------------------------------------------

void Datahandler::incrementIT()
{
	
	if( position < ((int)objectMap.size()-1) )	// To prevent invalid data acces
	{
		++(this->it);
		++position;	
	}
};

//-----------------------------------------------------------------------------

void Datahandler::decrementIT()
{
	if( position > 0 )	// To prevent invalid data acces
	{
		--(this->it);
		--position;
	}
};

//-----------------------------------------------------------------------------

void Datahandler::setPosToIT()
{
	
	map<string, fileStateObject>::iterator localIT = objectMap.begin();
	int pos = 0;
	
	while( (localIT != this->it) && (localIT != objectMap.end()) )
	{
		++localIT;
		++pos;
	}
	
	if( localIT == this->it )
	{
		this->position = pos;
	}
	else
	{
		// TODO throw
		cout << "ERROR in Datahandler::setPosToIT: Unable to find position for iterator.\n";
	}

};

//-----------------------------------------------------------------------------
/*
URIobject* Datahandler::getNextFile()
{

	//URIobject file;
	if( todo.size() != 0 )
	{
		// Get the last element from the vector and deleted it from the list.
		URIobject* file = todo.back();
		todo.pop_back();
		return file;
	}
	else
	{
		// TODO trow
		cout << "ERROR: Datahandler::getNextFile : todo is empty.\n";
	}
	
	return NULL;
};
*/
//-----------------------------------------------------------------------------

list<URIobject*> Datahandler::filesToDo()
{
	list<URIobject*> todo;
	map<string, fileStateObject>::iterator localIT = objectMap.begin();
	while( localIT != objectMap.end() )
	{
		if( (localIT->second.state == TODO_NO_DATAOBJECT) || (localIT->second.state == TODO_HAS_DATAOBJECT) )
		{
			todo.push_back( localIT->second.uri );
		}
		++localIT;
	}
	return todo;
};

//-----------------------------------------------------------------------------

list<URIobject*> Datahandler::filesDone()
{
	list<URIobject*> done;
	map<string, fileStateObject>::iterator localIT = objectMap.begin();
	while( localIT != objectMap.end() )
	{
		if( localIT->second.state == DONE_EXECUTED_TOOLCHAIN )
		{
			done.push_back( localIT->second.uri );
		}
	}
	return done;	
};

//-----------------------------------------------------------------------------


void Datahandler::fileFinished( ObjectData* object )																
{
	bool found = false;
	map<string, fileStateObject>::iterator it = objectMap.begin();
	
	while( it != objectMap.end() )
	{
		if( it->second.objectData == object ) 
		{
			found == true;
			it->second.state = DONE_EXECUTED_TOOLCHAIN;
			break;
		}
		else it++;
	}

	if( !found )
	{
		// TODO throw
		cout << "ERROR in Datahandler::fileFinished: unable to find finished object.\n";
	}
			
};


//-----------------------------------------------------------------------------

void Datahandler::updateFileList()
{



	list<URIobject*>* foundFiles;	

	for( int iFolder = 0; iFolder < folders.size(); iFolder++ )
	{
		
		// Search a folder and return a list of files which have the desired type(s).
		foundFiles = searchDirectory( folders[iFolder], recursive[iFolder] );
		
		// Loop over all the  files to add to the map
		list<URIobject*>::iterator it = foundFiles->begin();
		while( it != foundFiles->end() )
		{
			addKey( *it );
			++it;
		}
		
		delete foundFiles;
	}
	
	
	
};

//-----------------------------------------------------------------------------


list<URIobject*> * Datahandler::searchDirectory( URIobject folder, bool rec )
{

#ifdef TODO_DEF
#warning TODO in file __FILE__ at line __LINE__. The folder seach perforemd in this function should have its own class. In this class a function should just return a function.
#endif

	const unsigned char isFile = 0x8;
	const unsigned char isFolder = 0x4;
	
	struct dirent *dptr;
	DIR *pdir = NULL; 	

	// TODO try
	list<URIobject*> * foundFiles = new list<URIobject*>;

	
	list<URIobject> foundFolders;	
	
	// Open folder
	string folderString = folder.getFileName();	
	const char* folderName = folderString.c_str();
	pdir = opendir( folderName );
	
	cout << "Folder name is: \"" << folderName << "\"\n";
	
	if( pdir != NULL ) 
	{

		while( dptr=readdir(pdir) )
    {
      string fileNameFound = dptr->d_name;
      

			if ( dptr->d_type == isFile)
			{
      	// A file is found
      	string nameOfFile = dptr->d_name;
      	
      	// See if the file has the correct type
      	if( correctType( nameOfFile ) )
      	{
      		// See if it is not allready added
      		string uriString = folder.getUriString() + "/" + nameOfFile;
      		map<string, fileStateObject>::iterator foundIT = objectMap.find( uriString );
					if( foundIT == objectMap.end() )
					{      		
	      		// Add it
		    		URIobject* uri = new URIobject( uriString );
		    		foundFiles->push_back( uri ); 
  				}    		
      	};
      }
      else if( rec && (dptr->d_type == isFolder)  )
   		{
		 		string nameOfFolder = dptr->d_name;
		 		// Check to see if it equal to .. of ., we don't want to recursively search backwards ;-)
		 		if( ! ((nameOfFolder.compare("..") == 0) || (nameOfFolder.compare(".") == 0)) )
		 		{
	 				// A directory is found and we are in a recursive folder		
	 				// Add it to the list of folders todo.
		   		string uriString = folder.getUriString() + "/" + nameOfFolder;
		   		URIobject uri( uriString );
		   		foundFolders.push_back( uri );
		   	}
  		};

		};

		closedir(pdir);

	}
	else
	{
		// TODO throw
		cout << "ERROR: Datahandler::searchDirectory: unable to open directory: \"" << folder.getUriString() << "\"\n";
	}
	
	// Loop over all directories which are to be done in recursive mode.
	while( !foundFolders.empty() )
	{
		// Search a subfolder and return a list of files found in there.
		list<URIobject*>* foundFilesInSubfolder = searchDirectory( foundFolders.front(), rec );

		// Add the file found in the subfolder to the files found in the current folder 
		foundFiles->insert( foundFiles->end(), foundFilesInSubfolder->begin(), foundFilesInSubfolder->end() );

		// wrap up
		delete foundFilesInSubfolder;
		foundFolders.pop_front();	
	}


	return foundFiles;
}

//-----------------------------------------------------------------------------


bool Datahandler::correctType( string nameOfFile )
{

	if( getCategoryFromType( nameOfFile ) ) return true;
  return false;
  
};

//-----------------------------------------------------------------------------

Category* Datahandler::getCategoryFromType( string nameOfFile )
{

 	// Loop over file types
  for( int i = 0; i < fileTypes.size(); i++ )
  {
		
		// if all files are desired add the file.
		if( fileTypes[i].compare("*.*") == 0 )
		{
			return categories[i];
		}
		
		// Find the last . in the fileType or *. Using the as wild card.
		size_t posDot = fileTypes[i].find_last_of( ".*" ) + 1;		
			
		// Take only the part after the period to get rid of * and .		
		string type = fileTypes[i].substr( posDot );
		string typeOfFile = nameOfFile.substr( nameOfFile.length() - 1 - posDot  );			
						
  	// Compare extension
		if( type.compare( typeOfFile ) == 0 )
		{
			return categories[i];
		}
		 
  };
  
  return NULL;
  
};


//-----------------------------------------------------------------------------

bool Datahandler::save( )
{
	return this->save( name );
};

//-----------------------------------------------------------------------------

bool Datahandler::save( URIobject fileNameUri )
{
	string fileName = fileNameUri.getFileName();

/*	
	// If fileName is equel to "" use the name given in Datahandler::name
	if( fileName.compare("") == 0 )
	{
	
//		fileName = (this->name).getUriString();
		
		// Check to see if the fileName is still not equal to "". If it is, throw an exception.
		if( fileName.compare("") == 0 )
		{
			// TODO throw
		};	
		
	};	
*/



	// Create file object.
	ofstream file;

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{

		// Write all the folders to the file and whether or not the folder should be searched recursively.
		for( int i = 0; i < folders.size(); ++i )
		{
			file << "Folder: " << folders[i].getUriString() << "\n";
			file << "Recursive: "<< this->boolToString( recursive[i] ) << "\n";
		};


		// Write the file types to the file.
		for( int i = 0; i < fileTypes.size(); ++i )
		{
			file << "Type: " << fileTypes[i] << "\n";
			file << "Category: " << categories[i]->getName() << "\n";
		}


		// Write the file names of the already processed files
		map<string, fileStateObject>::iterator localIT = objectMap.begin();
		while( localIT != objectMap.end() )
		{
			if( localIT->second.state == DONE_EXECUTED_TOOLCHAIN ) file << "Done: " << localIT->second.uri->getUriString() << "\n";
			++localIT;
		}

		
		file.close();	
		name = fileName;
	}
	else
	{		
		// throw TODO 
		cout << "Error in Datahandler::save: Unable to open file " << fileName << "\n";
	}	

};

//-----------------------------------------------------------------------------

bool Datahandler::load( string fileNameString,  vector<Category*>* catVec )
{

	fstream file;								// Create file object.
	string inputString;					// This string is used to read the file line by line.
	size_t found;								// Used for the string function find.
	vector<string> description;	// All the lines containing information about the field.	
	
	// Open the file
	file.open( fileNameString.c_str() );

	if( file.is_open() )
	{
		
		setName( fileNameString );
		
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
				URIobject folderURI(inputString);
				folders.push_back( folderURI );
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
				fileTypes.push_back( inputString );
				continue;
			}	

			// Search for categories
			found = inputString.find("Category:", 0);	
			if( found!=string::npos )
			{
				
				bool found_cat = false;
			
				inputString.erase(0, 10);
				for( int i = 0; i < catVec->size(); i++ )
				{
					if( inputString.compare((*catVec)[i]->getName()) == 0 )
					{					
						categories.push_back( (*catVec)[i] );
						found_cat = true;
						break;
					}
				};

				if( !found_cat )
				{
					//TODO find category autmaticly if fails throw error.
					cout << "ERROR in Datahandler::load: Unable to fined category: " << inputString << "\n";	
					return false;	
				};
				
				continue;
				
			};	

			// Search for completed files
			found = inputString.find("Done:", 0);	
			URIobject* uri = NULL;
			if( found!=string::npos )
			{
				inputString.erase(0, 6);
				uri = new URIobject( inputString );
				addKey( uri );
				continue;
			}	


		}	


		file.close();	


		// Check if things went correct
		if( folders.size() != recursive.size() )
		{
// TODO Throw
			cout << "ERROR in Datahandler::load: the vectors folders and recursive do not have the same size.\n";
			return false;
		}

		// Check if things went correct
		if( fileTypes.size() != categories.size() )
		{
// TODO Throw
			cout << "ERROR in Datahandler::load: the vectors fileType and categories do not have the same size.\n";
			return false;
		}
		
		// Update the file list of all file still to be processed.
		updateFileList();


	}
	else
	{
		// throw TODO 
		cout << "Unable to open file for reading in Datahandler::load, file name: \"" << fileNameString << "\"\n";
		return false;
	}	


	name = fileNameString;
	return true;

};

//-----------------------------------------------------------------------------

void Datahandler::addFolder( URIobject folder, bool searchRecursive )
{
	folders.push_back( folder );
	recursive.push_back( searchRecursive );
};


//-----------------------------------------------------------------------------

vector<URIobject> Datahandler::getFolders()
{
	return folders;
};


//-----------------------------------------------------------------------------

vector<bool> Datahandler::getRecursive()
{
	return recursive;
};


//-----------------------------------------------------------------------------

void Datahandler::addFileType( string type, Category* cat )
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

vector<Category*> Datahandler::getCategories()
{
	return categories;
};			 

//-----------------------------------------------------------------------------

void Datahandler::setName( string uriName )
{
	name = uriName;
};

//-----------------------------------------------------------------------------

string Datahandler::getName()
{
	return name;
};


//-----------------------------------------------------------------------------


void Datahandler::addObjectData( Category* category, URIobject* name )
{
		// Search for the file name in the map.
		map<string, fileStateObject>::iterator it = objectMap.find( name->getUriString() );
		
		if( it != objectMap.end() )
		{
			// TODO throw incase of memory shortage
			ObjectData* data = new ObjectData( category, name ); 
			
			it->second.state = TODO_HAS_DATAOBJECT;
			it->second.objectData = data;
			
		}
		else
		{
			// TODO throw
			cout << "ERROR in Datahandler::addNewObject: unable to fine object name \"" << name->getUriString() << "\" in map.\n";
		}
		
		
};

//-----------------------------------------------------------------------------

void Datahandler::addObjectData( )
{

	if( this->it->second.objectData == NULL )
	{
		// TODO throw incase of memory shortage
		ObjectData* data = new ObjectData( this->it->second.category, this->it->second.uri ); 
		
		it->second.state = TODO_HAS_DATAOBJECT;
		it->second.objectData = data;
		
	}
		
};



//-----------------------------------------------------------------------------

void Datahandler::addKey( URIobject* uri )
{
	// Create the fileStateObject struct and fill it with data.	
	fileStateObject* fileStruct = new fileStateObject;
	fileStruct->state = TODO_NO_DATAOBJECT;
	fileStruct->objectData = NULL;
	fileStruct->category = getCategoryFromType( uri->getUriString() );
	fileStruct->uri = uri;				
	
	// Add the key and struct to the map.
	objectMap[ uri->getUriString() ] = *fileStruct;

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
		// TODO implement this type of exception
		// throw FieldException( 4 ); 	//throw Error: invalid convertion from string to bool.
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

