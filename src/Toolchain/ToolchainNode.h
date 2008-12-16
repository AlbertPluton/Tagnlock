//
//	Author: A.L. Hertog
//	Date: 25 November 2008
//	License: GPL
//
//

#ifndef TOOLCHAINNODE_H
#define TOOLCHAINNODE_H

#include <string>
#include <vector>
using namespace std;


//! A ToolchainNode object sibolizes the link between two operations (a ToolchainOberation object) or the start of the chain (a Toolchain object) and an operation. 

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
		
		//! Swamps the position of the node with its higher nightbour in the nodeVector.
		void moveNodeDown( ToolchainNode* node );
	
	
		//! Returns the parent node.
		ToolchainNode* getParentNode();
		
	
		//! This function is implemented in the childeren of the class.
		virtual void execute( ){};
		
		
		//! Get function for the description.
		string getDescription();
				
		//! Set function for the description.
		void setDescription( string descrip );
		
		
		//! Get function returning the name of this node.
		string getName();
		
		//! Set function for the name of this node.
		void setName( string n );
		
	
	
	private:
			
			vector<ToolchainNode*> nodeVector; 
			
			ToolchainNode* parentNode;
	
			string description;
			
			string name;

};









#endif









