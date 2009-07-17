//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//


#ifndef DISPLAYFILEPDF_H
#define DISPLAYFILEPDF_H

#include <gtkmm.h>

#include <glib/poppler.h>

#include "DisplayFile.h"

class DisplayFilePDF : public DisplayFile
{

	public:
	
		DisplayFilePDF( string name );
		
		~DisplayFilePDF( );
	
	
	private:

		PopplerDocument* document;
		int nPages;
		vector<PopplerPage*> pagesVec;
		vector<Gdk::Pixbuf*> pixbufVec;
		
};


#endif



