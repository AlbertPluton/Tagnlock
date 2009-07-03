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

	toolchainWindow = NULL;

 
	
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

//  refXml->get_widget("DataWindow", dataWindow);
  refXml->get_widget("ToolchainWindow", toolchainWindow);
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
	delete toolchainWindow;
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




