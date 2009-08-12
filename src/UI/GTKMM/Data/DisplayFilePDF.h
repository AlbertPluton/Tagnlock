//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//


#ifndef DISPLAYFILEPDF_H
#define DISPLAYFILEPDF_H

#include <gtkmm.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include <glib/poppler.h>

#include "DisplayFile.h"


//! This class is able to create a widget which displays a PDF file. For this it uses poppler.

class DisplayFilePDF : public DisplayFile
{

	public:
	
		DisplayFilePDF( string name );
		
		~DisplayFilePDF( );
	
		//! This function returns a widget which displays the file.
//		Gtk::Widget* getDisplayWidget();	


	private:

		PopplerDocument* document;

		vector<PopplerPage*> pagesVec;
		vector<GdkPixbuf*> gdkPixbufVec;
		vector< Glib::RefPtr<Gdk::Pixbuf>* > pixbufVec;

		Gtk::Toolbar bar;
		Gtk::ToolButton next, prev;
		Gtk::ToolItem itemPage;
		Gtk::Entry pageNumberEntry;
		Gtk::HBox pageBox;
		Gtk::Label pageLabel;
		Gtk::SeparatorToolItem sep1, sep2;
		
		
		

		Gtk::VBox box;

		Gtk::ScrolledWindow scrolledWindow;
		Gtk::Image image;
		
		
		void nextPage();
		void prevPage();
		void spinPage();
		void showPage( int pageNum );
		void renderCurrentPage();


		int currentPage;
		int nPages;
		double scale;
		
};


#endif



