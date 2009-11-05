//
//	Author: A.L. Hertog
//	Date: 30 October 2009
//	License: GPL
//
//


#include "Configuration.h"


// Define the static member variable
map<string, string> Configuration::configMap;

//-----------------------------------------------------------------------------


Configuration::Configuration( string className )
{
	classKey = className;
	this->loadConfig();
};


//-----------------------------------------------------------------------------


Configuration::~Configuration()
{


};




//-----------------------------------------------------------------------------

void Configuration::loadConfig()
{

	fstream file;								// Create file object.
	string inputString;					// This string is used to read the file line by line.
	size_t found;								// Used for the string function find.
	
		
	// Open the file
	file.open( CONFIG_FILE_NAME );

	if( file.is_open() )
	{
		
		while( !file.eof() )
		{
				
			// throw TODO
			getline(file, inputString);		
			
			// Delete comments
			string delimiter = "#";
			found = inputString.find_first_of( delimiter );
			if( found != string::npos ) inputString.erase( found, inputString.size() );
			
			// Delete whitespaces infront and after the data
			delimiter = " \t\n\r\v\f";
			found = inputString.find_first_not_of( delimiter );
			if( found != string::npos ) inputString.erase( 0, found );
			if( found == string::npos ) inputString.erase( 0, inputString.size() );
			found = inputString.find_last_not_of( delimiter );
			if( found != string::npos ) inputString.erase( found+1, inputString.size() );

			// If the string is empty continue with the next line.			
			if( inputString.empty() ) continue;	
			
			// Search for the end of the map key.
			found = inputString.find_first_of("=");
			if( found!=string::npos )
			{			
				string key = inputString.substr(0, found);
				string data = inputString.substr(found+1);
				
				// Search for the given key
				map<string, string>::iterator it = configMap.find(key);
	
				//! Add the object if it is NOT found in the map.
				if( it == configMap.end() )
				{
					configMap[key] = data;
				}
				else
				{
					// TODO throw
					cout << "ERROR in Configuration::load: key \"" << key << "\" already excits in map.\n";
				}
			}	
				
		}
		
		// Emit the signal indicating that a new map has been loaded.
		m_signal_map_loaded.emit();
		
		file.close();	
	
		
	}
	else
	{
		// throw TODO 
		cout << "ERROR in Configuration::load: unable to open file \"" << CONFIG_FILE_NAME <<"\".\n";
	}		
};




//-----------------------------------------------------------------------------


void Configuration::saveConfig()
{
	// Create file object.
	ofstream file;

	// Open the file
	file.open( CONFIG_FILE_NAME );
	
	if( file.is_open() )
	{
	
		// Emit the signal to the derived classes that they should parse their data.
		m_signal_parse.emit( );
	
	
		// See if the map has key pairs in it.
		if( configMap.size() != 0 )
		{
			map<string, string>::iterator it;
			// Loop over all key pairs.
			for( it = configMap.begin(); it != configMap.end(); it++ )
    	{
    		// Write the key and the data to the file.
				file << it->first << "=" << it->second << "\n";    		    	
    	}
		}
		else
		{
			// TODO throw
			cout << "ERROR in Configuration::save: no key pars in map.\n";
		}
	
	
	
		file.close();	
		
	}
	else
	{		
		// throw TODO 
		cout << "ERROR in Configuration::save: unable to open file \"" << CONFIG_FILE_NAME <<"\".\n";
	}
	
		
};


//-----------------------------------------------------------------------------

int Configuration::stringToInt( string data )
{
	stringstream convert( data );
	int number = 0;
	convert >> number;
	return number;
};

//-----------------------------------------------------------------------------

float Configuration::stringToFloat( string data )
{
	stringstream convert( data );
	float number = 0.0;
	convert >> number;
	return number;
};

//-----------------------------------------------------------------------------

double Configuration::stringToDouble( string data )
{
	stringstream convert( data );
	double number = 0.0;
	convert >> number;
	return number;
};

//-----------------------------------------------------------------------------

bool Configuration::stringToBool( string data )
{
	bool output;
	
	if( data.compare(0, 4, "true") == 0 || data.compare(0, 4, "TRUE") == 0 || data.compare(0, 4, "True") == 0 )
	{ 
		output = true;
	}
	else if( data.compare(0, 5, "false") == 0 || data.compare(0, 5, "FALSE") == 0 || data.compare(0, 5, "False") == 0 )
	{
	 output = false;
	}
	else
	{
		// TODO throw FieldException( 4 ); 	//throw Error: invalid convertion from string to bool.
		cout << "ERROR in Configuration::stringToBool: invalid convertion from string to bool.\n";		
	}
	
	return output;
};

//-----------------------------------------------------------------------------

Configuration::type_signal_parse Configuration::signal_parse()
{
	return m_signal_parse;
};

//-----------------------------------------------------------------------------

Configuration::type_signal_map_loaded Configuration::signal_map_loaded()
{
	return m_signal_map_loaded;
};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


