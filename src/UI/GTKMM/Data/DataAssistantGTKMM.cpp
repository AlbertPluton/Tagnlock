//
//	Author: A.L. Hertog
//	Date: 22 Augustus 2009
//	License: GPL
//
//


#include "DataAssistantGTKMM.h"


//-----------------------------------------------------------------------------


DataAssistantGTKMM::DataAssistantGTKMM( ) : 
																							nameTable( 1, 3 ),																							
																							nameButton( Gtk::Stock::SAVE_AS ),
																							addFolder( Gtk::Stock::ADD ),
																							delFolder( Gtk::Stock::DELETE ),
																							fileTable( 1, 2 )																					
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
	nameTable.attach( nameLabel, 0, 1, 0, 1, Gtk::SHRINK, Gtk::EXPAND, 2, 0);
	nameTable.attach( nameEntry, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 2, 0);
	nameTable.attach( nameButton, 2, 3, 0, 1, Gtk::SHRINK, Gtk::EXPAND, 2, 0);

	nameButton.signal_clicked().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_nameButton));

	append_page( nameTable );
  set_page_type( nameTable, Gtk::ASSISTANT_PAGE_CONTENT);
  set_page_title( nameTable, "Name");
	set_page_complete( nameTable, true);



	// Page 2 Folder selecting ----------------------------
	folderScrolledWindow.add( folderTreeView );
	folderScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

	folderBox.add( folderScrolledWindow );
	folderBox.pack_start( folderButtonBox, Gtk::PACK_SHRINK );
	folderBox.set_border_width(5);

	folderButtonBox.pack_start( delFolder, Gtk::PACK_SHRINK );
	folderButtonBox.pack_start( addFolder, Gtk::PACK_SHRINK );
  folderButtonBox.set_spacing(5);
  folderButtonBox.set_layout( Gtk::BUTTONBOX_END );
  
	addFolder.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_addFolder ) );
	delFolder.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_delFolder ) );

	//Create the Tree model:
	folderRefTreeModel = Gtk::ListStore::create( mColumns );
	folderTreeView.set_model( folderRefTreeModel );
	folderTreeSelection = folderTreeView.get_selection();

  //Add the TreeView's view columns:
  //m_TreeView.append_column_editable("ID", ModelColumns.col_id);
  folderTreeView.append_column_editable("Folder", mColumns.col_folder);
  folderTreeView.append_column_editable("Recursive", mColumns.col_recursive);

//	mColumns.col_folder->set_resizable( true );
//	mColumns.col_recursive->set_resizable( true );

	append_page( folderBox );
	set_page_type( folderBox, Gtk::ASSISTANT_PAGE_CONTENT );
	set_page_title( folderBox, "Select source forlder(s)" );
	set_page_complete( folderBox, true );
	rowIndex = -1;

	Gtk::TreeViewColumn* 	col = folderTreeView.get_column(0);
	col->set_resizable( true );
	col->set_min_width(420);
//	col = folderTreeView.get_column(1);
//	col->set_sizing( Gtk::TREE_VIEW_COLUMN_AUTOSIZE ); // TREE_VIEW_COLUMN_FIXED
//	col->set_fixed_width(20);


	// Page 3 File type  and Category selecting -------------------------
	fileLabel.set_label("Select or enter file types (e.g. *.pdf):");
	fileEntry.append_text("*.pdf");
	fileEntry.signal_changed().connect(sigc::mem_fun(*this, &DataAssistantGTKMM::on_entry_changed) );

	fileTable.attach( fileLabel, 0, 1, 0, 1, Gtk::SHRINK, Gtk::EXPAND, 2, 0);
	fileTable.attach( fileEntry, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND, 2, 0);

	append_page( fileTable );
	set_page_type( fileTable, Gtk::ASSISTANT_PAGE_CONTENT );
	set_page_title( fileTable, "Select file type(s)");


	// Page 5 Overview ------------------------------------
	confirmLabel.set_label( "Please confirm your settings for the datahandler to be created." );
	append_page( confirmLabel );
  set_page_type( confirmLabel, Gtk::ASSISTANT_PAGE_CONFIRM);
  set_page_title( confirmLabel, "Confirm");
	


	show_all();

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
			set_page_complete( nameTable, true);		  
      break;
    }
     default:
    {
      break;
    }	
	};	
};


//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_addFolder()
{

	// Create a dialog to choose a datahandler from a file.
	Gtk::FileChooserDialog dialog( *this, "Select folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {	

			Gtk::TreeModel::Row row = *(folderRefTreeModel->append());
			rowIndex++;
			row[mColumns.col_id] = rowIndex;
  		row[mColumns.col_folder] = dialog.get_uri();
  		row[mColumns.col_recursive] = false;

			set_page_complete( folderBox, true);		  
      break;
    }
     default:
    {
      break;
    }	
	};	

};


//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_delFolder()
{
	Gtk::TreeModel::iterator iter = folderTreeSelection->get_selected();
	if(iter) //If anything is selected
	{
		folderRefTreeModel->erase(iter);
	}
};

//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_entry_changed()
{
	set_page_complete( fileTable, true );
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------











