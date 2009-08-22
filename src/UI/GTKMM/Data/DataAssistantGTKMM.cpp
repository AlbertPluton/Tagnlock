//
//	Author: A.L. Hertog
//	Date: 22 Augustus 2009
//	License: GPL
//
//


#include "DataAssistantGTKMM.h"


//-----------------------------------------------------------------------------


DataAssistantGTKMM::DataAssistantGTKMM( ) : 

																						introLabel("This wizard will guide you through the process of creating a new datahandler."),


																						nameChooser(Gtk::FILE_CHOOSER_ACTION_SAVE)
																						
{


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


};

 
//-----------------------------------------------------------------------------


DataAssistantGTKMM::~DataAssistantGTKMM()
{
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



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

