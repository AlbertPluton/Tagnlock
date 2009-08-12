//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//

//#ifdef WITH_POPPLER

#include "DisplayFilePDF.h"

#include <sstream>
using namespace std;

//-----------------------------------------------------------------------------

DisplayFilePDF::DisplayFilePDF( string name ) : DisplayFile( name )
{

	double width, height = 0.0;
	GdkPixbuf* gdkPixbuf;

	this->document = poppler_document_new_from_file( name.c_str(), NULL, NULL );
	nPages = poppler_document_get_n_pages( this->document );
	pagesVec.reserve(nPages);
	pixbufVec.reserve(nPages);
	currentPage = 1;

	

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing DisplayFilePDF object with " << nPages << " pages.\n";
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
		pixbufVec[i] = new Glib::RefPtr<Gdk::Pixbuf>;
		*(pixbufVec[i]) = Glib::wrap( gdkPixbuf );


#ifdef DEBUG_MESSAGES_DEF
	cout << "\t Done\n";
#endif

	};

	prev.set_stock_id( Gtk::Stock::GO_UP);
	prev.signal_clicked().connect( sigc::mem_fun( this, &DisplayFilePDF::prevPage) );
	prev.show();
	
	
	next.set_stock_id( Gtk::Stock::GO_DOWN );
	next.signal_clicked().connect( sigc::mem_fun( this, &DisplayFilePDF::nextPage) );
	next.show();
 
 
 	stringstream string;
 	
 	string << "  of " << nPages;
  
 	pageLabel.set_label( string.str() );
 	pageLabel.show();

	bar.append( prev );
	bar.append( next );
	bar.append( sep1 );
	pageBox.pack_start( pageNumberEntry );
	pageBox.pack_start( pageLabel );	
	itemPage.add( pageBox );	
	bar.append( itemPage );
	bar.append( sep2 );

/*
	Gtk::Adjustment adjustment(1, 1, nPages );
	pageNumberSpin.configure( adjustment, 1, 0 );
	pageNumberSpin.set_numeric();
	pageNumberSpin.set_update_policy( Gtk::UPDATE_ALWAYS );
	pageNumberSpin.signal_value_changed().connect( sigc::mem_fun( this, &DisplayFilePDF::spinPage) );
*/

	
	scrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	image.set( *(pixbufVec[0]) );
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


void DisplayFilePDF::spinPage()
{
	cout << "old page number: " << pageNumberSpin.get_value_as_int() << "\n";
	showPage( pageNumberSpin.get_value_as_int() );
};

//-----------------------------------------------------------------------------


void DisplayFilePDF::showPage( int pageNum )
{
	// Check for valid page number.
	if( (pageNum <= nPages) && (pageNum > 0) )
	{
		// Set the current page number to the new value.
		currentPage = pageNum;
		pageNumberSpin.set_value( currentPage );
		cout << "Current page: " << currentPage << "\tspin value: " <<  pageNumberSpin.get_value_as_int() << "\n";
		pageNumberSpin.update();
		
		
		image.clear();
		
		// Create an image from the pixbuf and display it in the scrolled window.
		image.set( *(pixbufVec[currentPage-1]) );
	}
	
	//pageNumberSpin.update();

};


//-----------------------------------------------------------------------------



//#endif



