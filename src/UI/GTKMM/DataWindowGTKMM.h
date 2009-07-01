//
//	Author: A.L. Hertog
//	Date: 22 June 2009
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


class DataWindowGTKMM 
{

	public:
		DataWindowGTKMM();
		~DataWindowGTKMM();



	private:
	
			Gtk::Window* dataWindow;


};


