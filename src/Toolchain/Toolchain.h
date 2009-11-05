//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include "ToolchainOperation.h"

#include "Datahandler.h"
#include "ObjectData.h"
#include "FieldData.h"
#include <ostream>
#include <typeinfo>

#include "ExecuteSystemCommand.h"
#include "TextFileStorage.h"

//! A Toolchain object is the start of a tooolchain.

class Toolchain : public ToolchainOperation<Datahandler*, Datahandler*>
{

	public:
	
		//! The default constructor.
		Toolchain();
		
		//! The default destructor.
		~Toolchain();
	
		
		//! Store the toolchain in a file. This function uses the name given in the variable fileName of this class. If non is given it will throw an error.
		void saveToolchain( );
		
		//! Store the toolchain in a file.
		/*!
			\param fileName The name and location of the desired save file.
		*/
		void saveToolchain( string fileName );
		
		//! Load a toolchain from a file.
		/*!
			\param fileName The name and location of the desired file.
		*/
		static Toolchain* loadToolchain( string fileName );
		
		
		//! Execute the toolchain
		void execute( );//Datahandler* handler );
		
		
		//! Returns a pointer to the datahandler on which this toolchain is operating.
		Datahandler* getOutput();
		
		
		//! Returns the file name in which the toolchain is stored. Will return "" if non is given.
		string getFileName();
		
		//! Set the file name of this toolchain
		void setFileName( string name );

				
	private:
		
		Datahandler* data;
		
		string getChilderen( ToolchainNode* parent, string parentID );
		
		void addNodeFromString( string id, string type, string node );
		
		string fileName;
		
		
};


#endif
