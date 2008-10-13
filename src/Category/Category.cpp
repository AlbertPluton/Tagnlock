//
//	Author: A.L. Hertog
//	Date: 27 August 2008
//	License: GPL
//
//

#include "Category.h"

#include "FieldException.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;



//-----------------------------------------------------------------------------

Category::Category()
{
	
}



//-----------------------------------------------------------------------------

Category::~Category()
{
	//cout << "Destroy Category\n";
}



//-----------------------------------------------------------------------------

void Category::addField( Field * newField )
{
	fields.push_back(newField);
};


		
//-----------------------------------------------------------------------------

void Category::addFieldAt( Field * newField, int possition )
{			
	fields.insert( fields.begin() + possition, 1, newField );
};



//-----------------------------------------------------------------------------

void Category::loadCategory( string fileName )
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
			
			// Search the string for the keyword "Type: 
			found = inputString.find("Type: ", 0);	
			// If a new description of a field starts.
			if( found!=string::npos )
			{			
				// If there is information in the description create a field object from it. 
				// This means the first time "Type: " is found the field will not be created, 
				// only after all its information is obtained from the file and the "Type: " of
				// the next field is found it will be created. 
				if( ! description.empty() )
				{
					// Create new field object and push it in the fields vector.
					try
					{
						fields.push_back( Field::newField( &description ) );		
					}
					catch( FieldException e ) // I am not catching here by reference but by value because I've experienced some strange behaviour. When catch by reference sometimes the FieldException object would not exist any more.
					{
						int num = 1 + (int)fields.size();
            						stringstream convert;
						convert << num;
						e.addInfo( "In field number: " + convert.str() + "\n" );
						e.addInfo( "In file: " + fileName + "\n" );
						throw;
					}
					catch( exception& e )	{	throw; }					
					// The previous field has just been created thus clear the description for the new field.
					description.clear();
				}
			}
			
			// Add the line to the description.
			description.push_back( inputString );
									
		}

		// If there is informaiton in the description (the last field in the file), create a field object from it. 
		if( ! description.empty() )
		{
			// Create new field object and push it in the fields vector.
			try
			{
				fields.push_back( Field::newField( &description ) );
			}
			catch( FieldException e ) // See above about why I am catching by value.
			{
				int num = 1 + (int)fields.size();
				stringstream convert;
				convert << num;
				e.addInfo( "In field number: " + convert.str() + "\n" );
				e.addInfo( "In file: " + fileName + "\n" );
				throw;
			}
			catch( exception& e )	{ throw; }		
			description.clear();
		}	

		file.close();	
		
	}
	else
	{
		// throw TODO 
		cout << "Unable to open file for reading";
	}		
	
};



//-----------------------------------------------------------------------------

void Category::saveCategory( string fileName, bool overwrite )
{

	// Create file object.
	ofstream file;

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{
	
		vector<string> description;
				
		// Iterate over all elements in the vector fields.
		for( int i = 0; i<fields.size(); i++)
		{
			// obtain the description of element i.
			description = fields[i]->getDescription();

			// Put a white line infront of each field
			file << "\n";
	
			// Iterate over all the lines in the description
			for( int j = 0; j< (int)description.size(); j++ )
			{
				// Write a line to the file.
				file << description.at( j ) << "\n";
			}
			//cout << "Saved field no. " << i << "\n";	
		}		
		
		file.close();	
		
	}
	else
	{		
		// throw TODO 
		cout << "Unable to open file for writing";
	}	
	
};



//-----------------------------------------------------------------------------

int Category::getFieldsSize()
{
	return (int)fields.size();
};



//-----------------------------------------------------------------------------

string Category::getFieldTypeAt( int index )
{
	return fields.at( index )->getType();
};



//-----------------------------------------------------------------------------

vector<string> Category::getFieldTypeVector()
{
	vector<string> types;
	for( int i = 0; i<fields.size(); i++ )
	{
		types.push_back( fields.at(i)->getType() );
	}
	return types;
};



