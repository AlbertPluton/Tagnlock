//
//	Author: A.L. Hertog
//	Date: 7 October 2009
//	License: GPL
//
//

#include "ToolchainWindowGTKMM.h"

//-----------------------------------------------------------------------------

ToolchainWindowGTKMM::ToolchainWindowGTKMM(  int argc, char **argv, string gladeFileName ) : EngineGTKMM( argc, argv, gladeFileName )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing a ToolchainWindowGTKMM object.\n";
#endif

	toolchainWindow = NULL;
	treeView = NULL;
	textView = NULL;


  //Load the Glade file and instiate its widgets:
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
		try
		{
		  refXml = Gnome::Glade::Xml::create( gladeFileName );
		}
		catch(const Gnome::Glade::XmlError& ex)
		{
		  std::cerr << ex.what() << std::endl;
		  // TODO do something to exit, catch or throw.
		  //return 1;
		}
	#else
		std::auto_ptr<Gnome::Glade::XmlError> error;
		refXml = Gnome::Glade::Xml::create( gladeFileName, "", "", error);
		if(error.get())
		{
		  std::cerr << error->what() << std::endl;
		  // TODO do something to exit, catch or throw.
		  //return 1;
		}
	#endif	

	// Get the Glade-instantiated windows, dialogs, etc.
	refXml->get_widget("ToolchainWindow", toolchainWindow);
	refXml->get_widget("treeview1", treeView);
	refXml->get_widget("textview1", textView);
	
	if( treeView )
	{
		// Create the Tree model
		refTreeViewModel = Gtk::TreeStore::create(treeViewColumns);
		treeView->set_model(refTreeViewModel);

		// Append columns
		treeView->append_column( "Name", treeViewColumns.col_name );
		treeView->append_column( "Description", treeViewColumns.col_description );
	}
	else
	{
		// TODO throw
	}
	
  if(toolchainWindow)
  {
		connectSignals();
    toolchainWindow->show_all();
 		kit->run();
	};
}

//-----------------------------------------------------------------------------

ToolchainWindowGTKMM::~ToolchainWindowGTKMM( )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Destroying a ToolchainWindowGTKMM object.\n";
#endif	

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::connectSignals()
{

  //Get the Glade-instantiated Button, and connect a signal handler:
  Gtk::ToolButton* pToolButton = 0;


  // New button
  refXml->get_widget("toolbutton5", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::newButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }


  // Save button
  refXml->get_widget("toolbutton2", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::newButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  // Open button
  refXml->get_widget("toolbutton4", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::openButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Add button
  refXml->get_widget("toolbutton6", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::addButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Delete button
  refXml->get_widget("toolbutton7", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::deleteButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Up button
  refXml->get_widget("toolbutton12", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::upButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Down button
  refXml->get_widget("toolbutton13", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::downButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }    
  
  
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::dispalyToolchain( )
{


	Gtk::TreeModel::Row row;
	Toolchain* toolchain = NULL;
	ToolchainNode* node = NULL;
	
	// Loop over all the toolchains in the engine.
	for( int i = 0; i < this->getToolchainsSize(); i++ )
	{
		toolchain = this->getToolchain(i);
		for( int j = 0; i < toolchain->getNodeVectorSize(); i++ )
		{
					//--------------------------------------------------------------------------------------------------------------------------------------------------
		} 
	};
	
	
};

//-----------------------------------------------------------------------------


void ToolchainWindowGTKMM::addToolchainOperation()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::modifyToolchainNode()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::newButton_clicked()
{

};

		
//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::saveButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::openButton_clicked()
{
	// Create a dialog to load a toolchain from a file.
	Gtk::FileChooserDialog dialog( *toolchainWindow, "Please a toolchain file.", Gtk::FILE_CHOOSER_ACTION_OPEN); 

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	
    	string result_name = dialog.get_filename();
			cout << result_name << "\n";

			Toolchain* newToolchain = Toolchain::loadToolchain( result_name );
			this->addToolchain( newToolchain );
			this->dispalyToolchain();
     
      break;
    }
     default:
    {
      break;
    }	
	};
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::addButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::deleteButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::upButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::downButton_clicked()
{

};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

