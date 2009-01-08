//
//	Author: A.L. Hertog
//	Date: 8 January 2009
//	License: GPL
//
//


#include "EngineGTKMM.h"


//-----------------------------------------------------------------------------

EngineGTKMM::EngineGTKMM( int argc, char *argv[], string gladeFileName )
{


	kit(argc, argv);

	
  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gnome::Glade::Xml> refXml;
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
		try
		{
		  refXml = Gnome::Glade::Xml::create("simple.glade");
		}
		catch(const Gnome::Glade::XmlError& ex)
		{
		  std::cerr << ex.what() << std::endl;
		  return 1;
		}
	#else
		std::auto_ptr<Gnome::Glade::XmlError> error;
		refXml = Gnome::Glade::Xml::create("simple.glade", "", "", error);
		if(error.get())
		{
		  std::cerr << error->what() << std::endl;
		  return 1;
		}
	#endif	
	
	// Get the Glade-instantiated Dialogs.
	
	// Connect the signal handlers.
	
	
	// Start the event loop.	
	kit.run();
	
};


//-----------------------------------------------------------------------------

EngineGTKMM::~EngineGTKMM()
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


