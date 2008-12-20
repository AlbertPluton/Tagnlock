//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#ifndef TOOLCHAINOPERATION_H
#define TOOLCHAINOPERATION_H

#include "ToolchainNodeOutput.h"
#include "ToolchainNode.h"
#include "ToolchainNodeInput.h"
#include "Toolchain.h"

#include <typeinfo>

#include <exception>



//! A ToolchainOperation holds information on the operations to be done on the data.

template <class type_input, class type_output>
class ToolchainOperation : public ToolchainNodeOutput<type_input, type_output>
{


	public:
	
		//! The default constructor.
		/*!
			\param parent Pointer to the parent node of this operation.
		*/
		ToolchainOperation( ToolchainNode* parent );

		
		//! The default destructor.
		~ToolchainOperation( );
		
		
		//! Function to set the input data.
		//void setInput( type_in in );
	
		//! Function to set the output data.
		//void setOutput( type_out out );
		
		//! Function to get the input data.
		//type_in getInput();
		
		//! Function to get the output data.
		//type_out getOutput();
		
		//! Function which returns the data type of the input.
		//type_info getTypeIn();
		
		//! Function which returns the data type of the output.
		//type_info getTypeOut();
	
	protected:
	
		//! This function can be called in the derived execute function to execute the children of a node.
		virtual void executeChildren();
	
	private:

		//type_in input;
		//type_out output;

};



//-----------------------------------------------------------------------------

template <class type_in, class type_out>
ToolchainOperation<type_in, type_out>::ToolchainOperation( ToolchainNode* parent ) : ToolchainNodeOutput<type_in, type_out>( parent )
{

};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
ToolchainOperation<type_in, type_out>::~ToolchainOperation( )
{

};


//-----------------------------------------------------------------------------
/*
template <class type_in, class type_out>
void ToolchainOperation<type_in, type_out>::setInput( type_in in )
{
	input = in;
};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
void ToolchainOperation<type_in, type_out>::setOutput( type_out out )
{
	output = out;
};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
type_in ToolchainOperation<type_in, type_out>::getInput()
{
	return input;
};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
type_out ToolchainOperation<type_in, type_out>::getOutput()
{
	return output;
};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
type_info ToolchainOperation<type_in, type_out>::getTypeIn()
{
	return typeid(input);
};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
type_info ToolchainOperation<type_in, type_out>::getTypeOut()
{
	return typeid(output);
};

//-----------------------------------------------------------------------------
*/
template <class type_in, class type_out>
void ToolchainOperation<type_in, type_out>::executeChildren()
{
	
	ToolchainNode* childNode = NULL;
	ToolchainNodeInput<type_out>* childNodeInput = NULL;	
	 	
	for( int i = 0; i < this->getNodeVectorSize(); i++ )
	{
		
		// Obtain a child
		childNode = this->getChildNode( i );

		try
		{
			// Cast the child to a ToolchainNodeInput object with the same input type as the output of this object.
			childNodeInput = dynamic_cast< (ToolchainNodeInput<type_out>*) > childNode;
		}
		catch( exception& e )
		{
			throw e
		}
		// Check if the cast went oke, if not throw an exeception
		//if( childNodeInput == NULL ) 
		//{
			// TODO throw
		//}	


		// Use the pointer to set the output of this class as the input of the child.
		childNodeInput->setInput( this->getOutput );
		
		// Now execute the child
		childNode->execute();


		childNode = NULL;
		childNodeInput = NULL;

	}
	
};


//-----------------------------------------------------------------------------

#endif



