//
//	Author: A.L. Hertog
//	Date: 26 August 2008
//	License: GPL
//
//

#include "TextField.h"

#include <exception>
#include "FieldException.h"

#include <iostream>
using namespace std;


//-----------------------------------------------------------------------------

TextField::TextField( string fieldLabel, bool fieldRequired, bool fieldReset ) : Field( fieldLabel, fieldRequired, fieldReset)
{

}



//-----------------------------------------------------------------------------

TextField::TextField( vector<string> * description )
{
	string str;

	// Start the loop from the second item in the description. This because the type is already know.
	for( int i = 1; i<(int)description->size(); i++)
	{
		str = description->at(i);
		
		if( str.compare( 0, 7, "Label: ") == 0 ) 	// ----------------------------------
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
				e.addInfo( "Input string was: " + str + "\n" );
				throw;
			}		
			catch( exception& e) { throw; }	
		}
		else if( str.compare( 0, 7, "Reset: ") == 0)	//-------------------------------
		{
			// The same as above but now not for required but for reset.
			try { this->setReset( this->stringToBool( str.substr(7, 5) ) ); }
			catch(  FieldException& e ) 
			{
				// Add information to the exception to be able to trace its origin. 
				e.setFieldType( this->getType() );
				e.setFieldLabel( this->getLabel() );
				e.addInfo( "Input string was: " + str + "\n" );
				throw;
			}			
			catch( exception& e) { throw; }			
		}
		else	//-------------------------------------------------------------------
		{
			throw FieldException( 1, this->getType(), this->getLabel(), "Input string was: " + str + "\n" ); // throw Error: unknown item in description 
		}
		
	}
	
}



//-----------------------------------------------------------------------------

TextField::~TextField()
{

}



//-----------------------------------------------------------------------------

string TextField::getType()
{
	return "TextField";
}






