//
//	Author: A.L. Hertog
//	Date: 25 November 2008
//	License: GPL
//
//


#include "ToolchainNode.h"



//-----------------------------------------------------------------------------

ToolchainNode::ToolchainNode( ToolchainNode* parent )
{

	parentNode = parent;

	// Let the parent know it has a new child, unless parent == NULL which means it is a Toolchain object, the start of the chain.
	if( parent != NULL) parent->addNode( this );

};


//-----------------------------------------------------------------------------

ToolchainNode::~ToolchainNode()
{

	// Inform the parent and children of this node that it has died.
	
	// Inform the parent.
	if( this->getParentNode() != NULL )
	{
		(this->getParentNode())->removeNode( this );
	}
	
	
	// Inform the childeren of this node that it has died
	for( int i = 0; i < (int)nodeVector.size(); i++ )
	{
		nodeVector.at(i)->deleteParentNode();
	}
	
	
};


//-----------------------------------------------------------------------------

void ToolchainNode::addNode( ToolchainNode* node )
{
	nodeVector.push_back( node );
};

//-----------------------------------------------------------------------------

void ToolchainNode::addNode( ToolchainNode* node, int index )
{
	if( index >= nodeVector.size() )
	{
		this->addNode( node );
	}
	else
	{
		vector<ToolchainNode*>::iterator it = nodeVector.begin() + index;
		nodeVector.insert( it, node );
	}
};

//-----------------------------------------------------------------------------

void ToolchainNode::removeNode( ToolchainNode* node )
{
	for( int i = 0; i < (int)nodeVector.size(); i++ )
	{
		if( nodeVector.at(i) == node )
		{
			nodeVector.erase( nodeVector.begin()+i );
			i = (int)nodeVector.size(); // quite the loop
		}	
	}
};


//-----------------------------------------------------------------------------

void ToolchainNode::moveNodeUp( ToolchainNode* node )
{
	ToolchainNode* temp = NULL;

	for( int i = 0; i < (int)nodeVector.size(); i++ )
	{
		if( nodeVector.at(i) == node )
		{
			if( i != 0 )
			{
				// Store the upper element.
				temp = nodeVector.at(i-1);
				// Switch them.
				nodeVector.at(i-1) == node;
				nodeVector.at(i) == temp;
			}
			else	// node is the first object in the vector thus it cant be moved further up.
			{
				// Fill temp because it did find node thus no exception has to be thrown.
				temp = node;
			}
			i = (int)nodeVector.size(); // quite the loop
		}
	}
	
	// The switch was not performed
	if( temp == NULL )
	{
		// TODO throw
	}
};


//-----------------------------------------------------------------------------

void ToolchainNode::moveNodeDown( ToolchainNode* node )
{
	ToolchainNode* temp = NULL;

	for( int i = 0; i < (int)nodeVector.size(); i++ )
	{
		if( nodeVector.at(i) == node )
		{
			if( i != (int)nodeVector.size()-1 )
			{
				// Store the lower element.
				temp = nodeVector.at(i+1);
				// Switch them.
				nodeVector.at(i+1) == node;
				nodeVector.at(i) == temp;
			}
			else	// node is the first object in the vector thus it cant be moved further up.
			{
				// Fill temp because it did find node thus no exception has to be thrown.
				temp = node;
			}
			i = (int)nodeVector.size(); // quite the loop
		}
	}
	
	// The switch was not performed
	if( temp == NULL )
	{
		// TODO throw
	}
};


//-----------------------------------------------------------------------------

ToolchainNode* ToolchainNode::getChildNode( int index )
{
	return nodeVector.at( index );
};

//-----------------------------------------------------------------------------

int ToolchainNode::getNodeVectorSize()
{
	return (int)nodeVector.size();
};

//-----------------------------------------------------------------------------

ToolchainNode* ToolchainNode::getParentNode()
{
	return parentNode;
};

//-----------------------------------------------------------------------------

string ToolchainNode::getDescription()
{
	return description;
};

//-----------------------------------------------------------------------------

void ToolchainNode::setDescription( string descrip)
{
	description = descrip;
};

//-----------------------------------------------------------------------------

string ToolchainNode::getName()
{
	return name;
};

//-----------------------------------------------------------------------------

void ToolchainNode::setName( string n )
{
	name = n;
};

//-----------------------------------------------------------------------------

void ToolchainNode::deleteParentNode()
{
	parentNode = NULL;
};


//-----------------------------------------------------------------------------

string ToolchainNode::toString()
{
	string type = typeid(*this).name();
	string output = "Class type: \"\"" + type + "\"\"\nName: \"\"" + this->getName() + "\"\"\nDescription: \"\"" + this->getDescription() + "\"\"\n";
	return output;
};	


//-----------------------------------------------------------------------------

void ToolchainNode::fromString( string input )
{  
	size_t found_name, found_quote1, found_quote2, found_quote3, found_quote4, found_des;

	// Search for the name identifier
  found_name = input.find("Name: ");
  if( found_name != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote1 = input.find("\"\"", found_name+5 );
  	if( found_quote1 != string::npos )
  	{
  		// Search for the end quote
  		found_quote2 = input.find("\"\"", found_quote1+2 );
			if( found_quote2 != string::npos )
			{
				// Set the name of this object
				this->setName( input.substr( found_quote1+2, found_quote2-(found_quote1+2) ) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in ToolchainNode::fromString, line " << __LINE__ << ": unable to find quote 2 for name.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in ToolchainNode::fromString, line " << __LINE__ << ": unable to find quote 1 for name.\n";
  	} 	
  }
  else
  {
  	// TODO throw
  	cout << "WARNING in ToolchainNode::fromString line " << __LINE__ << ": no name found for object with input: \n\"" << input << "\"\n";
  }
  
	// Search for the description identifier
  found_des = input.find("Description: ");
  if( found_des != string::npos )
  {
  	// Search for quotes " and ' at the beginning of the name from where name was found
  	found_quote3 = input.find("\"\"", found_des+13 );
  	if( found_quote3 != string::npos )
  	{
  		// Search for the end quote
  		found_quote4 = input.find("\"\"", found_quote3+2 );
			if( found_quote4 != string::npos )
			{
				// Set the description of this object
				this->setDescription( input.substr( found_quote3+2, found_quote4-(found_quote3+2) ) );
			}
			else
			{
				// TODO throw
				cout << "ERROR in ToolchainNode::fromString, line " << __LINE__ << ": unable to find quote 4 for description.\n";
			} 	  		 		
  	}
  	else
  	{
  		// TODO throw
  		cout << "ERROR in ToolchainNode::fromString, line " << __LINE__ << ": unable to find quote 3 for description.\n";
  	} 	
  }	
  else
  {
  	// TODO throw
  	cout << "WARNING in ToolchainNode::fromString line " << __LINE__ << ": no description found for object with input: \n\"" << input << "\"\n";
  }  
  
};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

