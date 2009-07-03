//
//	Author: A.L. Hertog
//	Date: 3 July 2009
//	License: GPL
//
//


#include "EngineGTKMM.h"



#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;


//! This class is an interface to the data window and the engine. It is used to process user input among other relevant things.

class DataWindowGTKMM : public EngineGTKMM
{

	public:
	
		//! The default constructor.
		/*!
			\param data is a pointer to the data window.
		*/
		DataWindowGTKMM( Glib::RefPtr<Gnome::Glade::Xml>* xml );
		
		//! The default destructor.
		~DataWindowGTKMM();





	private:
	
			Gtk::Window* dataWindow;


};


