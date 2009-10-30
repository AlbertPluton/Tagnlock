//
//	Author: A.L. Hertog
//	Date: 30 October 2009
//	License: GPL
//
//


#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <string>
using namespace std;


//! A class to store the configuration of the program in.
class Configuration
{

	public:
		
		//! The default constructor	
		Configuration();
	
		//! The default destructor
		~Configuration();
		
		
		//! Load the configuration from a file
		void load();
		
		
		//! Save the configuration to a file.
		void save();
	
	
	
	private:



};

#endif


