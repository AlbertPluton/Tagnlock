//
//	Author: A.L. Hertog
//	Date: 5 December 2008
//	License: GPL
//
//


#include "ExecuteSystemCommand.h"

#include <iostream>


//-----------------------------------------------------------------------------

ExecuteSystemCommand::ExecuteSystemCommand( ToolchainNode* parent ) : ToolchainOperation<string, int>( parent )
{

	// Set the input to a default value.
	this->setInput( (string)("") );

	// Set the output to a default value.
	this->setOutput( 0 );

};


//-----------------------------------------------------------------------------

ExecuteSystemCommand::ExecuteSystemCommand( ToolchainNode* parent, int index ) : ToolchainOperation<string, int>( parent, index )
{

	// Set the input to a default value.
	this->setInput( (string)("") );

	// Set the output to a default value.
	this->setOutput( 0 );

};


//-----------------------------------------------------------------------------

ExecuteSystemCommand::ExecuteSystemCommand( ToolchainNode* parent, string comm ) : ToolchainOperation<string, int>( parent )
{
	setCommand( comm );

	// Set the input to a default value.
	this->setInput( (string)("") );

	// Set the output to a default value.
	this->setOutput( 0 );

};


//-----------------------------------------------------------------------------


ExecuteSystemCommand::ExecuteSystemCommand( ToolchainNode* parent, string comm, string args ) : ToolchainOperation<string, int>( parent )
{
	setCommand( comm );
	setArguments( args );

	// Set the input to a default value.
	this->setInput( (string)("") );

	// Set the output to a default value.
	this->setOutput( 0 );

};
			

//-----------------------------------------------------------------------------

ExecuteSystemCommand::ExecuteSystemCommand( ToolchainNode* parent, string comm, vector<string> args ) : ToolchainOperation<string, int>( parent )
{
	setCommand( comm );
	setArguments( args );

	// Set the input to a default value.
	this->setInput( (string)("") );

	// Set the output to a default value.
	this->setOutput( 0 );

};


//-----------------------------------------------------------------------------

ExecuteSystemCommand::~ExecuteSystemCommand( )
{

};

//-----------------------------------------------------------------------------


void ExecuteSystemCommand::execute()
{

	string str = this->getCommand() + " " + this->getInput() + " " + this->getArguments();
	
	cout << "Command string is: " << str << "\n";					// TODO remove debug lines
	
	for( int i = 0; i < (int)arguments.size(); i++ ) cout << "argument " << i << ": " << arguments.at(i) << "\n";
	
	
	// If the command processor is available 
	if( system( NULL ) )
	{
		// execute the system command.
		this->setOutput( system( str.c_str() ) );
	}
	else
	{
		// TODO throw 
	}
	
	//this->executeChilderen();
	
};


//-----------------------------------------------------------------------------


void ExecuteSystemCommand::setCommand( string comm )
{
	command = comm;
};


//-----------------------------------------------------------------------------

string ExecuteSystemCommand::getCommand( )
{
	return command;
};			

//-----------------------------------------------------------------------------

void ExecuteSystemCommand::setArguments( string args )
{
	this->deleteAllArguments( );
	ExecuteSystemCommand::addArguments( args );
};

//-----------------------------------------------------------------------------

void ExecuteSystemCommand::setArguments( vector<string> args )
{
	this->deleteAllArguments( );
	ExecuteSystemCommand::addArguments( args );
};

//-----------------------------------------------------------------------------

void ExecuteSystemCommand::addArguments( string args )
{
	// Convert the string to a vector and add this vector to the arguments.
	this->addArguments( this->stringToVector( args ) );
};			

//-----------------------------------------------------------------------------

void ExecuteSystemCommand::addArguments( vector<string> args )
{
	for( int i = 0; i < (int)args.size(); i++ )
	{
		arguments.push_back( args.at(i) );
	}
};				

//-----------------------------------------------------------------------------

void ExecuteSystemCommand::deleteArgument( int index )
{
	
	if( index >= (int)arguments.size() )
	{
		// TODO throw
	}
	
	arguments.erase( arguments.begin()+index );
};

//-----------------------------------------------------------------------------

void ExecuteSystemCommand::deleteAllArguments( )
{
	arguments.clear();
};

//-----------------------------------------------------------------------------

string ExecuteSystemCommand::getArguments( )
{
	return this->vectorToString( &arguments );
};

//-----------------------------------------------------------------------------

string ExecuteSystemCommand::getArgument( int index )
{
	if( index >= (int)arguments.size() )
	{
		// TODO throw
	}
	
	return arguments.at( index );
};			

//-----------------------------------------------------------------------------

string ExecuteSystemCommand::vectorToString( vector<string>* vec )
{
	string str;
	
	// Loop through the vector en add all the elements to the string with spaces in between.
	for( int i = 0; i < (int)vec->size(); i++ )
	{
		str += vec->at(i);
		str += " ";
	}
	
	// Delete the last redundant white space.
	//if( 0 < (int)vec->size() ) str.erase( str.end() );
	
	return str;
};

//-----------------------------------------------------------------------------

vector<string> ExecuteSystemCommand::stringToVector( string str )
{
	vector<string> vec;
	
	size_t found, foundDeliberateSpaceBegin, foundDeliberateSpaceEnd;
	

  string delimiter = " \t\n";

	// Used to indicate a deliberate white space
	string spaceDelimiter = "\'\"";

	// Delete white spaces in front and after the arguments
	found = str.find_first_not_of( delimiter );
	if( found != string::npos ) str.erase( 0, found );
	if( found == string::npos ) return vec;	// The string is empty thus return an empty vector
	found = str.find_last_not_of( delimiter );
	if( found != string::npos ) str.erase( found+1, str.size() );


	
	while( found != string::npos )
	{

		found = str.find_first_of( delimiter );
		foundDeliberateSpaceBegin = str.find_first_of( spaceDelimiter );

		// Note: string::npos == -1 by default therefor check if the found variables are not equal to it before comparing the two to see which is larger.


		// The end of an argument is found
		if( (found != string::npos) && (foundDeliberateSpaceBegin != string::npos) && (found < foundDeliberateSpaceBegin)  )
		{
		
		
			// Add the argument to the vector.
			vec.push_back( str.substr(0, found-1 ) );
		
			// Erase it from the string including the after it.
			str.erase(0, found );
			
			
		}
		else 
		// A string with deliberate white spaces is found 
		if( (found != string::npos) && (foundDeliberateSpaceBegin != string::npos) && (found > foundDeliberateSpaceBegin)  )
		{
		
		
			// Search for the end of the string with deliberate white spaces
			foundDeliberateSpaceEnd = str.find_first_of( spaceDelimiter, foundDeliberateSpaceBegin+1 );
			
			// If no end was found, throw an exception
			if( foundDeliberateSpaceEnd == string::npos )
			{
				// TODO throw
				cout << "Something went wrong in ExecuteSystemCommand::stringToVector( string str ), line" << __LINE__ << ".\n";
			}
			
			// Search for the next white space.
			found = str.find_first_of( delimiter, foundDeliberateSpaceEnd );
			
			if( found == string::npos ) 
			{
				found = str.size();
			}
			
			// Add the string with deliberate white spaces to the vector.
			vec.push_back( str.substr(0, found ) );
			
			// Erase the string
			str.erase(0, found );		
			
			// See if it was followed by a white space and in that case delete it.			
			found = str.find_first_of( delimiter );
			if( found == 0 ) str.erase(0, 1);
			
			
		}
		else
		// The end of an argument is found (There are no deliberate spaces in the argument string).
		if( found != string::npos )
		{		
		
		
			// Add the argument to the vector.
			vec.push_back( str.substr(0, found-1 ) );
		
			// Erase it from the string including the after it.
			str.erase(0, found );	
			
				
		}
		else
		// If the end of the string was found but the string is not yet empty
		if( (found == string::npos) && (str.size() > 0) )
		{		
		
		
			// Add the last argument to the vector.
			vec.push_back( str );
		
				
		}				
		else
		{	
			// TODO throw 
			cout << "Something went wrong in ExecuteSystemCommand::stringToVector( string str ), line" << __LINE__ << ".\n";
		}

		
	} // End of the while loop


	return vec;
}; 

//-----------------------------------------------------------------------------

string ExecuteSystemCommand::toString()
{
	string comm = this->getCommand();
	if( comm.compare( "" ) == 0 )
	{
		// TODO throw error
	}
	string output = this->ToolchainNode::toString() + "Command: \"\"" + comm + "\"\"\nArguments: \"\"" + this->getArguments() + "\"\"\n";
	return output;
};


//-----------------------------------------------------------------------------

void ExecuteSystemCommand::fromString( string input )
{
	size_t found_command, found_quote1, found_quote2, found_quote3, found_quote4, found_args;

	// Read the base class variables from the string
	this->ToolchainNode::fromString( input );

	// Search for the command identifier
  found_command = input.find("Command: ");
  if( found_command != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote1 = input.find("\"\"", found_command+9 );
  	if( found_quote1 != string::npos )
  	{
  		// Search for the end quote
  		found_quote2 = input.find("\"\"", found_quote1+2 );
			if( found_quote2 != string::npos )
			{
				// Set the name of this object
				this->setCommand( input.substr( found_quote1+2, found_quote2-(found_quote1+2) ) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in ExecuteSystemCommand::fromString, line " << __LINE__ << ": unable to find quote 2 for command.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in ExecuteSystemCommand::fromString, line " << __LINE__ << ": unable to find quote 1 for command.\n";
  	} 	
  }
  else
  {
  	// TODO throw
  	cout << "ERROR in ExecuteSystemCommand::fromString line " << __LINE__ << ": no command found for object with input: \n\"" << input << "\"\n";
  }
  
	// Search for the arguments identifier
  found_args = input.find("Arguments: ");
  if( found_args != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote3 = input.find("\"\"", found_args+11 );
  	if( found_quote3 != string::npos )
  	{
  		// Search for the end quote
  		found_quote4 = input.find("\"\"", found_quote3+2 );
			if( found_quote4 != string::npos )
			{
				// Set the description of this object
				this->setArguments( input.substr( found_quote3+2, found_quote4-(found_quote3+2) ) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in ExecuteSystemCommand::fromString, line " << __LINE__ << ": unable to find quote 4 for arguments.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in ExecuteSystemCommand::fromString, line " << __LINE__ << ": unable to find quote 3 for argurments.\n";
  	} 	
  }	
  else
  {
  	// TODO throw
  	// This might nog be a problem as the command does not need any arguments.
  	cout << "WARNING in ExecuteSystemCommand::fromString line " << __LINE__ << ": no arguments found for object with input: \n\"" << input << "\"\n";
  } 
   
};


//-----------------------------------------------------------------------------

