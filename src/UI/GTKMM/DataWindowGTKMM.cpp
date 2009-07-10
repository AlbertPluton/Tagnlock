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
	categoryScrolledWindow = NULL;
	displayScrolledWindow = NULL;
	category = NULL;



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
  refXml->get_widget("scrolledwindow1", categoryScrolledWindow);
  refXml->get_widget("scrolledwindow4", displayScrolledWindow);

	category = new CategoryGTKMM( categoryScrolledWindow );   


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
	delete categoryScrolledWindow;
	delete displayScrolledWindow;

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

	this->readDataFromUI();

	if( true ) // TODO compare the category
	{	
		category->makeNewTable( (this->getCurrentDatahandler())->getCurrentObject() );
	}

	category->fillTable( (this->getCurrentDatahandler())->getCurrentObject() );

	categoryScrolledWindow->show_all();

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayNextDatahandler()
{
	// Only perform the action if there is a datahandler in the vector.
	if( currentData >= 0 )
	{
		currentData++;
		if( currentData < data.size() )	
		{
			this->displayDatahandlerObject();
		}
		else
		{
			currentData--;
		};
	};
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousDatahandler()
{
		currentData--;
		if( currentData >= 0 )
		{
			this->displayDatahandlerObject();
		}
		else
		{
			currentData++;
		};
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayNextObjectData()
{
	// Only perform the action if ther is a datahandler in the vector.
	if( currentData >= 0 )
	{
		// A little abuse of the getNextObject function only to update the value of the current object in the datahandler.
		(this->getCurrentDatahandler())->getNextObject();

		this->displayDatahandlerObject();
	};
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousObjectData()
{
	// Only perform the action if ther is a datahandler in the vector.
	if( currentData >= 0 )
	{
		// A little abuse of the getPreviousObject function only to update the value of the current object in the datahandler.
		(this->getCurrentDatahandler())->getPreviousObject();

		this->displayDatahandlerObject();
	};

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



