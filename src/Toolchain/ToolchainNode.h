//
//	Author: A.L. Hertog
//	Date: 25 November 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef TOOLCHAINNODE_H
#define TOOLCHAINNODE_H

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;


//! A ToolchainNode object symbolizes the link between two operations (a ToolchainOberation object) or the start of the chain (a Toolchain object) and an operation. 

class ToolchainNode
{
	
	public:
	
	
		//! The constructor. 
		/*!
			\param parent A pointer to the parent node is required as a parameter.
		*/
		ToolchainNode( ToolchainNode* parent );

		//! The constructor. 
		/*!
			\param parent A pointer to the parent node is required as a parameter.
			\param index The index at which the new node is placed within the list of the parent.
		*/
		ToolchainNode( ToolchainNode* parent, int index );

		//! The default destructor.
		~ToolchainNode();

	
	
		//! Adds a node object at the end of the nodeVector.
		void addNode( ToolchainNode* node );
		
		//! Adds a node object at the indicated index in the nodeVector.
		/*!
			Incase the index is larger than the nodeVector size, the new node is added at the end of the vector.
		*/
		void addNode( ToolchainNode* node, int index );
		
		//! Removes a node from the nodeVector
		/*!
			\returns true if the operation was successful.
		*/
		bool removeNode( ToolchainNode* node );
		
		
		//! Swamps the position of the node with its predecessor in the nodeVector.
		/*!
			\returns true if the operation was successful.
		*/
		bool moveNodeUp( );
		
		//! Swamps the position of the node with its higher neighbour in the nodeVector.
		/*!
			\returns true if the operation was successful.
		*/
		bool moveNodeDown( );
		
		//! Make this node a brother/sister of its current parent.
		/*!
			\returns true if the operation was successful.
		*/
		bool moveNodeLeft( );

		//! Make this node a child of the node above it.		
		/*!
			\returns true if the operation was successful.
		*/
		bool moveNodeRight( );
		
		//! Moves this node to a different parent specified by the newParent parameter. Childeren of this node are moved to. The node can be placed at a specified index.
		/*!
			\returns true if the operation was successful.
			\param newParent the new parent of this node.
			\param index the index at which this node is placed in the new parent vector. If left empty this node is placed at the end of the vector.
		*/
		bool changeParent( ToolchainNode* newParent, int index = -1 );
	
	
		//! Returns the child node at the number index in the nodeVector.
		ToolchainNode* getChildNode( int index );
				
		//! Returns the amount of childeren this node has.
		int getNodeVectorSize();
		
		//! Returns the index of this node within the vector of the parent. This function will return -1 if no parent was found.
		int getNodeIndex();
				
		//! Returns the parent node.
		ToolchainNode* getParentNode();
		
	
		//! This function is implemented in the children of the class.
		/*!
			\param onlyCurrentObject This boolean indicates wheter only the current object in the data handler should be executed.
		*/
		virtual void execute( bool onlyCurrentObject = false ){};
		
		
		//! Get function for the description.
		string getDescription();
				
		//! Set function for the description.
		void setDescription( string descrip );
		
		
		//! Get function returning the name of this node.
		string getName();
		
		//! Set function for the name of this node.
		void setName( string n );
		
		
		//! Returns the type of object.
		string getType();


		//! Convert the class to a string for saving or display purposes
		virtual string toString();		
		
		//! Set the variables of the class by description given in the string
		virtual void fromString( string input );


	protected:
	
		//! This function can be called in the derived execute function to execute the children of a node.
		virtual void executeChildren( bool onlyCurrentObject = false ){};


		//! This function is used by the parent class when it is destructed of the child node is removed from the nodeVector.
		void deleteParentNode();
		
		
		//! This vector holds all direct children nodes of this parent node.
		vector<ToolchainNode*> nodeVector; 
		
		ToolchainNode* parentNode;

		string description;
		
		string name;
		
		

};









#endif










