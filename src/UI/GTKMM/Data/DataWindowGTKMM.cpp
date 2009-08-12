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
	displayWindow = NULL;
	displayFile	 = NULL;
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
  refXml->get_widget("alignment3", displayWindow);


	category = new CategoryGTKMM( );   
	if( category ) categoryScrolledWindow->add( (Gtk::Widget&)*category );

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
	delete displayWindow;
	delete displayFile;

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
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::newButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  

	// Open button
  refXml->get_widget("toolbutton26", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::openButton_clicked) );
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

  ObjectData* object = (this->getCurrentDatahandler())->getCurrentObject();

	if( (object != NULL) && true ) // TODO compare the category
	{	
		category->makeNewTable( object );
		category->fillTable( object );
	}


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
	// Only perform the action if there are multiple objects in the vector.
	if( currentData > 0 )
	{
		// A little abuse of the getNextObject function only to update the value of the current object in the datahandler.
		(this->getCurrentDatahandler())->getNextObject();

		this->displayDatahandlerObject();
	};
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousObjectData()
{
	// Only perform the action if there are multiple objects in the vector.
	if( currentData > 0 )
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

void DataWindowGTKMM::newButton_clicked()
{
#ifdef TODO_DEF
#warning TODO Make real code instead of test code in DataWindowGTKMM::newButton_clicked().
#endif

	// This is test code
	Category* cat = new Category();
	cat->loadCategory ("/home/bart/DMS_SVN/testSaveCategory.cat");
	this->addCategory(cat);

	Datahandler* datahandler = new Datahandler();
	this->addDatahandler( datahandler );
	datahandler->addNewObject( cat, "/home/bart/DMS_SVN/Test.pdf" );
	
	this->displayDatahandlerObject();
	
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::openButton_clicked()
{
	
	// Create a dialog to choose from which directory the sources files should be taken.
	Gtk::FileChooserDialog dialog( *dataWindow, "Please choose the source directory.", Gtk::FILE_CHOOSER_ACTION_OPEN); //Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER 	 );

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::NEW, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	
    	Glib::ustring result = dialog.get_uri();
			//Glib::ustring result = dialog.get_current_folder();
			string result_2 = result.raw();
			cout << result_2 << "\n";
      
      if( displayFile != NULL ) 
      {
      	displayWindow->remove();
      	delete displayFile;
      }
      displayFile = DisplayFile::getDisplay( result_2 );
      Gtk::Widget* widget = displayFile->getDisplayWidget();

			displayWindow->add( *widget );      

      displayWindow->show_all();
      
      
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


