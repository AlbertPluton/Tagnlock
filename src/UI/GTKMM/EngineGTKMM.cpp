//
//	Author: A.L. Hertog
//	Date: 8 January 2009
//	License: GPL
//
//


#include "EngineGTKMM.h"
#include <gtkmm/box.h>

//-----------------------------------------------------------------------------

EngineGTKMM::EngineGTKMM( int argc, char **argv, string gladeFileName )
{


	kit = new Gtk::Main(argc, argv);

	dataWindow = 0;
	toolchainWindow = 0;
	categoryWindow = 0;
	openDialog = 0;
	
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
	
	// Get the Glade-instantiated windows and dialogs.
	
	// Connect the signal handlers.
	
  //Get the Glade-instantiated Dialog:
  refXml->get_widget("DataWindow", dataWindow);
  refXml->get_widget("ToolchainWindow", toolchainWindow);
  refXml->get_widget("CategoryWindow", categoryWindow);
  
  refXml->get_widget("OpenDialog", openDialog);
  
  if(dataWindow && toolchainWindow && categoryWindow && openDialog)
  {

		connectSignalsToButtons();
		connectSignalsToToolButtons();

		// TODO place the following function in a better place = other function.
    dataWindow->show();
    categoryWindow->show();
    toolchainWindow->show();
    
    openDialog->hide();
    
    kit->run();
 		
	}

	
};


//-----------------------------------------------------------------------------

EngineGTKMM::~EngineGTKMM()
{
	delete dataWindow;
	delete toolchainWindow;
	delete categoryWindow;
	delete openDialog;
};

//-----------------------------------------------------------------------------

void EngineGTKMM::connectSignalsToButtons()
{
    //Get the Glade-instantiated Button, and connect a signal handler:
    Gtk::Button* pButton = 0;

		// OpenWindow =============================================================================================================

	  // Open button 
    refXml->get_widget("button1", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
		
	  // Cancel button
    refXml->get_widget("button2", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
		
}


//-----------------------------------------------------------------------------

void EngineGTKMM::connectSignalsToToolButtons()
{
    //Get the Glade-instantiated Button, and connect a signal handler:
    Gtk::ToolButton* pToolButton = 0;
    
    
    // DataWindow ===============================================================================================================
    
    // New button
    refXml->get_widget("toolbutton25", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    

		// Open button
    refXml->get_widget("toolbutton26", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Save button
		refXml->get_widget("toolbutton27", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Back button
    refXml->get_widget("toolbutton29", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::displayPreviousObjectData) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Forward button
    refXml->get_widget("toolbutton30", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::displayNextObjectData) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    
    // ToolchainWindow ===============================================================================================================
 
 
 
    // CategoryWindow ===============================================================================================================
   
    // New button
    refXml->get_widget("toolbutton14", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    

		// Open button
    refXml->get_widget("toolbutton15", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::loadCategory) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Save button
		refXml->get_widget("toolbutton16", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    } 
    
    // Undo button
		refXml->get_widget("toolbutton18", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }   

    // Redo button
		refXml->get_widget("toolbutton19", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }  
    
    
		// Add button
    refXml->get_widget("toolbutton21", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Delete button
		refXml->get_widget("toolbutton22", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    } 
    
    // Up button
		refXml->get_widget("toolbutton23", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }   

    // Down button
		refXml->get_widget("toolbutton24 ", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }        
      
   
}

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


void EngineGTKMM::on_toolbutton25_clicked(  )
{

	cout << "Pressed ToolButton25\n";

  //if(dataWindow)
    //dataWindow->hide(); //hide() will cause main::run() to end.
    
}

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------







// === The following functions are implementations of the virtual functions in the Engine class ====================
	
// --- Functions relating to Category -----------------------------------------

void EngineGTKMM::loadCategory()
{
	
	openDialog->show();
};

//-----------------------------------------------------------------------------

void EngineGTKMM::saveCategory()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::newField()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::modifyField()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::displayCategory( int index )
{

};



//-----------------------------------------------------------------------------

// --- Functions relating to Datahandler --------------------------------------

void EngineGTKMM::displayDatahandlerObject( )
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::displayNextDatahandler()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::displayPreviousDatahandler()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::displayNextObjectData()
{

};



//-----------------------------------------------------------------------------

void EngineGTKMM::displayPreviousObjectData()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::readDataFromUI()
{

};


//-----------------------------------------------------------------------------
// --- Functions relating to Toolchain ----------------------------------------

void EngineGTKMM::dispalyToolchain( )
{

};

//-----------------------------------------------------------------------------


void EngineGTKMM::addToolchainOperation()
{

};

//-----------------------------------------------------------------------------

void EngineGTKMM::modifyToolchainNode()
{

};

//-----------------------------------------------------------------------------












//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------




