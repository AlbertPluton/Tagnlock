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

ostream& operator<< (ostream& out, const ExecuteSystemCommand& node)
{
	ToolchainNode base = (ToolchainNode)node; 
	out << base;
	out << node.command << 't';
	for( int i = 0; i < node.arguments.size(); i++ )
	{
		string arg = node.arguments[i];
		out << arg << " ";
	}
	out << endl;
	return out;	
};


//-----------------------------------------------------------------------------

istream& operator>> (istream& in, ExecuteSystemCommand& node)
{
	ToolchainNode base = (ToolchainNode)node; 
	in >> base;
	in >> node.command;
	string args;
	in >> args;
	node.arguments = node.stringToVector(args);
};


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

