//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	License: GPL
//
//


#include "DataWindowGTKMM.h"



//-----------------------------------------------------------------------------

DataWindowGTKMM::DataWindowGTKMM(  int argc, char **argv, string gladeFileName ) : EngineGTKMM( argc, argv, gladeFileName )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing DataWindowGTKMM	object.\n";
#endif

	dataWindow = NULL;

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
  refXml->get_widget("DataWindow", dataWindow);
   
   
  if(dataWindow)
  {

		connectSignals();
    dataWindow->show();
 			 kit->run();
	}
	
	
};


//-----------------------------------------------------------------------------

DataWindowGTKMM::~DataWindowGTKMM()
{
	
	delete dataWindow;
	
};

//-----------------------------------------------------------------------------


void DataWindowGTKMM::connectSignals()
{

    //Get the Glade-instantiated Button, and connect a signal handler:
    Gtk::ToolButton* pToolButton = 0;


    // New button
    refXml->get_widget("toolbutton25", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    

		// Open button
    refXml->get_widget("toolbutton26", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Save button
		refXml->get_widget("toolbutton27", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Back button
    refXml->get_widget("toolbutton29", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::displayPreviousObjectData) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Forward button
    refXml->get_widget("toolbutton30", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::displayNextObjectData) );
    }
    else
    {
    	// TODO throw error
    }
    
  
 
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayDatahandlerObject()
{

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayNextDatahandler()
{

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousDatahandler()
{

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayNextObjectData()
{

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousObjectData()
{

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::readDataFromUI()
{

};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



