//
//	Author: A.L. Hertog
//	Date: 19 December 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef TOOLCHAINNODEINPUT_H
#define TOOLCHAINNODEINPUT_H

#include "ToolchainNode.h"
#include <typeinfo>


//! This class is a template class which is used to enable different input data types.

template <class type_input>
class ToolchainNodeInput : public ToolchainNode
{

	public:
	
		
		//! The default constructor.
		ToolchainNodeInput( ToolchainNode* parent );
		
		//! Constructor extended with desired position of the new node.
		ToolchainNodeInput( ToolchainNode* parent, int index );
	
		//! The default destructor.
		~ToolchainNodeInput( );
		
		
		//! Set the input.
		void setInput( type_input in );
		
		//! Returns the input.
		type_input getInput( );
		

		//! Function which returns the data type of the input.
		type_info getTypeIn();
	


	private:
	
		type_input input;


};

//=============================================================================

template <class type_input>
ToolchainNodeInput<type_input>::ToolchainNodeInput( ToolchainNode* parent ) : ToolchainNode( parent )
{

};

//-----------------------------------------------------------------------------

template <class type_input>
ToolchainNodeInput<type_input>::ToolchainNodeInput( ToolchainNode* parent, int index ) : ToolchainNode( parent, index )
{

};

//-----------------------------------------------------------------------------

template <class type_input>
ToolchainNodeInput<type_input>::~ToolchainNodeInput( )
{

};

//-----------------------------------------------------------------------------

template <class type_input>
void ToolchainNodeInput<type_input>::setInput( type_input in )
{
	input = in;
};

//-----------------------------------------------------------------------------

template <class type_input>
type_input ToolchainNodeInput<type_input>::getInput( )
{
	return input;
};

//-----------------------------------------------------------------------------

template <class type_input>
type_info ToolchainNodeInput<type_input>::getTypeIn()
{
	return typeid(input);
};

//-----------------------------------------------------------------------------




#endif
