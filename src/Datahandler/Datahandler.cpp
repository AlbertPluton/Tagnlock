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

Datahandler::Datahandler()
{
	it = objectDataList.begin();
	position = 0;
	name = "";
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
	if( objectDataList.size() > 0 )	return (*(this->it));	// A bit strange notation to get the pointer from the list
	return NULL;
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getNextObject()
{
	incrementIT();
 	if( objectDataList.size() > 0 ) 
 	{
 		return (*(this->it));	// A bit strange notation to get the pointer from the list
 	}
 	else if( this->it == objectDataList.end() );
 	{
 		// If the datahandler is empty / at the end of known objects, make a new dataobject.
 		
 		string fileName = getNextFile();
 		
 		// If the file name is empty some thing went wrong so do nothing.
 		if( fileName.compare("") != 0 )
 		{
 			
 			// Find the file category matching the file type of this function.
 			Category* cat = getCategoryFromType( fileName );

 			if( cat ) // If a category is found
			{
				addNewObject( cat, fileName );
				return getCurrentObject();
			}
			else
			{
				// TODO throw found no category suiteble for this file. This is very strange as it was might have been / should have been to get her, during the updating of the todo vector.		
			}
			
 		}
 	}
 	
	return NULL;
};

//-----------------------------------------------------------------------------

ObjectData* Datahandler::getPreviousObject()
{
	decrementIT();
	if( objectDataList.size() > 0 ) return (*(this->it)); // A bit strange notation to get the pointer from the list
	return NULL;
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

void Datahandler::decrementIT()
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

	string file = "";
	if( todo.size() != 0 )
	{
		// Get the last element from the vector and deleted it from the vector.
		file = todo.back();
		todo.pop_back();
	}
	else
	{
		// TODO trow
		cout << "ERROR: Datahandler::getNextFile : todo is empty.\n";
	}
	return file;

};

//-----------------------------------------------------------------------------

vector<string> Datahandler::filesToDo()
{
	return todo;
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

	list<ObjectData*>::iterator it = objectDataList.begin();
	
	for (list<ObjectData*>::iterator it= objectDataList.begin(); it!= objectDataList.end(); ++it)
	{
		if( object == *it )
		{
			found = true;
			objectDataList.erase( it );
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



	list<string>* foundFiles;	

	for( int iFolder = 0; iFolder < folders.size(); iFolder++ )
	{
		
		// Search a folder and return a list of files which have the desired type(s).
		foundFiles = searchDirectory( folders[iFolder], recursive[iFolder] );
		
		if( !foundFiles->empty() )
		{
			todo.insert( todo.end(), foundFiles->begin(), foundFiles->end() );
		}
		
//		for( int iFiles = 0; iFiles < foundFiles->size(); iFiles++ )
//		{
//			todo.push_back( (*foundFiles)[iFiles] );
//		}	

		delete foundFiles;
		
	}
	
	
	
};

//-----------------------------------------------------------------------------


list<string>* Datahandler::searchDirectory( string folder, bool rec )
{
	const unsigned char isFile = 0x8;
	const unsigned char isFolder = 0x4;
	
	struct dirent *dptr;
	DIR *pdir = NULL; 	

//	try
//	{
		list<string>* foundFiles = new list<string>;
//	}
//	catch( exception& e )
//	{
		// TODO
//	}
	
	list<string> foundFolders;	
	
	// Open folder
#warning "Using not so smart way to convert uri to normal location"
	// Remove file://
	string folder2 = folder.substr( 6 );	
	const char* folderName = folder2.c_str();
	pdir = opendir( folderName );
	
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
      		// See if it is not allready done
      		bool doneBool = false;
      		for( int i = 0; i < done.size(); i++ )
      		{
      			if( nameOfFile.compare( done[i] ) == 0 )
      			{
      				doneBool = true;
      				break;
      			}
      		}
      		
      		// Add it
      		if( !doneBool ) foundFiles->push_back( folder + "/" +nameOfFile ); 
      		
      	};
      }
      else if( rec && (dptr->d_type == isFile) )
   		{
 				// A directory is found and we are in a recursive folder		
 				// Add it to the list of folders todo.
 				foundFolders.push_back( folder + dptr->d_name );
  		};

		};

		closedir(pdir);

	}
	else
	{
		// TODO throw
		cout << "ERROR: Datahandler::searchDirectory: unable to open directory: " << folder << "\n";
	}
	
	// Loop over all directories which are to be done in recursive mode.
	while( !foundFolders.empty() )
	{
		// Search a subfolder and return a list of files found in there.
		list<string>* foundFilesInSubfolder = searchDirectory( folder + foundFolders.front(), rec );

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
	return this->save( "" );
};

//-----------------------------------------------------------------------------

bool Datahandler::save( string fileName )
{

	// If fileName is equel to "" use the name given in Datahandler::name
	if( fileName.compare("") == 0 )
	{
	
		fileName = this->name;
		
		// Check to see if the fileName is still not equal to "". If it is, throw an exception.
		if( fileName.compare("") == 0 )
		{
			// TODO throw
		};	
		
	};	




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
			file << "Recursive: "<< this->boolToString( recursive[i] ) << "\n";
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
		name = fileName;
	}
	else
	{		
		// throw TODO 
		cout << "Error in Datahandler::save: Unable to open file " << fileName << "\n";
	}	

};

//-----------------------------------------------------------------------------

bool Datahandler::load( string fileName,  vector<Category*>* catVec )
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
		cout << "Unable to open file for reading in Datahandler::load.\n";
		return false;
	}	


	name = fileName;
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

void Datahandler::setName( string strName )
{
	name = strName;
};

//-----------------------------------------------------------------------------

string Datahandler::getName()
{
	return name;
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

