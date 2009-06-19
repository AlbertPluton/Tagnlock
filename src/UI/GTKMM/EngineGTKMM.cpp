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

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing FieldTableGTKMM	object.\n";
#endif


	kit = new Gtk::Main(argc, argv);

	dataWindow = 0;
	toolchainWindow = 0;
	categoryWindow = 0;
	fieldTableGTKMM = new FieldTableGTKMM();
	
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
  
  
  // categoryWindow specific
  refXml->get_widget("scrolledwindow3", categoryFieldsWindow);
 	categoryFieldsWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);

  refXml->get_widget("CategoryTreeWindow", categoryTreeWindow);
 	categoryTree = new CategoryTreeGTKMM();
	categoryTreeWindow->add( (*categoryTree) );

	refXml->get_widget("CategoryFieldEditWindow", categoryFieldEditWindow);
	fieldEditWindow = NULL;
 	
	// end categoryWindow

   
  if(dataWindow && toolchainWindow && categoryWindow)
  {

		connectSignals();

		// TODO place the following function in a better place = other function.
//    dataWindow->show();
    categoryWindow->show();
//    toolchainWindow->show();
   
    kit->run();
 		
	}
	
	


	
};


//-----------------------------------------------------------------------------

EngineGTKMM::~EngineGTKMM()
{

#ifdef DEBUG_MESSAGES_DEF	
	cout << "Destroyed a EngineGTKMM object.\n";
#endif

	delete dataWindow;
	delete toolchainWindow;
	delete categoryWindow;
	
	delete categoryFieldsWindow;
	
	delete categoryTreeWindow;
	delete categoryTree;
	
	delete categoryFieldEditWindow;
	delete fieldEditWindow;
};



//-----------------------------------------------------------------------------

void EngineGTKMM::connectSignals()
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
    	// TODO throw error	fieldTableGTKMM = new FieldTableGTKMM();
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
      
    // When clicking on a field in the tree view of the category window, change the selection
    categoryTree->get_signal_selectionChange().connect( sigc::mem_fun( this, &EngineGTKMM::fieldSelected) );

		fieldTableGTKMM->get_signal_selectionChange().connect( sigc::mem_fun( this, &EngineGTKMM::fieldSelected) );

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

// --- Functions relating to the general program flow -------------------------

void EngineGTKMM::quit()
{
	Gtk::Main::quit();
};


	
// --- Functions relating to Category -----------------------------------------

void EngineGTKMM::loadCategory()
{
  Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*categoryWindow);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:
#ifdef TODO_DEF
#warning TODO Make a good filter
#endif
/*	TODO Make a good filter for the files.
  Gtk::FileFilter filter_cat;
  filter_cat.set_name("Category files");
  filter_cat.add_pattern("cat");
  dialog.add_filter(filter_cat);
*/
  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      //Notice that this is a std::string, not a Glib::ustring.
      std::string fileName = dialog.get_filename();
      
      // Load a new category from the file and add it to the vector of category objects.
      Category* cat = new Category();
      cat->loadCategory( fileName );
      this->addCategory( cat );  
      
      // Display the current category which is the new one.
      this->displayCategory( this->getIndexCurrentCategory() );
      
      //std::cout << "Number of categories is: " << this->getNumberOfCategories() << ".\tCurrent category is: " << this->getCurrentCategory() << "\n" ;
      
      break;
    }
     default:
    {
      break;
    }
  }
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

	// If there is an table delete it.
	if( fieldTableGTKMM != NULL )
	{
		categoryFieldsWindow->remove();

		fieldTableGTKMM->clear();
		
		categoryTree->clearTreeModel();
		
		delete fieldEditWindow;
	}



	//fieldTableGTKMM = new FieldTableGTKMM();

	
	Category* cat =  this->getCategory( index );
	if( cat != NULL )
	{
		fieldTableGTKMM->makeNewTable( cat );

		// Add it to the scolled window.
		categoryFieldsWindow->add( *(Gtk::Widget*)fieldTableGTKMM );

		((Gtk::Widget*)fieldTableGTKMM)->show();
		
		// Make a tree model;
		categoryTree->makeTreeModel( cat );

	}
	else
	{
#ifdef TODO_DEF
#warning TODO throw error index exceded
#endif
		cout << "In file " << __FILE__ << " at line " << __LINE__ << ": cat = NULL.\n";
	}
	
	//categoryFieldsWindow->show_all_childeren();

};



//-----------------------------------------------------------------------------

void EngineGTKMM::fieldSelected( int select )
{

	this->setCurrentField( select );
	
	Field* selectedField = this->getCurrentField();
	
	// Make the window to edit the selected field.
	if( fieldEditWindow != NULL ) 
	{
		delete fieldEditWindow;
	}
		
	fieldEditWindow = FieldEditWindowGTKMM::newEditWindow( selectedField );
	categoryFieldEditWindow->add( *fieldEditWindow );
	categoryFieldEditWindow->show();


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




