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

ostream& operator<< (ostream& out, const ToolchainNode& node)
{
	out << node.name << '\n';
	out << node.description << endl;
	return out;	
};

//-----------------------------------------------------------------------------

istream& operator>> (istream& in, ToolchainNode& node)
{
	in >> node.name;
	in >> node.description;
	return in;
};

//-----------------------------------------------------------------------------

void ToolchainNode::deleteParentNode()
{
	parentNode = NULL;
};


//-----------------------------------------------------------------------------



