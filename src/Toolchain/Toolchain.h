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
	
		
		//! Store the toolchain in a file.
		/*!
			\param fileName The name and location of the desired save file.
		*/
		void saveToolchain( string fileName );
		
		//! Load a toolchain from a file.
		/*!
			\param fileName The name and location of the desired file.
		*/
		void loadToolchain( string fileName );
		
		
		//! Execute the toolchain
		void execute( );//Datahandler* handler );
		
		
		//! Returns a pointer to the datahandler on which this toolchain is operating.
		Datahandler* getOutput();
		
		
		//! Returns the type of output this object giver, Datahandler*.
		//type_info getTypeOut();
	
		friend ostream& operator+= ( ostream& out, ToolchainNode* node );
		
	private:
		
		Datahandler* data;
		
		//! This function generates a structure of node number representing the toolchain structure. This to save and load it from text files.
		/*!
			\param parent is the pointer to the parent of which the childeren need to be examind.
			\param indent is the level of indentation of the parent.
		*/
		string generateNodeStructure( ToolchainNode* parent, string indent );

		
		
};


#endif
