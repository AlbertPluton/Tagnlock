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

	double width, height = 0.0;

	GdkPixbuf* gdkPixbuf = NULL;	

	this->document = poppler_document_new_from_file( name.c_str(), NULL, NULL );
	nPages = poppler_document_get_n_pages( this->document );
	pagesVec.reserve(nPages);
	pixbufVec.reserve(nPages);

	

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing DisplayFilePDF	object with " << nPages << " pages.\n";
#endif

	for(int i = 0; i < nPages; i++)
	{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Creating page "<< i <<" ...";
#endif

		// Store the pages in the pages vector
		pagesVec[i] = poppler_document_get_page( this->document, i );

		// Obtain the size of the page
    poppler_page_get_size( pagesVec[i], &width, &height);

		// Create an pixbuf
		gdkPixbuf =  gdk_pixbuf_new( GDK_COLORSPACE_RGB, FALSE, 8, (int)width, (int)height ); //(Colorspace colorspace, bool has_alpha, int bits_per_sample, int width, int height)

		// Render the page to the Gdkpixbuf
		poppler_page_render_to_pixbuf( pagesVec[i], 0, 0, width, height, 1, 0, gdkPixbuf );

		// Convert the Gdkpixbuf to the Gdk::Pixbuf of gtkmm
		pixbufVec[i] = Glib::wrap( gdkPixbuf, false );


#ifdef DEBUG_MESSAGES_DEF
	cout << "\t Done\n";
#endif

	};

	scrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

	box.pack_end( bar );
	box.pack_end( scrolledWindow );
	widget = box;

	bar.append( prev );
	bar.append( next );
	bar.append( itemSpin );

	itemSpin.append( pageNumber );

	Gtk::Adjustment adjustment = Adjustment( 1, 1, nPages ); 
	pageNumber.configure( adjustment, 1, 0 );
	





};


//-----------------------------------------------------------------------------

DisplayFilePDF::~DisplayFilePDF( )
{

};
	


//-----------------------------------------------------------------------------

Gtk::Widget* DisplayFilePDF::getDisplayWidget()
{

};



//-----------------------------------------------------------------------------





//#endif



