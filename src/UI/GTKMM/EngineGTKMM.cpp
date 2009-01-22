//
//	Author: A.L. Hertog
//	Date: 8 January 2009
//	License: GPL
//
//


#include "EngineGTKMM.h"


//-----------------------------------------------------------------------------

EngineGTKMM::EngineGTKMM( int argc, char **argv, string gladeFileName )
{


	kit = new Gtk::Main(argc, argv);

	dataWindow = 0;
	
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
  if(dataWindow)
  {

		connectSignalsToToolButtons();

		// TODO place the following function in a better place = other function.
    kit->run(*dataWindow);  
    delete dataWindow;
 
  }

	
};


//-----------------------------------------------------------------------------

EngineGTKMM::~EngineGTKMM()
{
	delete dataWindow;
};

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

void EngineGTKMM::newField( int indexCategory )
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


// --- Functions relating to Datahandler --------------------------------------
//-----------------------------------------------------------------------------

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




