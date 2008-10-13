//
//	Author: A.L. Hertog
//	Date: 09 October 2008
//	License: GPL
//
//


#include "SpinField.h"

#include <exception>
#include "FieldException.h"

#include <sstream>


//-----------------------------------------------------------------------------


SpinField::SpinField( string fieldLabel, bool fieldRequired, bool fieldReset ) : Field( fieldLabel, fieldRequired, fieldReset)
{
	// Set some default values.	
	min = NULL;
	max = NULL;
	step = 1;
	dec = 1;
	adhereStep = false;
	adhereDec = false;
}


//-----------------------------------------------------------------------------


SpinField::SpinField( string fieldLabel, bool fieldRequired, bool fieldReset, double* minimum, 
							double* maximum, double stepsize, bool adStep, int decimals, bool adDec ) : Field( fieldLabel, fieldRequired, fieldReset)
{
	min = NULL;
	max = NULL;
	
	// The class manages the values of min and max it self even though a pointer is asked. 
	// Meaning that new variables are made to which min and max point.
	// These are destroyed explicitly in the destructor.
	
	if( minimum )
	{
		try
		{
			min = new double;
		}
		catch(exception& e)
		{
			throw;	// rethrow the exception
		}
		*min = *minimum;
	}
	
	if( maximum )
	{
		try
		{
			max = new double;
		}
		catch(exception& e)
		{
			throw;	// rethrow the exception
		}
		*max = *maximum;
	}
	
	step = stepsize;
	adhereStep = adStep;
	dec = decimals;
	adhereDec = adDec;

};


//-----------------------------------------------------------------------------


SpinField::SpinField( vector<string> * description )
{
	string str;

	for( int i = 0; i<(int)description->size(); i++)
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
		else if( str.compare( 0, 7, "Reset: ") == 0 )	//-------------------------------
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
		else if( str.compare( 0, 7, "Minimum" ) == 0 )
		{
			// TODO
		}
		else if( str.compare( 0, 7, "Maximum" ) == 0 )
		{
			// TODO
		}		
		else if( str.compare( 0, 8, "Stepsize" ) == 0 )
		{
			// TODO
		}
		else if( str.compare( 0, 10, "AdhereStep" ) == 0 )
		{
			// TODO
		}			
		else if( str.compare( 0, 8, "Decimals" ) == 0 )
		{
			// TODO
		}
		else if( str.compare( 0, 9, "AdhereDec" ) == 0 )
		{
			// TODO
		}			
		else	//-------------------------------------------------------------------
		{
			throw FieldException( 1, this->getType(), this->getLabel(), "Input string was: " + str + "\n" ); // throw Error: unknown item in description 
		}
		
		
	}
};


//-----------------------------------------------------------------------------


SpinField::~SpinField()
{
	if( min != NULL ) delete min;
	if( max != NULL ) delete max;
};


//-----------------------------------------------------------------------------

string SpinField::getType()
{
	return "SpinField";
}

//-----------------------------------------------------------------------------


vector<string> SpinField::getDescription()
{

	// Create a string vector.
	vector<string> vec;

	// convert numbers to string via stringstream
  stringstream convert;
  string number;
	
	// Fill in the different lines. 
	vec.push_back( "Type: " 			+ this->getType() 	);
	vec.push_back( "Label: "			+ this->getLabel() 	);
	vec.push_back( "Required: " 	+ this->boolToString( this->getRequired() )	); 
	vec.push_back( "Reset: "			+ this->boolToString( this->getReset() )		);	

	convert << this->getMinimum();
	number = convert.str();	
	vec.push_back( "Minimum: "		+ number		);
	
	convert << this->getMaximum();
	number = convert.str();	
	vec.push_back( "Maximum: " 		+ number		);
	
	convert << this->getStepsize();
	number = convert.str();	
	vec.push_back( "Stepsize: "		+ number		);	
	vec.push_back( "AdhereStep: " + this->boolToString( this->getAdhereStep() ) );
	
	convert << this->getDecimals();
	number = convert.str();	
	vec.push_back( "Decimals: "		+ number		);
	vec.push_back( "AdhereDec: " + this->boolToString( this->getAdhereDec() ) );
		
};


//-----------------------------------------------------------------------------


double* SpinField::getMinimum()
{
	return min;
};


//-----------------------------------------------------------------------------


double* SpinField::getMaximum()
{
	return max;
};


//-----------------------------------------------------------------------------


double SpinField::getStepsize()
{
	return step;
};


//-----------------------------------------------------------------------------


int SpinField::getDecimals()
{
	return dec;
};


//-----------------------------------------------------------------------------


bool SpinField::getAdhereStep()
{
	return adhereStep;
};


//-----------------------------------------------------------------------------


bool SpinField::getAdhereDec()
{
	return adhereDec;
};


//-----------------------------------------------------------------------------


void SpinField::setMinimum( double* minimum )
{
	if( minimum )
	{
		if( min == NULL )
		{
			try
			{
				min = new double;
			}
			catch(exception& e)
			{
				throw;	// rethrow the exception
			}
		}
		*min = *minimum;
	}	
	else
	{
		min = NULL;
	}
};


//-----------------------------------------------------------------------------


void SpinField::setMaximum( double* maximum )	
{
	if( maximum )
	{
		if( max == NULL )
		{
			try
			{
				max = new double;
			}
			catch(exception& e)
			{
				throw;	// rethrow the exception
			}
		}
		*max = *maximum;
	}	
	else
	{
		max = NULL;
	}
};



//-----------------------------------------------------------------------------

void SpinField::setStepsize( double stepsize )
{
	step = stepsize;
};


//-----------------------------------------------------------------------------


void SpinField::setDecimals( int decimals )
{
	dec = decimals;
};


//-----------------------------------------------------------------------------


void SpinField::setAdhereStep( bool adhere )
{
	adhereStep = adhere;
};	


//-----------------------------------------------------------------------------


void SpinField::setAdhereDec( bool adhere )
{
	adhereDec = adhere;
};


//-----------------------------------------------------------------------------





