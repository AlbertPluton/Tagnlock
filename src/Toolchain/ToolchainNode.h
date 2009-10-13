//
//	Author: A.L. Hertog
//	Date: 25 November 2008
//	License: GPL
//
//

#ifndef TOOLCHAINNODE_H
#define TOOLCHAINNODE_H

#include <iostream>
#include <string>
#include <vector>
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

		//! The default destructor.
		~ToolchainNode();

	
	
		//! Adds a node object at the end of the nodeVector.
		void addNode( ToolchainNode* node );
		
		//! Removes a node from the nodeVector
		void removeNode( ToolchainNode* node );
		
		
		//! Swamps the position of the node with its predecessor in the nodeVector.
		void moveNodeUp( ToolchainNode* node );
		
		//! Swamps the position of the node with its higher neighbour in the nodeVector.
		void moveNodeDown( ToolchainNode* node );
	
		//! Returns the child node at the number index in the nodeVector.
		ToolchainNode* getChildNode( int index );
				
		//! Returns the amount of childeren this node has.
		int getNodeVectorSize();
				
		//! Returns the parent node.
		ToolchainNode* getParentNode();
		
	
		//! This function is implemented in the children of the class.
		virtual void execute( ){};
		
		
		//! Get function for the description.
		string getDescription();
				
		//! Set function for the description.
		void setDescription( string descrip );
		
		
		//! Get function returning the name of this node.
		string getName();
		
		//! Set function for the name of this node.
		void setName( string n );
		


	protected:
	
		//! This function can be called in the derived execute function to execute the children of a node.
		virtual void executeChildren(){};

	
			//! This function is used by the parent class when it is destructed of the child node is removed from the nodeVector.
			void deleteParentNode();
			
			
			//! This vector holds all direct children nodes of this parent node.
			vector<ToolchainNode*> nodeVector; 
			
			ToolchainNode* parentNode;
	
			string description;
			
			string name;
			
		

};









#endif










