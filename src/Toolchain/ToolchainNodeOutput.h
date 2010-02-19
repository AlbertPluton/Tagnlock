//
//	Author: A.L. Hertog
//	Date: 19 December 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef TOOLCHAINNODEOUTPUT_H
#define TOOLCHAINNODEOUTPUT_H

#include "ToolchainNodeInput.h"
#include "ToolchainNode.h"
#include <typeinfo>

//! This class is a template class which is used to enable different output data types.

template <class type_input, class type_output>
class ToolchainNodeOutput : public ToolchainNodeInput<type_input>
{

	public:
	
		
		//! The default constructor.
		ToolchainNodeOutput( ToolchainNode* parent );
	
		//! Constructor extended with desired position of the new node.
		ToolchainNodeOutput( ToolchainNode* parent, int index );
		
		//! The default destructor.
		~ToolchainNodeOutput( );
		
		
		//! Set the output.
		void setOutput( type_output out );
		
		//! Returns the output.
		type_output getOutput( );
		

		//! Function which returns the data type of the output.
		type_info getTypeOut();
	


	private:
	
		type_output output;


};

//=============================================================================

template <class type_input, class type_output>
ToolchainNodeOutput<type_input, type_output>::ToolchainNodeOutput( ToolchainNode* parent ) : ToolchainNodeInput<type_input>( parent )
{

};

//-----------------------------------------------------------------------------

template <class type_input, class type_output>
ToolchainNodeOutput<type_input, type_output>::ToolchainNodeOutput( ToolchainNode* parent, int index ) : ToolchainNodeInput<type_input>( parent, index )
{

};

//-----------------------------------------------------------------------------

template <class type_input, class type_output>
ToolchainNodeOutput<type_input, type_output>::~ToolchainNodeOutput( )
{

};

//-----------------------------------------------------------------------------

template <class type_input, class type_output>
void ToolchainNodeOutput<type_input, type_output>::setOutput( type_output out )
{
	output = out;
};

//-----------------------------------------------------------------------------

template <class type_input, class type_output>
type_output ToolchainNodeOutput<type_input, type_output>::getOutput( )
{
	return output;
};

//-----------------------------------------------------------------------------

template <class type_input, class type_output>
type_info ToolchainNodeOutput<type_input, type_output>::getTypeOut()
{
	return typeid(output);
};

//-----------------------------------------------------------------------------




#endif
