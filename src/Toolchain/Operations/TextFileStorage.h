//
//	Author: A.L. Hertog
//	Date: 17 December 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef TEXTFILESTORAGE_H
#define TEXTFILESTORAGE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Datahandler.h"

#include "ToolchainNode.h"
#include "ToolchainOperation.h"


//! This class can be used to store the data in a Datahandler in a text file.
/*!
	All data from the Datahandler can either be stored in a single text file of each object can be save to an individual file.
*/

class TextFileStorage : public ToolchainOperation<Datahandler*, string>
{


	public:
	
		//! The default constructor
		TextFileStorage( ToolchainNode* parent );
		
		//! Constructor which parameter for the desired place in the list.
		TextFileStorage( ToolchainNode* parent, int index );
		
		//! Constructor with parameters
		/*!
			\param parent is a pointer to the parent node of this toolchain operation object.
			\param loc is the location in which to store the file(s).
			\param name is the file(s). If each object is stored in an individual file a number will be concatenated to this name.
			\param individual if this Boolean is true each object in the Datahandler will be stored in an individual file.
		*/
		TextFileStorage( ToolchainNode* parent, string loc, string name, bool individual );
		
		
		//! The destructor
		~TextFileStorage();
	
	
		//! Execute this command, thus store the data from the Datahandler given in the input.
		void execute( bool onlyCurrentObject = false );
		
		//! Function to set the location of the file(s).
		void setLocation( string loc );
		
		//! Function to set the common file name.
		void setFileName( string name );
		
		//! Function to set whether or not all objects are stored in individual files.
		void setIndividualFiles( bool ind );
		
		
		//! Returns the location in which the file(s) is/are stored.
		string getLocation( );
		
		//! Returns the common file name.
		string getFileName( );
		
		//! Returns the Boolean indicating whether or not all objects are stored in individual files.
		bool getIndividualFiles( );
		
		//! Convert the class to a string for saving or display purposes
		virtual string toString();		
		
		//! Set the variables of the class by description given in the string
		virtual void fromString( string input );	
		
	private:

		string location;
		
		string fileName;
		int fileNumber;
		
		bool individualFiles;
 		bool onlyCurrent;

		//! Function used to store all data in a single file ( individualFiles == false ).
		void saveToSingleFile();
		
		//! Function used to store every object in an individual file ( individualFiles == true ).
		void saveToIndividualFile();
		

		//! A function to convert strings to booleans.
		bool stringToBool( string input );
		
		//! A function to convert booleans to strings.
		string boolToString( bool input );

};





#endif
