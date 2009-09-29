//
//	Author: A.L. Hertog
//	Date: 13 November 2008
//	License: GPL
//
//

#include "Datahandler.h"

#include "Category.h"

#include <exception>

#include "URIobject.h"

#include <iostream>
#include <vector>

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
	
	// Lets start of by defining a Category

	// A vector for the combo field
	vector<string> comboOptions;
	comboOptions.push_back("option 1");
	comboOptions.push_back("option 2");
	comboOptions.push_back("option 3");

	TextField fieldA( "text_A", true, true );
	CheckField fieldB( "check_B", false, true );
	CheckField fieldC( "check_C", false, true );
  ComboField fieldD( "combo_D", true, false, &comboOptions, ComboRadio);
	TextField fieldE( "text_E", false, false );	
	CheckField fieldF( "check_F", false, true );
	double min = -2;
	double max = 6;
	SpinField  fieldG( "spin_G", false, false, NULL, &max, 0.01, true, 3, true );	

	Category category_test;
	category_test.addField(&fieldA);
	category_test.addField(&fieldB);
	category_test.addField(&fieldC);
	category_test.addField(&fieldD);
	category_test.addField(&fieldE);
	category_test.addField(&fieldF);
	category_test.addField(&fieldG);

	category_test.setName("testName");



	// Lets load a second Category from a definition file.
	Category category_GPL;
	category_GPL.loadCategory("src/test/testCategory.txt");
	
	
	// Generate data for these categories and add them to a Datahandler.
	Datahandler dataHandler;
	string location = ""; URIobject uri(location);
	ObjectData* objectData;
	FieldData* fieldData;
	
		
	// Data for the first category
	for( int i = 1; i <= 5; i++ )
	{
		dataHandler.addNewObject( &category_test, &uri );
		objectData = dataHandler.getCurrentObject();
		(objectData->getDataAt( 0 ))->set( (string)"First string" );	
		(objectData->getDataAt( 1 ))->set( true );	
		(objectData->getDataAt( 2 ))->set( false );	
		(objectData->getDataAt( 3 ))->set( (string)"Second string" );
		(objectData->getDataAt( 4 ))->set( (string)"Third string" );
		(objectData->getDataAt( 5 ))->set( true );
		(objectData->getDataAt( 6 ))->set( i );
		//for( int j = 0; j < objectData->getSize(); j++ ) cout << "Type: " << (objectData->getDataAt( j ))->getType() << "\n"; //TODO remove debug line
		//cout << "\n"; //TODO remove debug line
	}
	
	
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
	objectData = dataHandler.getFirstObject();
	for( int i = 0; i < 8; i++ )
	{
		cout << "\n";
		for( int j = 0; j < objectData->getSize(); j++ )
		{
			fieldData = objectData->getDataAt(j);
			printData( fieldData );
		}
		objectData = dataHandler.getNextObject();
	}

	// Test of the getObjectAt function, mainly the shortets route calculation.

	// Get the 2e data object
	objectData = dataHandler.getObjectAt( 2 );
	cout << "\nNumber 2:\n";
	for( int j = 0; j < objectData->getSize(); j++ )
	{
		fieldData = objectData->getDataAt(j);
		printData( fieldData );
	}

	// Get the 7e data object
	objectData = dataHandler.getObjectAt( 7 );
	cout << "\nNumber 7:\n";
	for( int j = 0; j < objectData->getSize(); j++ )
	{
		fieldData = objectData->getDataAt(j);
		printData( fieldData );
	}

	// Get the 4e data object
	objectData = dataHandler.getObjectAt( 4 );
	cout << "\nNumber 4:\n";
	for( int j = 0; j < objectData->getSize(); j++ )
	{
		fieldData = objectData->getDataAt(j);
		printData( fieldData );
	}
	
	// Get the 5e data object
	objectData = dataHandler.getObjectAt( 5 );
	cout << "\nNumber 5:\n";
	for( int j = 0; j < objectData->getSize(); j++ )
	{
		fieldData = objectData->getDataAt(j);
		printData( fieldData );
	}
	

}




