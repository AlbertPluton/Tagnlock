//
//	Author: A.L. Hertog
//	Date: 22 Augustus 2009
//	License: GPL
//
//


#include "DataAssistantGTKMM.h"


//-----------------------------------------------------------------------------


DataAssistantGTKMM::DataAssistantGTKMM( ) : 
																							nameButton( Gtk::Stock::SAVE_AS )
//																						nameChooser(Gtk::FILE_CHOOSER_ACTION_SAVE)
																						
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing a DataAssisTantGTKMM object.\n";
#endif



  set_title("Creating a new datahandler");
  set_default_size(300, 400);

	signal_cancel().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_cancel));
  signal_close().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_cancel));


	// Page 0 Intro ---------------------------------------
	introLabel.set_label( "This wizard will guide you through the process of creating a new datahandler." );
	append_page( introLabel );
	set_page_complete( introLabel, true);
  set_page_type( introLabel, Gtk::ASSISTANT_PAGE_INTRO);
  set_page_title( introLabel, "This is the intro page!");


	// Page 1 Name ----------------------------------------
	nameLabel.set_label( "Name: " );
	nameBox.pack_start( nameLabel );
	nameBox.pack_start( nameEntry );
	nameBox.pack_start( nameButton );
	nameBox.show_all();

	nameButton.signal_clicked().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_nameButton));

	append_page( nameBox );
  set_page_type( nameBox, Gtk::ASSISTANT_PAGE_CONTENT);
  set_page_title( nameBox, "Name");
	set_page_complete( nameBox, true);



	// Page 5 Overview ------------------------------------
	confirmLabel.set_label( "Please confirm your settings for the datahandler to be created." );
	append_page( confirmLabel );
  set_page_type( confirmLabel, Gtk::ASSISTANT_PAGE_CONFIRM);
  set_page_title( confirmLabel, "Confirm");
	


	show_all();

/*
        // create two example pages - this could be every Gtk::Widget
        Gtk::Button* p1;
        Gtk::Button* p2;

        set_title("AssistantExample");
        set_default_size(300, 400);

        signal_cancel().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_cancel));
        signal_close().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_cancel));

        // create the pages.
        p1 = new Gtk::Button("This is page 1\nClick me to proceed");
        p2 = new Gtk::Button("This is page 2\nClick me to restart");

        // hold the pages in a list so we can delete theese later
        pages.push_back(p1);
        pages.push_back(p2);

        // append the first page to the Assistant
        append_page(*p1);

        // set the page's type to indicate this is the introduction page
        set_page_type(*p1, Gtk::ASSISTANT_PAGE_INTRO);

        // set the title of the page
        set_page_title(*p1, "This is the intro page!");

        // prepare the second page - as above
        append_page(*p2);
        set_page_type(*p2, Gtk::ASSISTANT_PAGE_SUMMARY);
        set_page_title(*p2, "This is the summary");

        p1->signal_clicked().connect(
                sigc::mem_fun(*this, &DataAssistantGTKMM::on_intro_finished));
        p2->signal_clicked().connect(
                sigc::mem_fun(*this, &DataAssistantGTKMM::on_summary_finished));

        show_all();
*/

};

 
//-----------------------------------------------------------------------------


DataAssistantGTKMM::~DataAssistantGTKMM()
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Destroying a DataAssistantGTKMM	object.\n";
#endif	



/*        std::list< Widget* >::iterator iter = pages.begin();

        while( iter != pages.end() ) 
				{
                delete *iter;
                iter++;
        }
*/
};




//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_intro_finished(void) 
{
/*

        // when the buttons is clicked we set the page as comlete so the user
        // can proceed to the next page
        Gtk::Widget* p1;
        std::list< Gtk::Widget* >::iterator iter = pages.begin();

        p1 = *iter;
        set_page_complete(*p1, true);

*/
}



//-----------------------------------------------------------------------------


void DataAssistantGTKMM::on_summary_finished(void) 
{

/*
        // when the button is clicked we switch to the introduction page and
        // mark this as not completed. So the user has to click on the button
        // to complete
        Gtk::Widget* p1;
        std::list< Gtk::Widget* >::iterator iter = pages.begin();

        p1 = *iter;
        set_page_complete(*p1, false);
        set_current_page(0);
*/
}



//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_cancel(void)
{
//			Gtk::Main::quit();

        this->hide_all();
}



//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_nameButton()
{

	// Create a dialog to choose a datahandler from a file.
	Gtk::FileChooserDialog dialog( *this, "Save as", Gtk::FILE_CHOOSER_ACTION_SAVE);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	
			nameEntry.set_text( dialog.get_uri() );
			set_page_complete( nameBox, true);		  
      break;
    }
     default:
    {
      break;
    }	
	};	
};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

