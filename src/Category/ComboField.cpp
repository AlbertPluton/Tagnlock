//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "ComboField.h"

#include "FieldException.h"

#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------

ComboField::ComboField( string fieldLabel, bool fieldRequired, bool fieldReset, vector<string> * fieldCombo, ComboType fieldType ) : Field( fieldLabel, fieldRequired, fieldReset)
{
	type = fieldType;
	combo = fieldCombo;
}



//-----------------------------------------------------------------------------

ComboField::ComboField( vector<string> * description )
{
	string str;

	for( int i = 0; i<(int)description->size(); i++)
	{
		str = description->at(i);
		
		if( str.compare( 0, 6, "Type: ") == 0 )	//-------------------------------------
		{
			str.erase(0, 6);
			
			// Set the ComboType to the correct value				TODO nicely implement the use of the enumerator so it can be used without the need to exend this if else statement for each new combo type.
			if( str.compare( "Combo" ) == 0 )	type = Combo;
			else if( str.compare( "ComboEntry" ) == 0 )	type = ComboEntry; 
			else if( str.compare( "ComboRadio" ) == 0 )	type = ComboRadio; 
			else
			{	
				throw FieldException( 2, "UNKONWN", "UNKNOWN", "Input string was: " + description->at(i) + "\n"  ); // throw Error: unknown combo type
			}
			
		}
		else if( str.compare( 0, 7, "Label: ") == 0 ) 	// ------------------------------
		{
			str.erase(0, 7);
			this->setLabel( str );
		}
		else if( str.compare( 0, 10, "Required: ") == 0 )	//---------------------------
		{
			// Get the substring of str which should contain true or false.
			// Convert it to a boolean, this function can throw a FieldException.
			// Assign the boolean to required.
			try { this->setRequired( this->stringToBool( str.substr(10, 5) ) ); }
			catch(  FieldException& e ) 
			{
				// Add information to the exception to be able to trace its origin. 
				e.setFieldType( this->getType() );
				e.setFieldLabel( this->getLabel() );
				e.addInfo( "Input string was:" + str + "\n" );
				throw;
			}			
			catch(  exception& e ) { throw; }	
		}
		else if( str.compare( 0, 7, "Reset: ") == 0 )	//-------------------------------
		{
			// The same as above but now not for required but for reset.
			try { this->setReset( this->stringToBool( str.substr(7, 5) ) ); }
			catch(  FieldException& e ) 
			{
				// Add information to the exception to be able to trace its origin. 
				e.setFieldType( this->getType() );
				e.setFieldLabel( this->getLabel() );
				e.addInfo( "Input string was:" + str + "\n" );
				throw;
			}			
			catch(  exception& e ) { throw; }				
		}
		else if( str.compare( 0, 6, "Size: ") == 0 )	//---------------------------------
		{
		
			str.erase(0, 6);
			int comboSize = this->stringToInt( str );
			
			// Check to see if the value of comboSize is not invalid
			if( (i + 1 + comboSize) == description->size() )
			{
			
				// TODO Am I generating a memory leak here or is this vector deleted by the destructor ?????????????????????????????????
				try {	combo = new vector<string>; }
				catch( exception& e ) { throw; }
				
				for( int j = i+1; j <= (i+comboSize); j++)
				{
					str = description->at(j);
					if( str.compare( 0, 8, "Option: ") == 0 )
					{
						str.erase(0, 8);
						this->combo->push_back(str);
					}
					else
					{
						throw FieldException( 3, this->getType(), this->getLabel(), "Input string was: " + str + "\n" ); // throw Error: Not a valid combo object 
					}
				}
				i += comboSize;
			}
			else
			{
				throw FieldException( 5, this->getType(), this->getLabel(), "Input string was: " + str + "\n" ); // throw Error: Size of combo field is invalid
			}
			
		}
		else	//-------------------------------------------------------------------
		{
			throw FieldException( 1, this->getType(), this->getLabel(), "Input string was: " + str + "\n" ); // throw Error: unknown item in description 
		}
		
	}
	
}


//-----------------------------------------------------------------------------

ComboField::~ComboField()
{
	delete combo;
}



//-----------------------------------------------------------------------------

string ComboField::getType()
{
	switch(type)
	{
		case 0:
			return "Combo"; 
		case 1:
			return "ComboEntry";
		case 2:
			return "ComboRadio";
		default:
			return "UNKNOWN";
	}
}



//-----------------------------------------------------------------------------

vector<string> ComboField::getDescription()
{

	// Create a string vector.
	vector<string> vec;

	// Fill in the different lines. 
	vec.push_back( "Type: " 			+ this->getType() 	);
	vec.push_back( "Label: "			+ this->getLabel() 	);
	vec.push_back( "Required: " 	+ this->boolToString( this->getRequired() )	); 
	vec.push_back( "Reset: "			+ this->boolToString( this->getReset() )		);
	vec.push_back( "Size: "				+ this->intToString( this->getComboSize() ) );
	// Iterate over all combo options
	for( int i = 0; i < this->getComboSize(); i++ )
	{
		vec.push_back( "Option: " + this->getComboElement( i ) );
	}

	// Return the pointer.	
	return vec;
	
}



//-----------------------------------------------------------------------------

int ComboField::getComboSize()
{
	return (int) combo->size();
}



//-----------------------------------------------------------------------------

string ComboField::getComboElement( int n )
{
	if( (n >= 0) && (n < (int)combo->size()) )
	{
		return combo->at(n);
	}
	else
	{
		// TODO throw exception.
	}
	return "";
}

//-----------------------------------------------------------------------------

void ComboField::addComboElement( string element )
{
	combo->push_back( element );
};

//-----------------------------------------------------------------------------

void ComboField::removeComboElement( int i )
{
	if( (i >= 0) && (i < (int)combo->size()) )
	{
		combo->erase( combo->begin() + i );
	}
	else
	{
		// TODO throw exception.
	}	
};

//-----------------------------------------------------------------------------


void ComboField::setComboElement( int i, string element )
{
	if( (i >= 0) && (i < (int)combo->size()) )
	{
		combo->at(i) = element;
	}
	else
	{
		// TODO throw exception.
	}	
};


//-----------------------------------------------------------------------------

void ComboField::setComboElements( vector<string> elements )
{

};
	


//-----------------------------------------------------------------------------








