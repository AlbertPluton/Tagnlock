//
//	Author: A.L. Hertog
//	Date: 17 December 2008
//	License: GPL
//
//



#include "Category.h"
#include "Field.h"
#include "FieldData.h"

#include "ToolchainNode.h"
#include "Toolchain.h"
#include "ExecuteSystemCommand.h"
#include "TextFileStorage.h"

#include "Datahandler.h"

#include <exception>

#include <iostream>
#include <vector>

#include "URIobject.h"

using namespace std;



void printData( FieldData* data )
{
	switch( data->getType() )
	{
		case typeFieldDataInt:
			cout << "Int: " << data->getInt() << "\n";
			break;
			
		case typeFieldDataFloat:
			cout << "Float: " << data->getFloat() << "\n";
			break;
			
		case typeFieldDataDouble:
			cout << "Double: " << data->getDouble() << "\n";
			break;
			
		case typeFieldDataString:
			cout << "String: " << data->getString() << "\n";
			break;
			
		case typeFieldDataBool:
			cout << "Bool: " << data->getBool() << "\n";
			break;		
			
		default:
			cout << "?????\n";
			break;			
	}


}



int main (int argc, const char* argv[] )
{

// TODO Why do I get a undefined refrence if i comment out the folling lines until the next todo??????
	TextField fieldA( "text_A", true, true );
// TODO that is until here.
	
	// Lets start of by defining a Category

	// Lets load a Category from a definition file.
	Category category_GPL;
	category_GPL.loadCategory("src/test/testCategory.txt");
	
	
	// Generate data for this category and add it to a Datahandler.
	Datahandler dataHandler;
	string uriString = ""; URIobject uri( uriString );
	ObjectData* objectData;
	FieldData* fieldData;
		
	
	
	// Data for the second category
	bool   read[] = {true, true, false};
	string name[] = {"Bart", "Albert", "Zelda"};
	string sirName[] = { "Employ", "Boss", "Cat"};
	string gender[] = { "Male", "Male", "Male" };
	string birthplace[] = { "Here", "There", "Japan" };
	double birthYear[] = { 1880, 1870, 1990 };
	string birthMonth[] = { "April", "May", "June" };
	double birthDay[] =	{ 1, 2, 3 };
	
	for( int i = 0; i < 3; i++ )
	{
		dataHandler.addNewObject( &category_GPL, &uri );
		objectData = dataHandler.getCurrentObject();
		(objectData->getDataAt( 0 ))->set( read[i] );
		(objectData->getDataAt( 1 ))->set( name[i] );
		(objectData->getDataAt( 2 ))->set( sirName[i] );
		(objectData->getDataAt( 3 ))->set( gender[i] );
		(objectData->getDataAt( 4 ))->set( birthplace[i] );
		(objectData->getDataAt( 5 ))->set( birthYear[i] );
		(objectData->getDataAt( 6 ))->set( birthMonth[i] );
		(objectData->getDataAt( 7 ))->set( birthDay[i] );
	}		

	
	// Display the data
	for( int i = 0; i < 3; i++ )
	{
		objectData = dataHandler.getObjectAt(i);
		cout << "\n";
		for( int j = 0; j < objectData->getSize(); j++ )
		{
			fieldData = objectData->getDataAt(j);
			printData( fieldData );
		}
		
	}

	
	
	//===========================================================================
	
	// Create a simple toolchain to save the data to a file.
	
	Toolchain* toolchain = new Toolchain();
	toolchain->setName("SaveToFile");
	toolchain->setDescription("This toolchain saves a datahandler to a text file and copies it to a second file.");
	toolchain->setInput( &dataHandler );

	cout << "\nToolchain name: " << toolchain->getName() << "\n";
	cout << "Toolchain desciption: " << toolchain->getDescription() << "\n\n";	


	string loc = "../";
	string fileName = "testFile";

	// Save the datahandler to 1 file
	TextFileStorage saveNode( toolchain );	
	saveNode.setLocation( loc );
	saveNode.setFileName( fileName );
	saveNode.setIndividualFiles( false );
	//saveNode.setInput( &dataHandler );

	// Copy the one file to a new file.
	ExecuteSystemCommand command( &saveNode, (string)"cp" );
	command.addArguments( loc + (string)"\'testFile 2 b\'" );


	// Save the objects in the data handler to individual files.
	TextFileStorage saveNode2( toolchain );	
	saveNode2.setLocation( loc );
	saveNode2.setFileName( fileName );
	saveNode2.setIndividualFiles( true );


	// execute the toolchain.
	toolchain->execute();
	
	
	// Lets try to save the toolchain to a file.
  toolchain->saveToolchain( "toolchainSave.txt" );

	// Lets try to load a toolchain.
	Toolchain* newToolchain = Toolchain::loadToolchain( "toolchainSave.txt" );

};




