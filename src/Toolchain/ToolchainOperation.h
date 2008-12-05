//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#ifndef TOOLCHAINOPERATION_H
#define TOOLCHAINOPERATION_H

#include "ToolchainNode.h"

//! A ToolchainOperation holds information on the operations to be done on the data.

class ToolchainOperation : public ToolchainNode
{


	public:
	
		//! The default constructor.
		/*!
			\param parent Pointer to the parent node of this operation.
		*/
		ToolchainOperation( ToolchainNode* parent );

		
		//! The default destructor.
		~ToolchainOperation( );
		
		
	
	
	private:


};


#endif



