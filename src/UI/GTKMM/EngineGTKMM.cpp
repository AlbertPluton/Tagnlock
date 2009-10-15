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
	cout << "Constructing EngineGTKMM	object.\n";
#endif


	kit = new Gtk::Main(argc, argv);

 
/*	
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
*/
	
	
	// Get the Glade-instantiated windows and dialogs.

//  refXml->get_widget("DataWindow", dataWindow);
//  refXml->get_widget("ToolchainWindow", toolchainWindow);
//  refXml->get_widget("CategoryWindow", categoryWindow);
  
/*  
  // categoryWindow specific
  refXml->get_widget("scrolledwindow3", categoryFieldsWindow);
 	categoryFieldsWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);

  refXml->get_widget("CategoryTreeWindow", categoryTreeWindow);
	refXml->get_widget("CategoryFieldEditWindow", categoryFieldEditWindow);
	categoryGTKMM = new CategoryGTKMM( categoryTreeWindow, categoryFieldEditWindow );

*/

 	
	// end categoryWindow

/*  
  if(dataWindow && toolchainWindow && categoryWindow)
  {

		connectSignals();

		// TODO place the following function in a better place = other function.
    dataWindow->show();
//    categoryWindow->show();
//    toolchainWindow->show();
   
    kit->run();
 		
	}
*/	



	
};


//-----------------------------------------------------------------------------

EngineGTKMM::~EngineGTKMM()
{

#ifdef DEBUG_MESSAGES_DEF	
	cout << "Destroyed a EngineGTKMM object.\n";
#endif

//	delete dataWindow;
//	delete toolchainWindow;
//	delete categoryWindow;
	

};



//-----------------------------------------------------------------------------


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





bool EngineGTKMM::loadCategory()
{
  Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
//  dialog.set_transient_for(*this);

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

#ifdef TODO_DEF
#warning TODO Check to see if the category is not already loaded.
#endif
      this->addCategory( cat );  
     
     	return true;
     	 
      //std::cout << "Number of categories is: " << this->getNumberOfCategories() << ".\tCurrent category is: " << this->getCurrentCategory() << "\n" ;
      
      break;
    }
     default:
    {
    	return false;
      break;
    }
  }
  
  return false;
  
};






//-----------------------------------------------------------------------------
// --- Functions relating to Toolchain ----------------------------------------

bool EngineGTKMM::loadToolchain()
{
	bool succes = false;

	// Create a dialog to load a toolchain from a file.
	Gtk::FileChooserDialog dialog( "Please a toolchain file.", Gtk::FILE_CHOOSER_ACTION_OPEN); 

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
			succes = true;
     
      break;
    }
     default:
    {
      break;
    }	
	};
	
	return succes;

};

//-----------------------------------------------------------------------------

bool EngineGTKMM::saveAsToolchain()
{
	bool succes = false;

	// Create a dialog to save a toolchain to a file.
	Gtk::FileChooserDialog dialog( "Please select a file name.", Gtk::FILE_CHOOSER_ACTION_OPEN); 

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	
    	string result_name = dialog.get_filename();
			cout << result_name << "\n";

			Toolchain* toolchain = this->getCurrentToolchain();
			toolchain->saveToolchain( result_name );
     	succes = true;
     	
      break;
    }
     default:
    {
      break;
    }	
	};
	
	return succes;
	
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




