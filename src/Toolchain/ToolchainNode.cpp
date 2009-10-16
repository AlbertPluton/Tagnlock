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

ToolchainNode::ToolchainNode( ToolchainNode* parent, int index )
{
	parentNode = parent;

	// Let the parent know it has a new child, unless parent == NULL which means it is a Toolchain object, the start of the chain.
	if( parent != NULL) parent->addNode( this, index );
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
	if( (index >= nodeVector.size()) || (index == -1) )
	{
		this->addNode( node );
	}
	else
	{
		vector<ToolchainNode*>::iterator it = nodeVector.begin() + index;
		nodeVector.insert( nodeVector.begin() + index, node );
	}
};

//-----------------------------------------------------------------------------

bool ToolchainNode::removeNode( ToolchainNode* node )
{
	for( int i = 0; i < this->getNodeVectorSize(); i++ )
	{
		if( nodeVector.at(i) == node )
		{
			nodeVector.erase( nodeVector.begin()+i );
			return true;
		}	
	}
	return false;
};


//-----------------------------------------------------------------------------

bool ToolchainNode::moveNodeUp( )
{
	ToolchainNode* temp = NULL;
	
	ToolchainNode* parent = this->getParentNode();

	if( parent )
	{
	
		for( int i = 0; i < parent->nodeVector.size(); i++ )
		{
			if( parent->nodeVector[i] == this )
			{
				if( i != 0 )
				{
					// Store the upper element.
					temp = parent->nodeVector[i-1];
					// Switch them.
					parent->nodeVector[i-1] = this;
					parent->nodeVector[i] = temp;
				}
				else	// this node is the first object in the vector thus it cant be moved further up.
				{
					// Fill temp because it did find node thus no exception has to be thrown.
					temp = this;
				}

				return true;
			}
		}

		// The switch was not performed
		if( temp == NULL )
		{
			// TODO throw

		}
		
	};
	
	return false;
};


//-----------------------------------------------------------------------------

bool ToolchainNode::moveNodeDown( )
{
	ToolchainNode* temp = NULL;
	
	ToolchainNode* parent = this->getParentNode();

	if( parent )
	{
	
		for( int i = 0; i < parent->nodeVector.size(); i++ )
		{
			if( parent->nodeVector[i] == this )
			{
				if( i != (int)parent->nodeVector.size()-1 )
				{
					// Store the lower element.
					temp = parent->nodeVector[i+1];
					// Switch them.
					parent->nodeVector[i+1] = this;
					parent->nodeVector[i] = temp;
				}
				else	// node is the first object in the vector thus it cant be moved further up.
				{
					// Fill temp because it did find node thus no exception has to be thrown.
					temp = this;
				}
				
				return true;
			}
		}
	
		// The switch was not performed
		if( temp == NULL )
		{
			// TODO throw
		}

	};
	
	return false;

};

//-----------------------------------------------------------------------------

bool ToolchainNode::moveNodeLeft( )
{
	
	ToolchainNode* oldParent = this->getParentNode();
	
	// Check to see if this is not the first node aka a Toolchain object.
	if( oldParent )
	{
		
		ToolchainNode* newParent = oldParent->getParentNode();
		
		// See if the new parent excists, if so change parent
		if( newParent ) 
		{	
			if( this->changeParent( newParent, newParent->getNodeIndex() + 1 ) )	return true;
		}
	
	
	}
	
	return false;
};


//-----------------------------------------------------------------------------

bool ToolchainNode::moveNodeRight( )
{
	// See if this is not the first object in the toolchain
	ToolchainNode* parent = this->getParentNode();
	if( parent )
	{
		
		// Search for the index of this node in the vector, but exclude the first node because he has no node above him to make the new parent.
		for( int i = 1; i < parent->getNodeVectorSize(); i++ )
		{
			if( parent->getChildNode(i) == this )
			{
				// Make the brother/sister above this node the parent of it.
				if( this->changeParent( parent->getChildNode(i-1) ) ) return true;
				break; // no need to loop further on.
			}
		}
	
	}
	return false;
};


//-----------------------------------------------------------------------------

bool ToolchainNode::changeParent( ToolchainNode* newParent, int index )
{

	if( newParent )
	{
		// Get the old/current parent.
		ToolchainNode* oldParent = this->getParentNode();
		
		// If there is no old parent it mostlikely meas this is a Toolchain object.
		if( oldParent )
		{
			// Set the new parent of this node
			this->parentNode = newParent;
			
			// Add the node to the new parent
			newParent->addNode( this, index );
			
			// Remove this node from the old parent
			oldParent->removeNode( this );
						
			return true;
		}
	}

	return false;
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

int ToolchainNode::getNodeIndex()
{
	ToolchainNode* parent = this->getParentNode();
	if( parent )
	{
		int i = 0;
		bool found = false;
		
		// Loop over all the childeren of the parent
		while( !found && (i < parent->getNodeVectorSize()) )
		{
			if( this == parent->getChildNode(i) ) 
			{
				found = true;
			}
			else
			{
				i++; 
			}
		}
		
		if( found ) return i;
		
	}
	else
	{
		return -1;
	}
	return -1;
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

