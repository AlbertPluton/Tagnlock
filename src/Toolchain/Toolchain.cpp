//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//



#include "Toolchain.h"
#include <sstream>


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
		
		file << "NODE_ID: 0\n";
		file << this->toString() << "NODE_END\n\n";
		file << getChilderen( this, "0" );
		file.close();	
		
	}
	else
	{		
		// throw TODO 
		cout << "ERROR: Unable to open file for writing in Toolchain::saveToolchain.\n";
	}	
	

};

//-----------------------------------------------------------------------------

Toolchain* Toolchain::loadToolchain( string fileName )
{
	
	Toolchain* toolchain = NULL;

	size_t found;
	string inputString;
	string idString = "";
	bool foundID = false;
	bool foundTYPE = false;
	string typeString = "";
	bool foundEND = false;
	string nodeString = "";
	
	// Create file object.
	ifstream file;

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{

		while( !file.eof() )
		{
			getline(file, inputString);		

			// Only if we are not reading a node
			if( !( foundID && foundTYPE) )
			{
				// Delete comments
				string delimiter = "#";
				found = inputString.find_first_of( delimiter );
				if( found != string::npos ) inputString.erase( found, inputString.size() );

				// Delete whitespaces infront and after the data
				delimiter = " \t\n\r\v\f";
				found = inputString.find_first_not_of( delimiter );
				if( found != string::npos ) inputString.erase( 0, found );
				if( found == string::npos ) inputString.erase( 0, inputString.size() );
				found = inputString.find_last_not_of( delimiter );
				if( found != string::npos ) inputString.erase( found+1, inputString.size() );

				// If the string is empty continue with the next line.			
				if( inputString.empty() ) continue;	
			}
	
			// Search for an id
			found = inputString.find("NODE_ID: ", 0);	
			if( found!=string::npos )
			{
				inputString.erase(0, 9);
				idString = inputString;
				foundID = true;
				nodeString = "";	
				continue;
			}	
			
			// Find the node its class type 				
			found = inputString.find("Class type: ", 0);	
			if( found!=string::npos )
			{		
				inputString.erase(0, 12);
				size_t found_quote1 = inputString.find("\"\"");
				size_t found_quote2 = inputString.rfind("\"\"");				
				if( found_quote1 < found_quote2 )
				{
					typeString = inputString.substr( found_quote1+2, found_quote2 - (found_quote1+2)   );
					foundTYPE = true;
					continue; 				
				}
				else
				{
					// TODO throw
					cout << "ERROR in Toolchain::loadToolchain: unable to recover correct class type.\n";
				}

			}	
			
			
			
			// If a id and type has been found read the node description
			found = inputString.find("NODE_END", 0);
			if( found!=string::npos )
			{				
				if( !foundID )
				{
					// TODO throw
					cout << "ERROR in Toolchain::loadToolchain: found node END withoud ID.\n";
				}
				else if( !foundTYPE )
				{
					// TODO throw
					cout << "ERROR in Toolchain::loadToolchain: found node END withoud TYPE.\n";				
				}
				else
				{
					foundEND = true;
				}
				// By setting foundEND true within the else statements any invalid node will be skiped.		
			}	


			if( !foundEND && foundID && foundTYPE )
			{			
				// Add the line to the string describing the node
				nodeString = nodeString + inputString + "\n";
				continue;
			}				



			// Every thing is found thus lets create a new node
			if( foundEND && foundID && foundTYPE )
			{			
			
				// Create a new node
				if( typeString.compare( typeid(Toolchain).name() ) == 0 )
				{
					// make a Toolchain object 
					toolchain = new Toolchain();
					toolchain->fromString( nodeString );
				}
				else if( toolchain )				
				{
					// make a node in the toolchain
					toolchain->addNodeFromString( idString, typeString, nodeString );
				}
				else
				{
					// TODO throw
					cout << "ERROR in Toolchain::loadToolchain: found a node but not a toolchain node.\n";
				}
				
				// Reset the booleans
				foundID = false;
				foundTYPE = false;
				foundEND = false;
				
			}	
				
		}		

		// The end of the file has been reached but the END of the node has not been found.
		if( !foundEND && foundID && foundTYPE )
		{
			// TODO throw
			cout << "ERROR in Toolchain::loadToolchain: Unable to find END of node.\n";
		}
		
		file.close();	
		
	}
	else
	{		
		// throw TODO 
		cout << "ERROR: Unable to open file for reading in Toolchain::loadToolchain.\n";
	}	
	
	return toolchain;
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
	

string Toolchain::getChilderen( ToolchainNode* parent, string parentID)
{
	string output = "";
	string childID = "";
	ToolchainNode* child = NULL;
	
	// Loop over all the childeren of the parent.
	for( int i = 0; i < parent->getNodeVectorSize(); i++ )
	{
		// Obtain a pointer to the child.
		child = parent->getChildNode(i);
		
		
		// Create an id for the child
		stringstream ss;
		ss << i;
		childID =  parentID + ":" + ss.str();
		
		// Add the id and child descriptio to the output
		output = output + "NODE_ID: " + childID + "\n" + child->toString() + "NODE_END\n\n";
		
		// Obtain childeren of the child
		output = output + getChilderen( child, childID );
	}
	
	return output;
};


//-----------------------------------------------------------------------------

void Toolchain::addNodeFromString( string id, string type, string node )
{

	ToolchainNode* newNode = NULL;
	
	// Split the id string into parts and convert to integers.
	vector<int> idVec;
	size_t found = id.find(":");
	string subString;
	// Loop over the remaining id branches. 
	while( found != string::npos )
	{
		subString = id.substr(0, found-1 );
		idVec.push_back( atoi( subString.c_str() ) );
		id.erase(0, found+1);
		found = id.find(":");				
	}	
	// Push back the last id.
	idVec.push_back( atoi( id.c_str() ) );



	// Obtain the parent of the new node
	ToolchainNode* parent = this;
	for( int i = 1; i < idVec.size()-1; i++ )
	{
		// Check to see if the id is valid. If it is not larger to what is currently in the memory.
		if( i < parent->getNodeVectorSize() )
		{
			parent = parent->getChildNode(i);
		}
		else
		{
			// TODO throw
			cout << "ERROR in Toolchain::addNodeFromString: id incorrect: \"" << id << "\"\n";
		}
	};




	// Create the new node based on its type and node string.
	if( type.compare( typeid(ExecuteSystemCommand).name() ) == 0 )
	{
		ExecuteSystemCommand* commandNode = new ExecuteSystemCommand( parent );
		commandNode->fromString( node );
		newNode = commandNode;
	}
	else if( type.compare( typeid(TextFileStorage).name() ) == 0 )
	{
		TextFileStorage* storageNode = new TextFileStorage( parent );
		storageNode->fromString( node );
		newNode = storageNode;
	}
	else
	{
		// TODO throw error
		cout << "ERROR in Toolchain::addNodeFromString: Unkown node object type: \"" << type << "\".\n";
	}



	
	// Add the new node to the parent
	parent->addNode( newNode, idVec[idVec.size()-1] );


};
		
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

