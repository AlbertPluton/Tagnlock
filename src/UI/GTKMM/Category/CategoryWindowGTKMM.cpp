//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	License: GPL
//
//


#include "CategoryWindowGTKMM.h"


//-----------------------------------------------------------------------------

CategoryWindowGTKMM::CategoryWindowGTKMM( int argc, char **argv, string gladeFileName ) : EngineGTKMM( argc, argv, gladeFileName )
{
#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing CategoryWindowGTKMM	object.\n";
#endif


	categoryWindow = NULL;
 
	
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
  refXml->get_widget("CategoryWindow", categoryWindow);
  

  refXml->get_widget("scrolledwindow3", categoryFieldsWindow);
 	categoryFieldsWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);

  refXml->get_widget("CategoryTreeWindow", categoryTreeWindow);
	refXml->get_widget("CategoryFieldEditWindow", categoryFieldEditWindow);
	categoryGTKMM = new CategoryGTKMM( categoryTreeWindow, categoryFieldEditWindow );



 	
	// end categoryWindow

   
  if(categoryWindow)
  {

		connectSignals();
    categoryWindow->show();
 			 kit->run();
	}
	
	


};

//-----------------------------------------------------------------------------

CategoryWindowGTKMM::~CategoryWindowGTKMM()
{

#ifdef DEBUG_MESSAGES_DEF	
	cout << "Destroyed a CategoryWindowGTKMM object.\n";
#endif


	delete categoryWindow;
	
	delete categoryFieldsWindow;
	delete categoryTreeWindow;
	delete categoryFieldEditWindow;


};

//-----------------------------------------------------------------------------

void CategoryWindowGTKMM::connectSignals()
{




    //Get the Glade-instantiated Button, and connect a signal handler:
    Gtk::ToolButton* pToolButton = 0;
    

    // New button
    refXml->get_widget("toolbutton14", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }
    

		// Open button
    refXml->get_widget("toolbutton15", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::loadCategory) );
    }
    else
    {
    	// TODO throw error
    }
    
    
    // Save button
		refXml->get_widget("toolbutton16", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    } 
    
    // Undo button
		refXml->get_widget("toolbutton18", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }   

    // Redo button
		refXml->get_widget("toolbutton19", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }  
    
    
		// Add button
    refXml->get_widget("toolbutton21", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error	fieldTableGTKMM = new FieldTableGTKMM();
    }
    
    
    // Delete button
		refXml->get_widget("toolbutton22", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    } 
    
    // Up button
		refXml->get_widget("toolbutton23", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }   

    // Down button
		refXml->get_widget("toolbutton24 ", pToolButton);
    if(pToolButton)
    {
      pToolButton->signal_clicked().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::on_toolbutton25_clicked) );
    }
    else
    {
    	// TODO throw error
    }        
      
    // When clicking on a field in the tree view of the category window, change the selection
    categoryGTKMM->get_signal_selectionChange().connect( sigc::mem_fun( this, &CategoryWindowGTKMM::fieldSelected) );



};

//-----------------------------------------------------------------------------

void CategoryWindowGTKMM::loadCategory()
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

void CategoryWindowGTKMM::saveCategory()
{

};

//-----------------------------------------------------------------------------

void CategoryWindowGTKMM::newField()
{

};

//-----------------------------------------------------------------------------

void CategoryWindowGTKMM::modifyField()
{

};

//-----------------------------------------------------------------------------

void CategoryWindowGTKMM::displayCategory( int index )
{

	categoryFieldsWindow->remove();
	categoryGTKMM->clear();

	
	Category* cat =  this->getCategory( index );
	if( cat != NULL )
	{
		categoryGTKMM->makeNewTable( cat );

		// Add it to the scolled window.
		categoryFieldsWindow->add( *(Gtk::Widget*)categoryGTKMM );

		((Gtk::Widget*)categoryGTKMM)->show();
		
		// Make a tree model;
//		categoryTree->makeTreeModel( cat );

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

void CategoryWindowGTKMM::fieldSelected( int select )
{

	this->setCurrentField( select );
	
	Field* selectedField = this->getCurrentField();
	
	// Make the window to edit the selected field.
//	if( fieldEditWindow != NULL ) 
//	{
//		delete fieldEditWindow;
//	}
		
//	fieldEditWindow = FieldEditWindowGTKMM::newEditWindow( selectedField, select );
//	categoryFieldEditWindow->add( *fieldEditWindow );
//	categoryFieldEditWindow->show();


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


