//
//	Author: A.L. Hertog
//	Date: 30 October 2009
//	License: GPL
//
//


#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#define CONFIG_FILE_NAME	"configuration_file"



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

#include <sigc++/sigc++.h>




//! A class to store the configuration of the program in.
class Configuration
{

	public:
		
		//! The default constructor	
		Configuration( string className );
	
		//! The default destructor
		~Configuration();
		
		
		//! Load the configuration from a file
		void loadConfig();
		
		
		//! Save the configuration to a file.
		void saveConfig();


	

	protected:
		
		//! Add all key - data pairs in the class to the map.
		virtual void parseToConfig(){};
		
		//! Update the class with data from the map. 
		virtual void updateFromConfig(){};
		

		//! Set the data of key. If key does not excits add it.
		template<class dataType> void setPair( string key, dataType data );	

		//! Add a key - data pair. Throw exception if key already excits.
		template<class dataType> void addPair( string key, dataType data );
		
		
		//! Get the data at the specified key. Throws an exception if the key is unknown. Throws an error if dataType and the data type indicator do not match
		template<class dataType> dataType getData( string key );



		//! The signal to indicate the derived classes should parse their data to the map.
		typedef sigc::signal<void> type_signal_parse;

		//! The signal to indicate a new configMap has been loaded from file.
		typedef sigc::signal<void> type_signal_map_loaded;


		//! Returns the signal parse.
		/*!
			This signal should be connected to the parseToMap function of all derived classes.
		*/
		type_signal_parse signal_parse();


		//! Returns the signal map loaded.
		/*!
			This signal can be connected to the updataFromMap function of the derived class(es).
		*/
		type_signal_map_loaded signal_map_loaded();
		
			
	private:

		string classKey;
	
		static map<string, string> configMap;

		//! Generate a data type indicator for the given data.
		/*!
			\returns an char indicating the type: 'I' for integer, 'F' for float, 'D' for double, 'S' for string and 'B' for boolean.
		*/
		template<class dataType> char getDataType( dataType data );
		
		int stringToInt( string data );
		float stringToFloat( string data );
		double stringToDouble( string data );
		bool stringToBool( string data );



		//! The actual signal definition
		type_signal_parse m_signal_parse;


		//! The actual signal definition
		type_signal_map_loaded m_signal_map_loaded;

};





//=============================================================================


template<class dataType> void Configuration::setPair(string key, dataType data)
{

	key = classKey + "-" + key;

	// Convert the data via a string stream to a string and add it to the map.
	stringstream ss;
	ss << getDataType(data) << data;
	configMap[key] = 	ss.str();		
};

//-----------------------------------------------------------------------------

template<class dataType> void Configuration::addPair(string key, dataType data)
{

	key = classKey + "-" + key;

	// Search for the given key
	map<string, string>::iterator it = configMap.find( key );
	
	//! Add the object if it is NOT found in the map.
	if( it == configMap.end() )
	{
		// Convert the data via a string stream to a string and add it to the map.
		stringstream ss;
		ss << getDataType(data) << data;
		configMap[key] = 	ss.str();
	}
	else
	{
		// TODO throw
		cout << "ERROR in Configuration::addPair: Key already found in map.\n";		
	}
	
};

//-----------------------------------------------------------------------------


template<> inline int Configuration::getData<int>( string key )
{
	
	key = classKey + "-" + key;
	
	// Search for the given key
	map<string, string>::iterator it = configMap.find( key );

	//! Check for the excistance of the key.
	if( it != configMap.end() )
	{	
	
		// Obtain the data in string form and extract the data type indicator.
		string data = configMap[key];
		string typeIndicator = data.substr(0,1);
		data.erase(0,1);
		
		// See if the data type indicator matches this type.
		if(typeIndicator.compare("I") == 0)		return stringToInt( data );
		else
		{
			// TODO throw
			cout << "ERROR in Configuration::getData<int>: dataType: \"int\" does not match data type indicator \"" << typeIndicator << "\".\n";
		}	
		
	}
	else
	{
		// TODO throw
		cout << "ERROR in Configuration::getData<int>: unable to find key \"" << key << "\" in map.\n";
	}
};


//-----------------------------------------------------------------------------

template<> inline float Configuration::getData<float>( string key )
{
	
	key = classKey + "-" + key;
	
	// Search for the given key
	map<string, string>::iterator it = configMap.find( key );

	//! Check for the excistance of the key.
	if( it != configMap.end() )
	{	
	
		// Obtain the data in string form and extract the data type indicator.
		string data = configMap[key];
		string typeIndicator = data.substr(0,1);
		data.erase(0,1);
		
		// See if the data type indicator matches this type.
		if(typeIndicator.compare("F") == 0)		return stringToFloat( data );
		else
		{
			// TODO throw
			cout << "ERROR in Configuration::getData<float>: dataType: \"float\" does not match data type indicator \"" << typeIndicator << "\".\n";
		}	
		
	}
	else
	{
		// TODO throw
		cout << "ERROR in Configuration::getData<float>: unable to find key \"" << key << "\" in map.\n";
	}
};


//-----------------------------------------------------------------------------

template<> inline double Configuration::getData<double>( string key )
{
	
	key = classKey + "-" + key;
	
	// Search for the given key
	map<string, string>::iterator it = configMap.find( key );

	//! Check for the excistance of the key.
	if( it != configMap.end() )
	{	
	
		// Obtain the data in string form and extract the data type indicator.
		string data = configMap[key];
		string typeIndicator = data.substr(0,1);
		data.erase(0,1);
		
		// See if the data type indicator matches this type.
		if(typeIndicator.compare("D") == 0)		return stringToDouble( data );
		else
		{
			// TODO throw
			cout << "ERROR in Configuration::getData<double>: dataType: \"double\" does not match data type indicator \"" << typeIndicator << "\".\n";
		}	
		
	}
	else
	{
		// TODO throw
		cout << "ERROR in Configuration::getData<double>: unable to find key \"" << key << "\" in map.\n";
	}
};


//-----------------------------------------------------------------------------

template<> inline string Configuration::getData<string>( string key )
{
	
	key = classKey + "-" + key;
	
	// Search for the given key
	map<string, string>::iterator it = configMap.find( key);

	//! Check for the excistance of the key.
	if( it != configMap.end() )
	{	
	
		// Obtain the data in string form and extract the data type indicator.
		string data = configMap[key];
		string typeIndicator = data.substr(0,1);
		data.erase(0,1);
		
		// See if the data type indicator matches this type.
		if(typeIndicator.compare("S") == 0)		return data;
		else
		{
			// TODO throw
			cout << "ERROR in Configuration::getData: dataType: \"string\" does not match data type indicator \"" << typeIndicator << "\".\n";
		}	
		
	}
	else
	{
		// TODO throw
		cout << "ERROR in Configuration::getData: unable to find key \"" << key << "\" in map.\n";
	}
};


//-----------------------------------------------------------------------------

template<> inline bool Configuration::getData<bool>( string key )
{
	
	key = classKey + "-" + key;
	
	// Search for the given key
	map<string, string>::iterator it = configMap.find( key);

	//! Check for the excistance of the key.
	if( it != configMap.end() )
	{	
	
		// Obtain the data in string form and extract the data type indicator.
		string data = configMap[key];
		string typeIndicator = data.substr(0,1);
		data.erase(0,1);
		
		// See if the data type indicator matches this type.
		if(typeIndicator.compare("B") == 0)		return stringToBool( data );
		else
		{
			// TODO throw
			cout << "ERROR in Configuration::getData: dataType: \"bool\" does not match data type indicator \"" << typeIndicator << "\".\n";
		}	
		
	}
	else
	{
		// TODO throw
		cout << "ERROR in Configuration::getData: unable to find key \"" << key << "\" in map.\n";
	}
};


//-----------------------------------------------------------------------------


template<class dataType> char Configuration::getDataType( dataType data )
{
	if( typeid(data) == typeid(int) ) 				return 'I';
	else if( typeid(data) == typeid(float) ) 	return 'F';
	else if( typeid(data) == typeid(double) ) return 'D';
	else if( typeid(data) == typeid(string) ) return 'S';
	else if( typeid(data) == typeid(bool) ) 	return 'B';
};
	
//-----------------------------------------------------------------------------
	
#endif


