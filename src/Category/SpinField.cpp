//
//	Author: A.L. Hertog
//	Date: 09 October 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "SpinField.h"

#include <exception>
#include "FieldException.h"

#include <sstream>

#include <iostream>

using namespace std;


//-----------------------------------------------------------------------------


SpinField::SpinField( string fieldLabel, bool fieldRequired, bool fieldReset ) : Field( fieldLabel, fieldRequired, fieldReset)
{
	// Set some default values.	
	min = NULL;
	max = NULL;
	step = 1;
	dec = 1;
	adhereStep = false;
	alwaysUpdate = false;
}


//-----------------------------------------------------------------------------


SpinField::SpinField( string fieldLabel, bool fieldRequired, bool fieldReset, double* minimum, 
							double* maximum, double stepsize, bool adStep, int decimals, bool update ) : Field( fieldLabel, fieldRequired, fieldReset)
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
	alwaysUpdate = update;

};


//-----------------------------------------------------------------------------


SpinField::SpinField( vector<string> * description )
{
	string str;
	
	double number;	// used to convert string to double

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
		else if( str.compare( 0, 9, "Minimum: " ) == 0 )
		{
			str.erase(0, 9);
			if( !(str.compare( 0, 4, "NULL") == 0) )
			{
				try
				{
					min = new double; 
				}
				catch( exception& e) { throw; }
				*min = this->stringToDouble( str );
			}
			else
			{
				min = NULL;
			}
		}
		else if( str.compare( 0, 9, "Maximum: " ) == 0 )
		{
			str.erase(0, 9);
			if( !(str.compare( 0, 4, "NULL") == 0) )
			{
				try
				{
					max = new double; 
				}
				catch( exception& e) { throw; }
				*max = this->stringToDouble( str );
			}
			else
			{
				max = NULL;
			}
		}		
		else if( str.compare( 0, 10, "Stepsize: " ) == 0 )
		{
			str.erase(0, 10);
			step = this->stringToDouble( str );	
		}
		else if( str.compare( 0, 12, "AdhereStep: " ) == 0 )
		{
			// Get the substring of str which should contain true or false.
			// Convert it to a boolean, this function can throw a FieldException.
			// Assign the boolean to adhereStep.
			try { this->setAdhereStep( this->stringToBool( str.substr(12, 5) ) ); }
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
		else if( str.compare( 0, 10, "Decimals: " ) == 0 )
		{
			str.erase(0, 10);
			dec = this->stringToInt( str );	
		}
		else if( str.compare( 0, 14, "AlwaysUpdate: " ) == 0 )
		{
			// Get the substring of str which should contain true or false.
			// Convert it to a boolean, this function can throw a FieldException.
			// Assign the boolean to alwaysUpdate.
			try { this->setAlwaysUpdate( this->stringToBool( str.substr(14, 5) ) ); }
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


	// Fill in the different lines. 
	vec.push_back( "Type: " 			+ this->getType() 	);
	vec.push_back( "Label: "			+ this->getLabel() 	);
	vec.push_back( "Required: " 	+ this->boolToString( this->getRequired() )	); 
	vec.push_back( "Reset: "			+ this->boolToString( this->getReset() 		)	);	


	if( this->getMinimum() != NULL ) // if min != NULL
	{
		vec.push_back( "Minimum: "		+ this->doubleToString( *(this->getMinimum()) )		);
	}
	else	// if min = NULL
	{
		vec.push_back( "Minimum: NULL" );
	}
	
	if( this->getMaximum() != NULL )	// if max != NULL
	{
		vec.push_back( "Maximum: " 		+ this->doubleToString( *(this->getMaximum()) ) );
	}
	else	// if max == NULL
	{
		vec.push_back( "Maximum: NULL" );
	}
	

	vec.push_back( "Stepsize: "		+ this->doubleToString( this->getStepsize() )	);	
	vec.push_back( "AdhereStep: " + this->boolToString( this->getAdhereStep() ) );
	
	vec.push_back( "Decimals: "		+ this->intToString( this->getDecimals() )	);
	
	
	vec.push_back( "AlwaysUpdate: " 	+ this->boolToString( this->getAlwaysUpdate()	) );
	
	return vec;
		
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


bool SpinField::getAlwaysUpdate()
{
	return alwaysUpdate;
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


void SpinField::setAlwaysUpdate( bool update )
{
	alwaysUpdate = update;
};


//-----------------------------------------------------------------------------





