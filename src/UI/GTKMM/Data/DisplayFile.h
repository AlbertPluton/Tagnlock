//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//


#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;

//! This is the base class of which the children should be able to generate a visualization of the file.

class DisplayFile
{

	public:
		
		//! Default constructor.
		DisplayFile( string name );
		
		//! Default destructor.
		~DisplayFile();
		
		
		//! This function returns a child of this class based on what type of file has been given.
		static DisplayFile* getDisplay( string fileName );
		
	
		//! This function returns a widget which displays the file.
		virtual Gtk::Widget* getDisplayWidget();
	
		//! return the name of the file.
		string getFileName();
	
	
	protected:

		string fileName;
		
		Gtk::Widget* widget;
		
};


#endif


