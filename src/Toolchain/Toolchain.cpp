//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#include "Toolchain.h"

#include "ToolchainOperation.h"


//-----------------------------------------------------------------------------

Toolchain::Toolchain() : ToolchainNode( NULL )
{

};

//-----------------------------------------------------------------------------

Toolchain::~Toolchain()
{

};

//-----------------------------------------------------------------------------

void Toolchain::saveToolchain( string fileName )
{
	// TODO
};

//-----------------------------------------------------------------------------

void Toolchain::loadToolchain( string fileName )
{
	// TODO
};

//-----------------------------------------------------------------------------

void Toolchain::execute( Datahandler* handler )
{
	data = handler;
	this->executeChildren();
};

//-----------------------------------------------------------------------------

Datahandler* Toolchain::getOutput()
{
	return data;
};


//-----------------------------------------------------------------------------

//type_info Toolchain::getTypeOut()
//{
//	return typeid(data);
//};


//-----------------------------------------------------------------------------

