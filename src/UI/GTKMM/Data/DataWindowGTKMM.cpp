//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
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
  refXml->get_widget("statusbar1", statusbar);
	datahandlerAssistant = new DataAssistantGTKMM( this );


	if( comboTable )
	{
	
		comboDatahandlers = new Gtk::ComboBoxText();
		comboToolchains = new Gtk::ComboBoxText();
		comboFilesTodo = new Gtk::ComboBoxText();
	
		comboTable->attach( *comboDatahandlers, 1, 2, 0, 1 );
		comboTable->attach( *comboToolchains, 1, 2, 1, 2 ); 
		comboTable->attach( *comboFilesTodo, 1, 2, 2, 3 );
	
		comboSignalDatahandlers = comboDatahandlers->signal_changed().connect(sigc::mem_fun(*this, &DataWindowGTKMM::comboDatahandlers_changed));
		comboSignalToolchains = comboToolchains->signal_changed().connect(sigc::mem_fun(*this, &DataWindowGTKMM::comboToolchains_changed));
		comboSignalFilesTodo = comboFilesTodo->signal_changed().connect(sigc::mem_fun(*this, &DataWindowGTKMM::comboFilesTodo_changed));
	}
	else
	{
		// TODO Faild to obtain table.
	}
	

	category = new CategoryGTKMM( );   
	if( category ) categoryScrolledWindow->add( (Gtk::Widget&)*category );
//	categoryScrolledWindow->show_all();


	// Connect the signal of the Configuration base class to go parse.
	signal_parse().connect( sigc::mem_fun(this, &DataWindowGTKMM::parseToConfig) );


  if(dataWindow)
  {

		connectSignals();
    dataWindow->show_all();
		datahandlerAssistant->hide_all();

		// Load the names in the combos.
		update_comboDatahandlers();
		update_comboFilesTodo();	
		update_comboToolchains();	

		// After start up show the first object.		
		(this->getCurrentDatahandler())->getFirst();
		displayDatahandlerObject();

		
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

	// The delete event to close the program
	dataWindow->signal_delete_event().connect( sigc::mem_fun( this, &EngineGTKMM::quit) );

  // New button
  refXml->get_widget("toolbutton25", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::newButton_clicked) );
    pToolButton->set_tooltip_text("Create a new datahandler.");
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
    pToolButton->set_tooltip_text("Open an exciting datahandler.");
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Save button
	refXml->get_widget("toolbutton27", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::saveDatahandler) );
    pToolButton->set_tooltip_text("Save the current datahandler.");
  }
  else
  {
  	// TODO throw error
  }
  
  // Save as button
	refXml->get_widget("toolbutton33", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::saveAsDatahandler) );
    pToolButton->set_tooltip_text("Save the current datahandler as.");
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
    pToolButton->set_tooltip_text("Display the previous file.");
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
    pToolButton->set_tooltip_text("Display the file file.");
  }
  else
  {
  	// TODO throw error
  }
  
  // Execute completed button
  refXml->get_widget("toolbutton35", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::executeCompletedButton_clicked) );
    pToolButton->set_tooltip_text("Execute the current toolchain on all completed files.");
  }
  else
  {
  	// TODO throw error
  }  

  // Execute button
  refXml->get_widget("toolbutton36", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &DataWindowGTKMM::executeCurrentButton_clicked) );
    pToolButton->set_tooltip_text("Execute the current toolchain on the current file.");
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

		// Disable the signal before changing the active row.
		//sigc::connection connection = comboSignalDatahandlers;
		comboSignalFilesTodo.disconnect();
		// Update the current datahandler combo
		comboFilesTodo->set_active( (this->getCurrentDatahandler())->getPosition() );
		// Enable the signal again
		comboSignalFilesTodo = comboFilesTodo->signal_changed().connect(sigc::mem_fun(*this, &DataWindowGTKMM::comboFilesTodo_changed));
		
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
		(this->getCurrentDatahandler())->getNext();

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
		(this->getCurrentDatahandler())->getPrevious();

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
/*
	// This is test code
	Category* cat = new Category();
	cat->loadCategory("./testSaveCategory.cat");
	this->addCategory(cat);
	
	Toolchain* tool = Toolchain::loadToolchain( "./toolchainSave.txt" );
	this->addToolchain( tool );
	
	
	this->saveConfig();
*/


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
	try
	{
		this->loadDatahandler();
		this->update_comboDatahandlers();
		this->update_comboFilesTodo();
//		(this->getCurrentDatahandler())->getNextObject();
		this->displayNextObjectData();
	}
	catch( exception& e )
	{
#ifdef TODO_DEF
#warning TODO DataWindowGTKMM::openButton_clicked()
#endif		
	}

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::executeCompletedButton_clicked()
{
	readDataFromUI();
	Toolchain* toolchain = this->getCurrentToolchain();
	Datahandler* pData = this->getCurrentDatahandler();
	try
	{
		toolchain->setInput( pData );
		// Execute all the completed objects
		toolchain->execute();
	}
	catch( exception& e )
	{
	
	}
	
	statusbar->push( "Executed toolchain \"" + toolchain->getName() + "\" on datahandler \"" + pData->getName() + "\"." );
	
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::executeCurrentButton_clicked()
{
	readDataFromUI();
	Toolchain* toolchain = this->getCurrentToolchain();
	Datahandler* pData = this->getCurrentDatahandler();
	try
	{
		toolchain->setInput( pData );
		// Execute only the current object.
		toolchain->execute( true );
	}
	catch( exception& e )
	{
	
	}
	
	statusbar->push( "Executed toolchain \"" + toolchain->getName() + "\" on datahandler \"" + pData->getName() + "\"." );
	
};
//-----------------------------------------------------------------------------

void DataWindowGTKMM::update_comboDatahandlers()
{
	string name;
	comboDatahandlers->clear_items();
	for( int i = 0; i < data.size(); i++ )
	{
		name = (data[i])->getName();
		comboDatahandlers->append_text( name );
	}
	comboDatahandlers->set_active( this->getCurrentDatahandlerIndex() );
};
		
//-----------------------------------------------------------------------------

void DataWindowGTKMM::update_comboFilesTodo()
{
	comboFilesTodo->clear_items();
	Datahandler* dh = this->getCurrentDatahandler();
	list<URIobject*> todo = dh->filesToDo();
	for( list<URIobject*>::iterator it = todo.begin(); it != todo.end(); ++it )
	{
		URIobject* uri = *it;
		comboFilesTodo->append_text( uri->getUriString() );
	}
	
};


//-----------------------------------------------------------------------------

void DataWindowGTKMM::update_comboToolchains()
{
	string name;
	comboToolchains->clear_items();
	for( int i = 0; i < toolchains.size(); i++ )
	{
		name = toolchains[i]->getName();
		comboToolchains->append_text( name );
	};
	comboToolchains->set_active( this->getCurrentToolchainIndex() );	

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
	dh->getObjectAt( row );
	this->displayDatahandlerObject();
};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::comboToolchains_changed()
{
	int row = comboToolchains->get_active_row_number();
	this->setCurrentToolchain(row);
	cout << "Current Toolchain set to: " << row << "\n";
};


//-----------------------------------------------------------------------------



void DataWindowGTKMM::parseToConfig()
{

};

//-----------------------------------------------------------------------------

void DataWindowGTKMM::updateFromConfig()
{

};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------




