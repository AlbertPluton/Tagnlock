//
//	Author: A.L. Hertog
//	Date: 29 August 2008
//	License: GPL
//
//

#include "Category.h"

#include <exception>

#include <iostream>
#include <vector>

using namespace std;

int main (int argc, const char* argv[] )
{


// Test if constructing a category and saving it to a file works.

// TODO Why do I get a undefined refrence if i comment out the folling lines until the next todo??????

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

// TODO that is until here.
		
	Category category;

	category.addField(&fieldA);
	category.addField(&fieldB);
	category.addField(&fieldC);
	category.addField(&fieldD);
	category.addField(&fieldB);
	category.addField(&fieldF);
	category.addField(&fieldG);

	category.saveCategory( "testSaveCategory.txt", true );


// Test the getFieldTypeVector

	vector<string> types = category.getFieldTypeVector();
	cout << "\nThe field type vector holds:\n";
	for( int i=0; i < category.getFieldsSize(); i++ )
	{
		cout << "\t" << types.at(i) << "\n";
	}

// Test to see if reading from a category definition file works

	Category category2;

	try
	{ 
		category2.loadCategory( "testSaveCategory.txt" );
	}
	catch( exception& e )
	{
		cout << e.what() << "\n";
		exit(0);
	}
	
	category2.saveCategory( "testSaveCategory2.txt", true );


	cout << "------------------------- END ------------------------------\n";

};
