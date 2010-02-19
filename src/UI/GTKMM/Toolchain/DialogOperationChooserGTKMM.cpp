//
//	Author: A.L. Hertog
//	Date: 15 October 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "DialogOperationChooserGTKMM.h"


//-----------------------------------------------------------------------------

DialogOperationChooserGTKMM::DialogOperationChooserGTKMM( Gtk::Window* parent )	: 
																																									Dialog( "Select an operation node", parent ),
																																									radioTextFileStorage("Text file storage"),
																																									radioExecuteSystemCommand("System command")
{
	
	// Request a minimum with
	this->set_size_request( 250 ); 
	
	// Put the radio buttons in the same group.
	Gtk::RadioButtonGroup group = radioTextFileStorage.get_group();
	radioExecuteSystemCommand.set_group( group );
	
	// Place the radio buttons in the dialog.
	Gtk::VBox* vBox = this->get_vbox();
	vBox->pack_start( radioTextFileStorage );
	vBox->pack_start( radioExecuteSystemCommand );
	
	// Add buttons
	this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
 	this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	
	show_all();

};


//-----------------------------------------------------------------------------

DialogOperationChooserGTKMM::~DialogOperationChooserGTKMM( )
{

};		


//-----------------------------------------------------------------------------

void DialogOperationChooserGTKMM::chooseOperationNode( ToolchainNode* parent )
{
	this->chooseOperationNode( parent, parent->getNodeVectorSize() );
};

//-----------------------------------------------------------------------------

void DialogOperationChooserGTKMM::chooseOperationNode( ToolchainNode* parent, int index )
{
	
	// Display the dialog and obtain the result. 
	int result = this->run();
	
  //Handle the response
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {		
    
    	if( radioTextFileStorage.get_active() )
    	{
    		// Create a TextFileStorage object
    		TextFileStorage* node = new TextFileStorage( parent, index );
    		
    		// Add some default values
    		node->setName( "Text file storage" );
    		node->setDescription( "Describe me" );
    		node->setLocation( "../" );
    		node->setFileName( "File_name" );
    		
    	}
    	else if( radioExecuteSystemCommand.get_active() )
    	{
    		// Create a ExecuteSystemCommand object
    		ExecuteSystemCommand* node = new ExecuteSystemCommand( parent, index );

    		// Add some default values
    		node->setName( "System command" );
    		node->setDescription( "Describe me" );
    		node->setCommand( "Enter command here" );	
    		    		
    	}
    	else
    	{
    		// TODO throw
    		cout << "ERROR in DialogOperationChooserGTKMM::chooseOperationNode: unknown radio button selection.\n";
    	}
    	
      break;
    }
     default:
    {
      break;
    }	
	};	
	
};


//-----------------------------------------------------------------------------







//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------








//-----------------------------------------------------------------------------






//-----------------------------------------------------------------------------






//-----------------------------------------------------------------------------
















