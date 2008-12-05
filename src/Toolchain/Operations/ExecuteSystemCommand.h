//
//	Author: A.L. Hertog
//	Date: 28 November 2008
//	License: GPL
//
//

#ifndef EXECUTESYSTEMCOMMAND_H
#define EXECUTESYSTEMCOMMAND_H


#include <string>
#include <vector>
using namespace std;

#include "../ToolchainNode.h"
#include "../ToolchainOperation.h"

#include <cstdlib>

//! The ExecuteSystemCommand class is used to execute a system command.

class ExecuteSystemCommand : public ToolchainOperation
{

	public:

			//! The default constructor.	
			ExecuteSystemCommand( ToolchainNode* parent );
			
			//! Constructor with parameter
			/*!
				\param parent Pointer to the parent node of the object.
				\param comm The command itself.
			*/			
			ExecuteSystemCommand( ToolchainNode* parent, string comm );

			//! Constructor with parameters
			/*!
				\param parent Pointer to the parent node of the object.
				\param comm The command itself.
				\param args String with arguments. Spaces in the string are considered to be the end of an argument unless part of the string is in "", '' or a \\ is place in front of the white space. Otherwise the individual arguments are phrased in to the string vector arguments.	
			*/			
			ExecuteSystemCommand( ToolchainNode* parent, string comm, string args );
			
			//! Constructor with parameters
			/*!
				\param parent Pointer to the parent node of the object.
				\param comm The command itself.
				\param args Vector of arguments, each argument has its own vector element.			
			*/
			ExecuteSystemCommand( ToolchainNode* parent, string comm, vector<string> args );

	
			//! The default destructor.
			~ExecuteSystemCommand( );
			
			
			
			//! Execute the command with the arguments as defined in the vector arguments.
			void execute();
			
			//! Execute the command with additional arguments.
			void execute( string args );
			
			//! Execute the command with additional arguments.
			void execute( vector<string> args );
			
			
						
			//! Sets the command. This function overwrites the current command.
			void setCommand( string comm );
						
			//! Retuns a string with the current command.
			string getCommand( );			


			//! This function deletes all the old arguments and adds new.
			/*!
				\param args String with arguments. Spaces in the string are considered to be the end of an argument unless part of the string is in "", '' or a \\ is place in front of the white space. Otherwise the individual arguments are phrased in to the string vector arguments.	
			*/	
			void setArguments( string args );
			
			//! This function deletes all the old arguments and adds new.			
			void setArguments( vector<strings> args );
			
			//! Function to add arguments without deleting any existing arguments.
			/*!
				\param args String with arguments. Spaces in the string are considered to be the end of an argument unless that part of the string is place in "" or ''. Otherwise the individual arguments are phrased in to the string vector arguments.	
			*/				
			void addArguments( string args );			
			
			//! Function to add an argument without deleting any existing arguments.
			void addArguments( vector<string> args );				
			
			//! Function which can be used to delete an argument at the desired index.
			void deleteArgument( int index );
			
			//! Deletes the whole arguments vector.
			void deleteAllArguments( );
			
			//! Returns a string with the current arguments.
			string getArguments( );
			
			//! Retruns a string with the argument at the desired index.
			string getArgument( int index );			
	
	
	private:

		// The command itself. 
		string command;
		
		// Possible arguments to the command.
		vector<string> arguments;


		
		//! Convert a vector of strings to a signle string
		string vectorToString( vector<string>* vec );
		
		//! Convert a string with arguments in to a vector with a signle argument in each vector element.
		vector<string> stringToVector( string str ); 


};



#endif


