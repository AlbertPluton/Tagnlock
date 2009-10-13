//
//	Author: A.L. Hertog
//	Date: 17 December 2008
//	License: GPL
//
//


#ifndef TEXTFILESTORAGE_H
#define TEXTFILESTORAGE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Datahandler.h"

#include "../ToolchainNode.h"
#include "../ToolchainOperation.h"


//! This class can be used to store the data in a Datahandler in a text file.
/*!
	All data from the Datahandler can either be stored in a single text file of each object can be save to an individual file.
*/

class TextFileStorage : public ToolchainOperation<Datahandler*, string>
{


	public:
	
		//! The default constructor
		TextFileStorage( ToolchainNode* parent );
		
		
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
		void execute();
		
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
		

	private:

		string location;
		
		string fileName;
		
		bool individualFiles;


		//! Function used to store all data in a single file ( individualFiles == false ).
		void saveToSingleFile();
		
		//! Function used to store every object in an individual file ( individualFiles == true ).
		void saveToIndividualFile();
		


};





#endif
