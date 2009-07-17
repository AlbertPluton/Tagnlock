//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//

//#ifdef WITH_POPPLER

#include "DisplayFilePDF.h"

//-----------------------------------------------------------------------------

DisplayFilePDF::DisplayFilePDF( string name ) : DisplayFile( name )
{
	
	this->document = poppler_document_new_from_file( name.c_str(), NULL, NULL );
	nPages = poppler_document_get_n_pages( this->document );
	pixbufVec.reserve(nPages);
	for(int i = 0; i < nPages; i++)
	{
		pagesVec[i] = poppler_document_get_page( this->document, i );
		pixbufVec[i]
		
		poppler_page_render_to_pixbuf       (PopplerPage *page,
                                                         int src_x,
                                                         int src_y,
                                                         int src_width,
                                                         int src_height,
                                                         double scale,
                                                         int rotation,
                                                         GdkPixbuf *pixbuf);
	};
};


//-----------------------------------------------------------------------------

DisplayFilePDF::~DisplayFilePDF( )
{

};
	


//-----------------------------------------------------------------------------








//#endif



