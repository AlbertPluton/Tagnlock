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
	currentCategory = -1;
	currentField = -1;
	currentData = -1;
	currentToolchain = -1;
	currentToolchainNode = NULL;

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
	this->setCurrentCategory( this->getNumberOfCategories() - 1 );
};

//-----------------------------------------------------------------------------

Category* Engine::getCurrentCategory( )
{
	if( currentCategory >= 0 ) return categories.at( currentCategory );
	else return NULL;
}

//-----------------------------------------------------------------------------

Category* Engine::getCategory( int index )
{
	if( (index >= 0) && (index < categories.size()) )
	{
		return categories.at( index );
	}
	else
	{
		// TODO throw
		return NULL;
	}
};


//-----------------------------------------------------------------------------

int Engine::getCategoriesSize()
{
	return categories.size();
};

//-----------------------------------------------------------------------------

void Engine::deleteCategory( int index )
{
	if( (index >= 0) && (index < categories.size()) )
	{	
		categories.erase( categories.begin() + index );
		categoryModified.erase( categoryModified.begin() + index );
	}
	else
	{
		// TODO throw
	}
};

//-----------------------------------------------------------------------------

bool Engine::getCategoryModified( int index )
{
	if( (index >= 0) && (index < categoryModified.size()) )
	{
		return categoryModified.at( index );
	}
	else
	{	
		// TODO throw
		return false;
	}
	
};

//-----------------------------------------------------------------------------

void Engine::setCategoryModified( int index, bool mod )
{
	if( (index >= 0) && (index < categoryModified.size()) )
	{	
		Engine::categoryModified.at( index ) = mod;
	}
	else
	{	
		// TODO throw
	}
};


//-----------------------------------------------------------------------------

void Engine::addField( int indexCategory, Field* field )
{
	if( (indexCategory >= 0) && (indexCategory < categories.size()) )
	{
		Category* cat = categories[ indexCategory ];
		cat->addField( field );
	}
	else
	{
		// TODO throw
	}
};


//-----------------------------------------------------------------------------

int Engine::getIndexCurrentField()
{
	return currentField;
};

//-----------------------------------------------------------------------------

Field* Engine::getCurrentField()
{
	return getCurrentCategory()->getFieldAt( currentField );
};

//-----------------------------------------------------------------------------

void Engine::setCurrentField( int field )
{
	currentField = field;
};

//-----------------------------------------------------------------------------

int Engine::getNumberOfCategories()
{
	return categories.size();
};

//-----------------------------------------------------------------------------

int Engine::getIndexCurrentCategory()
{
	return currentCategory;
};

//-----------------------------------------------------------------------------
		
void Engine::setCurrentCategory( int index )
{
	if( (index >= 0) && (index < categories.size()) )
	{	
		currentCategory = index;
	}
	else
	{
		//TODO throw
	}
};



//=============================================================================


void Engine::addDatahandler( Datahandler* newData )
{
	data.push_back( newData );
	dataModified.push_back( true );
	currentData = data.size()-1;
};

//-----------------------------------------------------------------------------

Datahandler* Engine::getCurrentDatahandler( )
{
	return data.at( currentData );
};

//-----------------------------------------------------------------------------


Datahandler* Engine::getDatahandler( int index )
{
	if( (index >= 0) && (index < data.size()) )
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
	if( (index >= 0) && (index < data.size()) )
	{
		data.erase( data.begin() + index );
		dataModified.erase( dataModified.begin() + index );
	}
	else
	{
		//TODO throw
	}	
};

//-----------------------------------------------------------------------------

bool Engine::getDataModified( int index )
{
	if( (index >= 0) && (index < dataModified.size()) )
	{
		return dataModified.at( index );
	}
	else
	{	
		// TODO throw
		return false;
	}
};


//-----------------------------------------------------------------------------

void Engine::setDataModified( int index, bool mod )
{
	if( (index >= 0) && (index < dataModified.size()) )
	{
		dataModified.at( index ) = mod;
	}	
	else
	{	
		// TODO throw
	}
};	


//-----------------------------------------------------------------------------

int Engine::getCurrentData()
{
	return currentData;
};

//-----------------------------------------------------------------------------

void Engine::setCurrentData( int index )
{
	if( (index >= 0) && (index < data.size()) )
	{
		currentData = index;
	}
	else
	{
		// TODO throw
	}
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
	if( (index >= 0) && (index < toolchains.size()) )
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
	if( (index >= 0) && (index < toolchains.size()) )
	{	
		// Get a pointer to the desired toolchain.
		Toolchain* toolchain = toolchains.at( index );
	
		// Set the current Datahandler object as the input for the toolchain.
		toolchain->setInput( data.at( currentData ) );
	
		// Execute the toolchain.
		toolchain->execute();	
	}
	else
	{
		// TODO throw
	}
};

//-----------------------------------------------------------------------------

void Engine::deleteToolchain( int index )
{
	if( (index >= 0) && (index < toolchains.size()) )
	{
		toolchains.erase( toolchains.begin() + index );
		toolchainModified.erase( toolchainModified.begin() + index );
	}
	else
	{
		// TODO throw
	}
};

//-----------------------------------------------------------------------------

bool Engine::getToolchainModified( int index )
{
	if( (index >= 0) && (index < toolchainModified.size()) )
	{
		return toolchainModified.at( index );
	}
	else
	{
		// TODO throw
	}
};


//-----------------------------------------------------------------------------

void Engine::setToolchainModified( int index, bool mod )
{
	if( (index >= 0) && (index < toolchainModified.size()) )
	{
		toolchainModified.at( index ) = mod;
	}
	else
	{
		// TODO throw
	}
};	

//-----------------------------------------------------------------------------

int Engine::getCurrentToolchain()
{
	return currentToolchain;
};

//-----------------------------------------------------------------------------

void Engine::setCurrentToolchain( int index )
{
	if( (index >= 0) && (index < toolchains.size()) )
	{
		currentToolchain = index;
	}
	else
	{
		// TODO throw
	}
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


