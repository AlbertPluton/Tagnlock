//
//	Author: A.L. Hertog
//	Date: 27 August 2008
//	License: GPL
//
//

#include "TextField.h"
#include "CheckField.h"
#include "ComboField.h"


#include <iostream>
#include <vector>

using namespace std;



int main (int argc, const char* argv[] )
{

	vector<string> description;

	// --------------------------------------------------------------------------
	// Test for the TextField class
	
	TextField fieldA( "test_A", false, true );
	
	cout << "\n\n";

	cout << "fieldA type: " 		<< fieldA.getType() 		<< "\n";
	cout << "fieldA label: " 		<< fieldA.getLabel() 		<< "\n";
	cout << "fieldA required: " << fieldA.getRequired() << "\n";
	cout << "fieldA reset: " 		<< fieldA.getReset() 		<< "\n\n";

	cout << "fieldA description:\n";
	description = fieldA.getDescription();
	for( int i = 0; i<description.size(); i++)
	{
		cout << "\t" << description.at(i) << "\n";
	}
	cout << "\n\n";



	// --------------------------------------------------------------------------
	// Test for the CheckField class
	
	CheckField fieldB( "test_B", true, true );
	
	cout << "fieldB type: " 		<< fieldB.getType() 		<< "\n";
	cout << "fieldB label: " 		<< fieldB.getLabel() 		<< "\n";
	cout << "fieldB required: " << fieldB.getRequired() << "\n";
	cout << "fieldB reset: " 		<< fieldB.getReset() 		<< "\n\n";
	
	cout << "fieldB description:\n";
	description = fieldB.getDescription();
	for( int i = 0; i<description.size(); i++)
	{
		cout << "\t" << description.at(i) << "\n";
	}
	cout << "\n\n";

	
	// --------------------------------------------------------------------------
	// Test for the ComboField class
	
	vector<string> comboOptions;
	comboOptions.push_back("option 1");
	comboOptions.push_back("option 2");
	comboOptions.push_back("option 3");
	
	ComboField fieldC( "test_C", true, false, &comboOptions, ComboRadio);
	
	cout << "fieldC type: " 		<< fieldC.getType() 		<< "\n";
	cout << "fieldC label: " 		<< fieldC.getLabel() 		<< "\n";
	cout << "fieldC required: " << fieldC.getRequired() << "\n";
	cout << "fieldC reset: " 		<< fieldC.getReset() 		<< "\n";
	cout << "fieldC combo size: "				<< fieldC.getComboSize() 			<< "\n";
	cout << "fieldC combo element 2: "	<< fieldC.getComboElement(1)	<< "\n\n";
	
	cout << "fieldC description:\n";
	description = fieldC.getDescription();
	for( int i = 0; i<description.size(); i++)
	{
		cout << "\t" << description.at(i) << "\n";
	}
	cout << "\n\n";

	
}
