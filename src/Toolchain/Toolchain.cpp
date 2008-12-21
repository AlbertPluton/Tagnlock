//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#include "Toolchain.h"



//-----------------------------------------------------------------------------

Toolchain::Toolchain() : ToolchainOperation< Datahandler*, Datahandler* >( NULL )
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

void Toolchain::execute( )//Datahandler* handler )
{
	//data = handler;
	this->setOutput( this->getInput() );
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
//	return typeid( Datahandler* );
//};


//-----------------------------------------------------------------------------

