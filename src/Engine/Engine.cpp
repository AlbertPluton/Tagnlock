//
//	Author: A.L. Hertog
//	Date: 1 January 2009
//	License: GPL
//
//


#include "Engine.h"

#include "URIobject.h"



//-----------------------------------------------------------------------------

Engine::Engine() : Configuration( "Engine" )
{		
	currentCategory = -1;
	currentField = -1;
	currentDatahandler = -1;
	currentToolchain = -1;
	currentToolchainNode = NULL;


	// Connect the signal of the Configuration base class to go parse.
	signal_parse().connect( sigc::mem_fun(this, &Engine::parseToConfig) );


	// Extract configuration data from the map
	this->updateFromConfig();

	// TODO 28092009 what is there todo??

};

//-----------------------------------------------------------------------------

Engine::~Engine()
{

	categories.erase( categories.begin(), categories.end() );
	data.erase( data.begin(), data.end() );
	toolchains.erase( toolchains.begin(), toolchains.end() );

};





//-----------------------------------------------------------------------------
// --- Functions relating to the general program flow -------------------------

void Engine::loadConfiguration()
{

};


//-----------------------------------------------------------------------------

void Engine::saveConfiguration()
{


};


//-----------------------------------------------------------------------------
// --- Functions relating to Category -----------------------------------------


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

vector<Category*>* Engine::getCatVec()
{
	return &categories;
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

void Engine::deleteField()
{
	// Get the category from which the field will be deleted
	Category* cat = this->getCurrentCategory();
	
	if( cat )
	{
		// Get the index of the field to delete.
		int index = this->getIndexCurrentField();
		
		// Check for a valid index.
		if( index > -1 )
		{
			// Delete the field
			cat->deleteField( index );
			
			currentField = -1;
		}
	}
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
	currentDatahandler = data.size()-1;
};

//-----------------------------------------------------------------------------

Datahandler* Engine::getCurrentDatahandler( )
{
	return data.at( currentDatahandler );
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
	
	// If the deleted item is the current datahandler, set the currentDatahandler to the last handler in the vector
	if( index == currentDatahandler ) currentDatahandler = data.size() - 1;
};

//-----------------------------------------------------------------------------

bool Engine::getDatahandlerModified( int index )
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

void Engine::setDatahandlerModified( int index, bool mod )
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

int Engine::getCurrentDatahandlerIndex()
{
	return currentDatahandler;
};

//-----------------------------------------------------------------------------

void Engine::setCurrentDatahandler( int index )
{
	if( (index >= 0) && (index < data.size()) )
	{
		currentDatahandler = index;
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
	currentToolchain = toolchains.size()-1;
	toolchainModified.push_back( true );
};

//-----------------------------------------------------------------------------

Toolchain* Engine::getToolchain( int index )
{
	if( (index >= 0) && (index < toolchains.size()) )
	{
		return toolchains[index];
	}
	else
	{
		return NULL;
	}
};

//-----------------------------------------------------------------------------

Toolchain* Engine::getCurrentToolchain( )
{
	if( (currentToolchain >= 0) && (currentToolchain < toolchains.size()) )
	{
		return toolchains[currentToolchain];
	}
	else
	{
		return NULL;
	}		
};		


//-----------------------------------------------------------------------------

int Engine::getToolchainsSize()
{
	return toolchains.size();
};

//-----------------------------------------------------------------------------

void Engine::executeToolchain( int index )
{
	if( (index >= 0) && (index < toolchains.size()) )
	{	
		// Get a pointer to the desired toolchain.
		Toolchain* toolchain = toolchains.at( index );
	
		// Set the current Datahandler object as the input for the toolchain.
		toolchain->setInput( data.at( currentDatahandler ) );
	
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

int Engine::getCurrentToolchainIndex()
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
	if( node != NULL )
	{
		currentToolchainNode = node;
		
		// search for the toolchain object
		ToolchainNode* searchNode = node;		
		while( searchNode->getParentNode() != NULL ) // If the parent is not NULL get the parent and search on.
		{
			searchNode = searchNode->getParentNode();
		};
		
		// The parent was NULL lets see if this is really a Toolchain object
		if( typeid(*searchNode) == typeid(Toolchain) )
		{
			// So we have the toolchain object
			// Lets see if we can find in in the toolchain vector
			int i = 0;
			bool found = false;
			while( !found && (i < toolchains.size()) )
			{
				if( searchNode == toolchains[i] )
				{
					// We found the same toolchain object.
					found = true;
				}
				else
				{
					// No result jet continue iterating.
					i++;
				}
			}
			
			if( found )
			{
				// We found the index, lets set the current toolchain index to this value.
				this->setCurrentToolchain(i);
			}
			else
			{
				// We have NOT found the desired toolchain in the vectro. 
				// TODO throw
				cout << "ERROR in Engine::setCurrentToolchainNode: unable to find Toolchain object in toolchains vector.\n";			
			}
					
		}
		else
		{
			// TODO throw
			cout << "ERROR in Engine::setCurrentToolchainNode: unable to find parent Toolchain object.\n";
		} 
		
	};
};


//=============================================================================
//-----------------------------------------------------------------------------

void Engine::parseToConfig()
{
	// create a string with all Category locations
	if( categories.size() )
	{
		string catLoc = "";
		for( int i = 0; i < categories.size(); i++ ) catLoc += categories[i]->getFileName() + ";";
		setPair<string>( "catLoc", catLoc );
	};
	
	// create a string with all Toolchain locations
	if( toolchains.size() > 0 )
	{
		string toolLoc = "";
		for( int i = 0; i < toolchains.size(); i++ ) toolLoc += toolchains[i]->getFileName() + ";";
		setPair<string>( "toolLoc", toolLoc );
	};
	
	// create a string with all Datahandler locations
	if( data.size() > 0 )
	{
		string dataLoc = "";
		for( int i = 0; i < data.size(); i++ ) dataLoc += data[i]->getName() + ";";
		setPair<string>( "dataLoc", dataLoc );
	};
	
};

//-----------------------------------------------------------------------------

void Engine::updateFromConfig()
{

	string catLoc = "";
	string toolLoc = "";
	string dataLoc = "";

	try
	{
		// Get the category locations
		catLoc = getData<string>( "catLoc" );
		// Get the toolchain locations
		toolLoc = getData<string>( "toolLoc" );
		// Get the datahandler locations
		dataLoc = getData<string>( "dataLoc" );			
	}
	catch( exception& e )
	{
		// TODO handle exception
		cout << "ERROR in Engine::updateFromMap\n";
	}
	
	// Go search for different locations in the loc strings
	size_t found;
	
	// Do the categories
	Category* cat = NULL;
	found = catLoc.find(";");
	while( found != string::npos ) 
	{
		cat = new Category();
		cat->loadCategory( catLoc.substr(0, found) );
		this->addCategory( cat);
		catLoc.erase(0, found+1);
		found = catLoc.find(";");
	}
	
	// Do the toolchains
	found = toolLoc.find(";");
	Toolchain* tool = NULL;
	while( found != string::npos ) 
	{
		tool = Toolchain::loadToolchain( toolLoc.substr(0, found) );
		this->addToolchain( tool );
		toolLoc.erase(0, found+1);		
		found = toolLoc.find(";");
	}	
	
	// Do the toolchains
	found = dataLoc.find(";");
	Datahandler* pData = NULL;
	while( found != string::npos ) 
	{
		string fileName = dataLoc.substr(0, found);
		pData = new Datahandler();
		pData->load( fileName, this->getCatVec() ); // TODO do some error checking on all load processes.	
		dataLoc.erase(0,found+1);
		found = dataLoc.find(";");
	};
	
};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


