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

	// Create file object.
	ofstream file;

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{


		file += this;


		file.close();	
		name = fileName;
	}
	else
	{		
		// throw TODO 
		cout << "Error in Toolchain::saveToolchain: Unable to open file " << fileName << "\n";
	}	


};

//-----------------------------------------------------------------------------

void Toolchain::loadToolchain( string fileName )
{
	// TODO
};

//-----------------------------------------------------------------------------

void Toolchain::execute( )
{
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

ostream& operator+= ( ostream& out, ToolchainNode* node )
{

	// Cast the node to its derived type and generate the output.
	if( typeid(*node) == typeid(Toolchain) )
	{
		//Toolchain* derived = static_cast<Toolchain*> node;
		out << *node; // Toolchain class has no << operator.
	}
	else 	if( typeid(*node) == typeid(ExecuteSystemCommand) )
	{
		ExecuteSystemCommand* derived = static_cast<ExecuteSystemCommand*>(node);
		out << *derived;		
	}
	else	if( typeid(*node) == typeid(TextFileStorage) )
	{
		TextFileStorage* derived = static_cast<TextFileStorage*>(node);
		out << *derived;
	}
	else
	{
		// TODO throw error
		cout << "ERROR in Toolchain.cpp operator+= : typeid not found!\n"; 
	}

	// Loop over the child nodes of this parent and get their output stream.
	for( int i = 0; i < node->getNodeVectorSize(); i++ )
	{
		out += node->getChildNode(i);
	};
	
	return out;
	
};

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

