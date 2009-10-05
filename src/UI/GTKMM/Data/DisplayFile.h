//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//


#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "URIobject.h"

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;

//! This is the base class of which the children should be able to generate a visualization of the file.

class DisplayFile
{

	public:
		
		//! Default constructor.
		DisplayFile( URIobject nameURI );
		
		//! Default destructor.
		~DisplayFile();
		
		
		//! This function returns a child of this class based on what type of file has been given.
		static DisplayFile* getDisplay( URIobject fileNameURI );
		
	
		//! This function returns a widget which displays the file.
		virtual Gtk::Widget* getDisplayWidget();
	
		//! return the name of the file.
		URIobject getFileName();
	
	
	protected:

		URIobject fileNameURI;
		
		Gtk::Widget* widget;
		
};


#endif


