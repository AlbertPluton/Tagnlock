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
	cout << "Constructing a DataWindowGTKMM object.\n";
#endif

	dataWindow = NULL;
	categoryScrolledWindow = NULL;
	displayWindow = NULL;
	displayFile	 = NULL;
	category = NULL;
	comboDatahandlers = NULL;
	comboFilesTodo = NULL;

	// Used to place the datahandler and todo files combo.
	Gtk::Table* comboTable = NULL;


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
  refXml->get_widget("table1", comboTable);
	datahandlerAssistant = new DataAssistantGTKMM( this );


	if( comboTable )
	{
	
		comboDatahandlers = new Gtk::ComboBoxText();
		comboFilesTodo = new Gtk::ComboBoxText();
	
		comboTable->attach( *comboDatahandlers, 1, 2, 0, 1 );
		comboTable->attach( *comboFilesTodo, 1, 2, 1, 2 );
	
		comboDatahandlers->signal_changed().connect(sigc::mem_fun(*this, &DataWindowGTKMM::comboDatahandlers_changed));
		comboFilesTodo->signal_changed().connect(sigc::mem_fun(*this, &DataWindowGTKMM::comboFilesTodo_changed));
	}
	else
	{
		// TODO Faild to obtain table.
	}


	category = new CategoryGTKMM( );   
	if( category ) categoryScrolledWindow->add( (Gtk::Widget&)*category );
//	categoryScrolledWindow->show_all();


  if(dataWindow)
  {

		connectSignals();
    dataWindow->show_all();
		datahandlerAssistant->hide_all();
 		kit->run();
	}
	
	
};


//-----------------------------------------------------------------------------

DataWindowGTKMM::~DataWindowGTKMM()
{
#ifdef DEBUG_MESSAGES_DEF
	cout << "Destroying a DataWindowGTKMM object.\n";
#endif	

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
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::saveButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  // Save as button
	refXml->get_widget("toolbutton33", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::saveAsButton_clicked) );
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

  ObjectData* object = (this->getCurrentDatahandler())->getCurrentObject();
	Category* cat1 = object->getCategory();
	Category* cat2 = NULL;
	if( category->getObjectData() ) cat2 = (category->getObjectData())->getCategory(); // THe objectData from category might be NULL for the first datahandler.

	if( (object != NULL) ) 
	{	
		// If the two categories are not the same, make a new table.
		if( cat1 != cat2 )
		{
			category->makeNewTable( object );
		};
		category->fillTable( object );

    if( displayFile != NULL ) 
    {
    	displayWindow->remove();
    	delete displayFile;
    }

    displayFile = DisplayFile::getDisplay( *(object->getObjectName()) );
    Gtk::Widget* widget = displayFile->getDisplayWidget();
		displayWindow->add( *widget );      
    displayWindow->show_all();

		// Update the current datahandler combo
		comboFilesTodo->set_active( (this->getCurrentDatahandler())->getPosition()-1 );

	}


	categoryScrolledWindow->show_all();

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayNextDatahandler()
{


	// Only perform the action if there is a datahandler in the vector.
	if( currentDatahandler >= 0 )
	{
		// Read data enterd by the user incase we are going to display an other object.
		this->readDataFromUI();

		currentDatahandler++;
		if( currentDatahandler < data.size() )	
		{
			this->displayDatahandlerObject();
		}
		else
		{
			currentDatahandler--;
		};
	};
	
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousDatahandler()
{

	if( currentDatahandler >= 1 )
	{
		
		// Read data enterd by the user incase we are going to display an other object.
		this->readDataFromUI();
	
		currentDatahandler--;
		this->displayDatahandlerObject();
		
	}	
	
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayNextObjectData()
{
	// Only perform the action if there datahandlers in the vector.
	if( currentDatahandler >= 0 )
	{
	
		// Read data enterd by the user incase we are going to display an other object.
		this->readDataFromUI();
		
		// A little abuse of the getNextObject function only to update the value of the current object in the datahandler.
		(this->getCurrentDatahandler())->getNextObject();

		this->displayDatahandlerObject();
	};
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::displayPreviousObjectData()
{

	// Only perform the action if there are datahandlers in the vector.
	if( currentDatahandler >= 0 )
	{
	
		// Read data enterd by the user incase we are going to display an other object.
		this->readDataFromUI();
		
		// A little abuse of the getPreviousObject function only to update the value of the current object in the datahandler.
		(this->getCurrentDatahandler())->getPreviousObject();

		this->displayDatahandlerObject();
	};

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::readDataFromUI()
{
	category->readFromTable( (this->getCurrentDatahandler())->getCurrentObject() );
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::newButton_clicked()
{
	// This is test code
	Category* cat = new Category();
	cat->loadCategory ("./testSaveCategory.cat");
	this->addCategory(cat);

	datahandlerAssistant->activate();
	displayNextObjectData();

/*
#ifdef TODO_DEF
#warning TODO Make real code instead of test code in DataWindowGTKMM::newButton_clicked().
#endif

	// This is test code
	Category* cat = new Category();
	cat->loadCategory ("./testSaveCategory.cat");
	this->addCategory(cat);

	Datahandler* datahandler = new Datahandler();
	this->addDatahandler( datahandler );
	datahandler->addNewObject( cat, "file:///home/Pluton/dms/Test.pdf" );
	
	this->displayDatahandlerObject();
	
*/

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::openButton_clicked()
{
	
	// Create a dialog to choose a datahandler from a file.
	Gtk::FileChooserDialog dialog( *dataWindow, "Please choose a datahandler file.", Gtk::FILE_CHOOSER_ACTION_OPEN); //Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER 	 );

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	
    	Glib::ustring result_name = dialog.get_uri();
			URIobject uri( result_name.raw() );
			cout << result_name << "\n";

			Datahandler* newDatahandler = new Datahandler();
			if( newDatahandler->load( uri, this->getCatVec() ) )
			{
				this->addDatahandler( newDatahandler );
				this->update_comboDatahandlers();
				this->update_comboFilesTodo();
				this->displayNextObjectData();
			}
			else
			{
				// TODO throw / catch
				cout << "ERROR in DataWindowGTKMM::openButton_clicked: Unable to open datahandler file: " << result_name << "\n";
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

void DataWindowGTKMM::saveButton_clicked()
{

	Datahandler* curDat = this->getCurrentDatahandler();

	// Check if this datahanlder has a file name if not got saveAsButton_clicked.
	string fileNameString = (curDat->getName()).getFileName();
	if(  fileNameString.compare( "" ) != 0 )
	{
		curDat->save( );
	}
	else
	{
		saveAsButton_clicked();
	}

};

//-----------------------------------------------------------------------------


void DataWindowGTKMM::saveAsButton_clicked()
{
	
	// Create a dialog to choose a file.
	Gtk::FileChooserDialog dialog( *dataWindow, "Save as", Gtk::FILE_CHOOSER_ACTION_SAVE); //Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER 	 );

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::SAVE_AS, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	
    	Glib::ustring result = dialog.get_uri();
			URIobject uri( result.raw() );
			cout << result.raw() << "\n";

  		if( this->getCurrentDatahandler()->save( uri ) != true )
			{
				// TODO catch / throw
				cout << "In DataWindowGTKMM::saveAsButton_clicked: unalbe to save datahandler in file: " << result.raw() << "\n";
			};

      
      break;
    }
     default:
    {
      break;
    }	
	};
};



//-----------------------------------------------------------------------------

void DataWindowGTKMM::update_comboDatahandlers()
{
	string name;
	comboDatahandlers->clear_items();
	for( int i = 0; i < data.size(); i++ )
	{
		name = ((data[i])->getName()).getUriString();
		comboDatahandlers->append_text( name );
	}
	comboDatahandlers->set_active( this->getCurrentDatahandlerIndex() );
};
		
//-----------------------------------------------------------------------------

void DataWindowGTKMM::update_comboFilesTodo()
{
	comboFilesTodo->clear_items();
	Datahandler* dh = this->getCurrentDatahandler();
	list<URIobject*> * todo = dh->filesToDo();
	for( list<URIobject*>::iterator it = todo->begin(); it != todo->end(); ++it )
	{
		comboFilesTodo->append_text( (*it)->getUriString() );
	}
	
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::comboDatahandlers_changed()
{
#ifdef TODO_DEF
#warning TODO DataWindowGTKMM::comboDatahandlers_changed()
#endif	
// change the current datahandler to the selected one.
};
		

//-----------------------------------------------------------------------------

void DataWindowGTKMM::comboFilesTodo_changed()
{
#ifdef TODO_DEF
#warning TODO DataWindowGTKMM::comboFilesTodo_changed()
#endif
	
	int row = comboFilesTodo->get_active_row_number();
	Datahandler* dh =	this->getCurrentDatahandler();
	
	
};

//-----------------------------------------------------------------------------




