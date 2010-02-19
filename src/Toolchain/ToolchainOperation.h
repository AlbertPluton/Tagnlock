//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//



#ifndef TOOLCHAINOPERATION_H
#define TOOLCHAINOPERATION_H

#include "ToolchainNodeOutput.h"
#include "ToolchainNode.h"
#include "ToolchainNodeInput.h"



#include <iostream>

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
		
		//! Constructor extended with desired position of the new node.
		ToolchainOperation( ToolchainNode* parent, int index );
		
		//! The default destructor.
		~ToolchainOperation( );
		

	
	protected:
	
		//! This function can be called in the derived execute function to execute the children of a node.
		virtual void executeChildren( bool onlyCurrentObject = false );
	
	private:



};



//-----------------------------------------------------------------------------

template <class type_in, class type_out>
ToolchainOperation<type_in, type_out>::ToolchainOperation( ToolchainNode* parent ) : ToolchainNodeOutput<type_in, type_out>( parent )
{

};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
ToolchainOperation<type_in, type_out>::ToolchainOperation( ToolchainNode* parent, int index ) : ToolchainNodeOutput<type_in, type_out>( parent, index )
{

};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
ToolchainOperation<type_in, type_out>::~ToolchainOperation( )
{

};

//-----------------------------------------------------------------------------

template <class type_in, class type_out>
void ToolchainOperation<type_in, type_out>::executeChildren( bool onlyCurrentObject )
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
			childNodeInput = dynamic_cast< ToolchainNodeInput<type_out>* > (childNode);
		}
		catch( exception& e )
		{
			cout << "ToolchainOperation<type_in, type_out>::executeChilderen() throws an exception!!!!\n";
			throw e;
		}
		
		// If the cast went oke set the input of the child.
		if( childNodeInput != NULL ) 
		{
			// Use the pointer to set the output of this class as the input of the child.
			childNodeInput->setInput( this->getOutput() );
		}


		
		// Now execute the child
		childNode->execute( onlyCurrentObject );


		childNode = NULL;
		childNodeInput = NULL;

	}
	
};


//-----------------------------------------------------------------------------

#endif



