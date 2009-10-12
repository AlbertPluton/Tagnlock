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

	// Toolchain structure string
	string structure = "";

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{

		file << "Structure:\n";
		file << typeid(*this).name(); file << "\n";
		file << generateNodeStructure( this, "" );
		file << "End structure\n";
		
		file << "\n# Toolchain nodes:\n";
		file += this;


		file.close();	
		name = fileName;
	}
	else
	{		
		// throw TODO 
		cout << "Error in Toolchain::saveToolchain: Unable to open file " << fileName << "\n";
	}	


};

//-----------------------------------------------------------------------------

void Toolchain::loadToolchain( string fileName )
{
	string inputString;	
	bool structureStart = false;
	bool structureEnd = false;
	
	// Create file object.
	ifstream file;

	// Toolchain structure string
	string structure = "";

	// Open the file
	file.open( fileName.c_str() );
	
	if( file.is_open() )
	{

		while( !file.eof() && !structureEnd )
		{
						
			// throw TODO
			getline(file, inputString);		
			
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
			
			// Search for the start of a toolchain strucutre
			if( inputString.compare("Structure:") == 0 )
			{
				structureStart = true;
				continue;
			}			

			// Create the toolchain structure in memory.
			if( structureStart )
			{
				if( inputString.compare( typeid( TextFileStorage ).name() ) == 0 )
				{
					TextFileStorage node = new TextFileStorage 
				}
				else if( inputString.compare( ) == 0 )
				{
					node = new
				}
			
			}
			
			// The end of the structure has been found
			if( inputString.compare("End structure:") == 0 )
			{
				structureEnd = true;
			}

		};
		
		
		// Create the toolchain nodes from the structure

		file.close();	
		name = fileName;
	}
	else
	{		
		// throw TODO 
		cout << "Error in Toolchain::saveToolchain: Unable to open file " << fileName << "\n";
	}	
	
	
	
	
	
	
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

ostream& operator+= ( ostream& out, ToolchainNode* node )
{

	// Cast the node to its derived type and generate the output.
	if( typeid(*node) == typeid(Toolchain) )
	{
		//Toolchain* derived = static_cast<Toolchain*> node;
		out << *node; // Toolchain class has no << operator.
	}
	else 	if( typeid(*node) == typeid(ExecuteSystemCommand) )
	{
		ExecuteSystemCommand* derived = static_cast<ExecuteSystemCommand*>(node);
		out << *derived;		
	}
	else	if( typeid(*node) == typeid(TextFileStorage) )
	{
		TextFileStorage* derived = static_cast<TextFileStorage*>(node);
		out << *derived;
	}
	else
	{
		// TODO throw error
		cout << "ERROR in Toolchain.cpp operator+= : typeid not found!\n"; 
	}

	// Loop over the child nodes of this parent and get their output stream.
	for( int i = 0; i < node->getNodeVectorSize(); i++ )
	{
		out += node->getChildNode(i);
	};
	
	return out;
	
};

//-----------------------------------------------------------------------------

string Toolchain::generateNodeStructure( ToolchainNode* parent, string indent )
{
	string structure = "";
	ToolchainNode* child = NULL;
	
	indent += "\t";
	
	for( int i = 0; i < parent->getNodeVectorSize(); i++ )
	{
		child = parent->getChildNode(i);
		structure = structure + indent + typeid(*child).name() + "\n";
		structure += generateNodeStructure( child, indent );	
	};		
	
	return structure;
};
		
		
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

