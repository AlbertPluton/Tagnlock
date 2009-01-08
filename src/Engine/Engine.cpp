//
//	Author: A.L. Hertog
//	Date: 1 January 2009
//	License: GPL
//
//


#include "Engine.h"





//-----------------------------------------------------------------------------

Engine::Engine()
{
	// TODO
};

//-----------------------------------------------------------------------------

Engine::~Engine()
{

	categories.erase( categories.begin(), categories.end() );
	data.erase( data.begin(), data.end() );
	toolchains.erase( toolchains.begin(), toolchains.end() );

};

//-----------------------------------------------------------------------------

void Engine::addCategory( Category* cat )
{
	categories.push_back( cat );
	categoryModified.push_back( true );
};

//-----------------------------------------------------------------------------

Category* Engine::getCategory( int index )
{
	if( index >= 0 )
	{
		return categories.at( index );
	}
	else
	{
		return NULL;
	}
};

//-----------------------------------------------------------------------------

void Engine::deleteCategory( int index )
{
	categories.erase( categories.begin() + index );
	categoryModified.erase( categoryModified.begin() + index );
};

//-----------------------------------------------------------------------------

bool Engine::getCategoryModified( int index )
{
	return categoryModified.at( index );
};

//-----------------------------------------------------------------------------

void Engine::setCategoryModified( int index, bool mod )
{
	Engine::categoryModified.at( index ) = mod;
};


//-----------------------------------------------------------------------------

void Engine::addField( int indexCategory, Field* field )
{
		Category* cat = this->getCategory( indexCategory );
		cat->addField( field );
};


//-----------------------------------------------------------------------------

Field* getCurrentField()
{
	return currentField;
};

//-----------------------------------------------------------------------------

void setCurrentField( Field* field )
{
	currentField = field;
};


//-----------------------------------------------------------------------------

int Engine::getCurrentCategory()
{
	return currentCategory;
};

//-----------------------------------------------------------------------------
		
void Engine::setCurrentCategory( int index )
{
	currentCategory = index;
};



//=============================================================================


void Engine::addDatahandler( Datahandler* newData )
{
	data.push_back( newData );
	dataModified.push_back( true );
};

//-----------------------------------------------------------------------------

Datahandler* Engine::getDatahandler( int index )
{
	if( index >= 0 )
	{
		return data.at( index );
	}
	else
	{
		return NULL;
	}
};

//-----------------------------------------------------------------------------

void Engine::deleteDatahandler( int index )
{
	data.erase( data.begin() + index );
	dataModified.erase( dataModified.begin() + index );
};

//-----------------------------------------------------------------------------

bool Engine::getDataModified( int index )
{
	return dataModified.at( index );
};


//-----------------------------------------------------------------------------

void Engine::setDataModified( int index, bool mod )
{
	dataModified.at( index ) = mod;
};	


//-----------------------------------------------------------------------------

int Engine::getCurrentData()
{
	return currentData;
};

//-----------------------------------------------------------------------------

void Engine::setCurrentData( int index )
{
	currentData = index;
};



//=============================================================================


void Engine::addToolchain( Toolchain* chain )
{
	toolchains.push_back( chain );
	toolchainModified.push_back( true );
};

//-----------------------------------------------------------------------------

Toolchain* Engine::getToolchain( int index )
{
	if( index >= 0 )
	{
		return toolchains.at( index );
	}
	else
	{
		return NULL;
	}
};

//-----------------------------------------------------------------------------

void Engine::executeToolchain( int index )
{
	// Get a pointer to the desired toolchain.
	Toolchain* toolchain = toolchains.at( index );
	
	// Set the current Datahandler object as the input for the toolchain.
	toolchain->setInput( data.at( currentData ) );
	
	// Execute the toolchain.
	toolchain->execute();	
	
};

//-----------------------------------------------------------------------------

void Engine::deleteToolchain( int index )
{
	toolchains.erase( toolchains.begin() + index );
	toolchainModified.erase( toolchainModified.begin() + index );
};

//-----------------------------------------------------------------------------

bool Engine::getToolchainModified( int index )
{
	return toolchainModified.at( index );
};


//-----------------------------------------------------------------------------

void Engine::setToolchainModified( int index, bool mod )
{
	toolchainModified.at( index ) = mod;
};	

//-----------------------------------------------------------------------------

int Engine::getCurrentToolchain()
{
	return currentToolchain;
};

//-----------------------------------------------------------------------------

void Engine::setCurrentToolchain( int index )
{
	currentToolchain = index;
};

//-----------------------------------------------------------------------------

ToolchainNode* Engine::getCurrentToolchainNode()
{
	return currentToolchainNode;
};

//-----------------------------------------------------------------------------

void Engine::setCurrentToolchainNode( ToolchainNode* node )
{
	currentToolchainNode = node;
};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


