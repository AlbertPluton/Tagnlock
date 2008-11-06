//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	License: GPL
//
//

#include "Field.h"
#include "TextField.h"
#include "CheckField.h"
#include "ComboField.h"
#include "SpinField.h"

#include "FieldException.h"

#include <sstream>
#include <iostream>
using namespace std;


//-----------------------------------------------------------------------------

Field::Field()
{
	label = "UNKNOWN";
	required = NULL;
	reset = NULL;
}



//-----------------------------------------------------------------------------

Field::Field( string fieldLabel, bool fieldRequired, bool fieldReset )
{
	label = fieldLabel;
	required = fieldRequired;
	reset = fieldReset;
}


//-----------------------------------------------------------------------------

Field::~Field()
{
	//cout << "Destroy Field " << label << "\n";
}


//-----------------------------------------------------------------------------

Field* Field::newField( vector<string>* description )
{
	string str;
	str = description->at(0);
	Field* field = NULL;


	if( str.compare( 6, 9, "TextField" ) == 0 )
	{
		try
		{
			field = new TextField( description );
		}
		catch( exception& e )
  	{
  		// Throw the current exception to the caller of this function.
			throw;
		}
	}
	else if( str.compare( 6, 10, "CheckField" ) == 0  )
	{
		try
		{
			field = new CheckField( description );
		}
		catch( exception& e ) {	throw; }
	}
	else if( str.compare( 6, 5, "Combo" ) == 0  )
	{	
		try
		{
			field = new ComboField( description );
		}
		catch( exception& e ) { throw; }
	}
	else if( str.compare( 6, 9, "SpinField" ) == 0 ) 
	{
		try
		{
			field = new SpinField( description );
		}
		catch( exception& e ) { throw; }
	}
	else
	{
		throw FieldException( 0, "UNKNOWN", "UNKNOWN", "Input string was:" + str + "\n"  ); // throw Error: Type undefined
	}
	
	return field;
	
}



//-----------------------------------------------------------------------------

string Field::getType()
{
	return "UNKNOWN";
}


//-----------------------------------------------------------------------------

vector<string> Field::getDescription()
{

	// Create a string vector.
	vector<string> vec;

	// Fill in the different lines. 
	vec.push_back( "Type: " 		+ this->getType() 	);
	vec.push_back( "Label: "		+ this->getLabel()	);
	vec.push_back( "Required: " + this->boolToString( required )	); 
	vec.push_back( "Reset: "		+ this->boolToString( reset )			);	

	// Return the vector.	
	return vec;

}



//-----------------------------------------------------------------------------

string Field::getLabel()
{
	return label;
}



//-----------------------------------------------------------------------------

bool Field::getRequired()
{
	return required;
}


//-----------------------------------------------------------------------------

bool Field::getReset()
{
	return reset;
}
		

//-----------------------------------------------------------------------------

void Field::setLabel( string fieldLabel )
{
	label = fieldLabel;
}



//-----------------------------------------------------------------------------

void Field::setRequired( bool fieldRequired )
{
	required = fieldRequired;
}


//-----------------------------------------------------------------------------

void Field::setReset( bool fieldReset )
{
	reset = fieldReset;
}


//-----------------------------------------------------------------------------

bool Field::stringToBool( string input )
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


string Field::boolToString( bool input )
{
	string output = "false";
	if( input ) output = "true";	
	
	return output;
};




//-----------------------------------------------------------------------------


int Field::stringToInt( string input )
{
		stringstream convert( input );
		int number = 0;
		convert >> number;
		return number;
};


//-----------------------------------------------------------------------------



double Field::stringToDouble( string input )
{
		stringstream convert( input );
		double number = 0.0;
		convert >> number;
		return number;
};



//-----------------------------------------------------------------------------


string Field::intToString( int input )
{
	stringstream convert;
	convert << input;
	return convert.str();
};


//-----------------------------------------------------------------------------


string Field::doubleToString( double input )
{
	stringstream convert;
	convert << input;
	return convert.str();
}


















