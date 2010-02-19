//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

//#ifdef WITH_POPPLER

#include "DisplayFilePDF.h"

#include <sstream>
using namespace std;

//-----------------------------------------------------------------------------

DisplayFilePDF::DisplayFilePDF( URIobject nameURI ) : DisplayFile( nameURI )
{

	string nameString = nameURI.getUriString();
	document = poppler_document_new_from_file( nameString.c_str(), NULL, NULL );
	nPages = poppler_document_get_n_pages( this->document );
	pagesVec.reserve(nPages);
	pixbufVec.reserve(nPages);
	currentPage = 0;
	scale = 1;
	

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing DisplayFilePDF object with " << nPages << " pages, file name: \"" << nameString << "\"\n";
#endif


	// Initialize the vectors with nothing in them.
	for( int i = 0; i < nPages; i++ )
	{
		pagesVec[i] = NULL;
		pixbufVec[i] = NULL;
	}


	renderPage( currentPage );


	prev.set_stock_id( Gtk::Stock::GO_BACK);
	prev.signal_clicked().connect( sigc::mem_fun( this, &DisplayFilePDF::prevPage) );
	prev.show();
	
	
	next.set_stock_id( Gtk::Stock::GO_FORWARD );
	next.signal_clicked().connect( sigc::mem_fun( this, &DisplayFilePDF::nextPage) );
	next.show();
 
 
 	stringstream string;
 	
 	string << "1  of " << nPages;
  
 	pageLabel.set_label( string.str() );
 	pageLabel.show();

	bar.append( prev );
	bar.append( next );
	bar.append( sep1 );
	pageBox.pack_start( pageLabel );	
	itemPage.add( pageBox );	
	bar.append( itemPage );
	bar.append( sep2 );


	scrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	image.set( *(pixbufVec[currentPage]) );
	scrolledWindow.add( image );
	
	box.pack_start( bar, Gtk::PACK_SHRINK  );
	box.pack_start( scrolledWindow );
	widget = (Gtk::Widget*)&box;

	box.set_homogeneous( false );



	box.show_all();




};


//-----------------------------------------------------------------------------

DisplayFilePDF::~DisplayFilePDF( )
{


};
	


//-----------------------------------------------------------------------------
/*
Gtk::Widget* DisplayFilePDF::getDisplayWidget()
{

};
*/


//-----------------------------------------------------------------------------

		
void DisplayFilePDF::nextPage()
{
	showPage( currentPage + 1 );
};

//-----------------------------------------------------------------------------



void DisplayFilePDF::prevPage()
{
	showPage( currentPage - 1 );
};

//-----------------------------------------------------------------------------


void DisplayFilePDF::showPage( int pageNum )
{
	// Check for valid page number.
	if( (pageNum < nPages) && (pageNum >= 0) )
	{
		// Set the current page number to the new value.
		currentPage = pageNum;
	 	stringstream string;
	 	
	 	string << currentPage+1 << " of " << nPages;
	 	pageLabel.set_label( string.str() );

		
		image.clear();
		
		if( pixbufVec[currentPage] == NULL ) renderPage( currentPage );

		// Create an image from the pixbuf and display it in the scrolled window.
		image.set( *(pixbufVec[currentPage]) );
	}
	

};


//-----------------------------------------------------------------------------


void DisplayFilePDF::renderPage( int page )
{

	double width, height = 0.0;
	GdkPixbuf* gdkPixbuf;


#ifdef DEBUG_MESSAGES_DEF
	cout << "Creating page "<< page  <<" ...";
#endif

	// Store the pages in the pages vector
	pagesVec[page] = poppler_document_get_page( document, page );

	// Obtain the size of the page
  poppler_page_get_size( pagesVec[page], &width, &height);

	// Create an pixbuf
	gdkPixbuf =  gdk_pixbuf_new( GDK_COLORSPACE_RGB, FALSE, 8, (int)(width*scale), (int)(height*scale) ); //(Colorspace colorspace, bool has_alpha, int bits_per_sample, int width, int height)

	// Render the page to the Gdkpixbuf
	poppler_page_render_to_pixbuf( pagesVec[page], 0, 0, width, height, scale, 0, gdkPixbuf );

	// Convert the Gdkpixbuf to the Gdk::Pixbuf of gtkmm	
	pixbufVec[page] = new Glib::RefPtr<Gdk::Pixbuf>;
	*(pixbufVec[page]) = Glib::wrap( gdkPixbuf );


#ifdef DEBUG_MESSAGES_DEF
	cout << "\t Done\n";
#endif


};



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


