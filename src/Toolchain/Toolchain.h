//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include "ToolchainNode.h"

#include "Datahandler.h"
#include "ObjectData.h"
#include "FieldData.h"

//! A Toolchain object is the start of a tooolchain.

class Toolchain : public ToolchainNode
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
		/*!
			\param handler Is the data handler of which the data should be processed by the tool-chain.
		*/
		void execute( Datahandler* handler );
		
	
	private:
		


};


#endif
