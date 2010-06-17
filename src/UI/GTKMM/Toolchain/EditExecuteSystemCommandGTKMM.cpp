//
//	Author: A.L. Hertog
//	Date: 22 October 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "EditExecuteSystemCommandGTKMM.h"




//-----------------------------------------------------------------------------

EditExecuteSystemCommandGTKMM::EditExecuteSystemCommandGTKMM( ToolchainNode* pNode )	:		EditToolchainNodeGTKMM( pNode ),
																																													labelCommand( "Command: ", 0.98, 0.5),
																																													labelArguments("Arguments: ", 0.98, 0.5)
{

	// Cast the base node pointer to a ExecuteSystemCommand object for easy acces.
	try
	{
		node = static_cast<ExecuteSystemCommand*>(pNode);
	}
	catch( exception& e )
	{
		throw e;
	}	
	

	// Add the command to the table
	this->attach( labelCommand, 0, 1, rows, rows+1, attachX, attachY );
	this->attach( entryCommand, 1, columns, rows, rows+1, attachX, attachY );
	entryCommand.set_text( node->getCommand() );
  entryCommand.set_tooltip_text("Enter a system command.");
	
	// Add the arguments to the table
	this->attach( labelArguments, 0, 1, rows+1, rows+2, attachX, attachY ); 
	this->attach( entryArguments, 1, columns, rows+1, rows+2, attachX, attachY );
	entryArguments.set_text( node->getArguments() );
  entryArguments.set_tooltip_text("Enter the arguments of the command here.");

	// Connect the signals
	entryCommand.signal_changed().connect( sigc::mem_fun( *this, &EditExecuteSystemCommandGTKMM::changedCommand ) );
	entryArguments.signal_changed().connect( sigc::mem_fun( *this, &EditExecuteSystemCommandGTKMM::changedArguments ) );
	
	
	this->show_all();
};


//-----------------------------------------------------------------------------

EditExecuteSystemCommandGTKMM::~EditExecuteSystemCommandGTKMM( )
{



};


//-----------------------------------------------------------------------------


void EditExecuteSystemCommandGTKMM::changedCommand()
{
	node->setCommand( entryCommand.get_text() );
	m_signal_changed.emit( );
};


//-----------------------------------------------------------------------------

void EditExecuteSystemCommandGTKMM::changedArguments()
{
	node->setArguments( entryArguments.get_text() );
	m_signal_changed.emit( );
};


//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------












