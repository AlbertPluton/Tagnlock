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
																							addFile( Gtk::Stock::ADD ),
																							delFile( Gtk::Stock::DELETE )
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
	rowIndexFolder = -1;

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

	Gtk::TreeViewColumn* 	col = folderTreeView.get_column(0);
	col->set_resizable( true );
	col->set_min_width(420);
//	col = folderTreeView.get_column(1);
//	col->set_sizing( Gtk::TREE_VIEW_COLUMN_AUTOSIZE ); // TREE_VIEW_COLUMN_FIXED
//	col->set_fixed_width(20);





	// Page 3 File type  and Category selecting -------------------------
	fileScrolledWindow.add( fileTreeView );
	fileScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

	fileBox.add( fileScrolledWindow );
	fileBox.pack_start( fileButtonBox, Gtk::PACK_SHRINK );
	fileBox.set_border_width(5);

	fileButtonBox.pack_start( delFile, Gtk::PACK_SHRINK );
	fileButtonBox.pack_start( addFile, Gtk::PACK_SHRINK );
  fileButtonBox.set_spacing(5);
  fileButtonBox.set_layout( Gtk::BUTTONBOX_END );
  
	addFile.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_addFile ) );
	delFile.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_delFile ) );

	//Create the Tree model:
	fileRefTreeModel = Gtk::ListStore::create( mColumns );
	fileTreeView.set_model( fileRefTreeModel );
	fileTreeSelection = fileTreeView.get_selection();
	rowIndexFile = -1;

  //Add the TreeView's view columns:
  //m_TreeView.append_column_editable("ID", ModelColumns.col_id);

 	//Display a combo text entry to select the file type
  fileColumnCombo = Gtk::manage(new Gtk::CellRendererCombo);
  int cols_count = fileTreeView.append_column("File type", *fileColumnCombo);
  Gtk::TreeViewColumn* pColumn = fileTreeView.get_column(cols_count - 1);
  if(pColumn)
  {
#ifdef GLIBMM_PROPERTIES_ENABLED
    pColumn->add_attribute(fileColumnCombo->property_text_column(), mColumns.col_type);
#else
    pColumn->add_attribute(*fileColumnCombo, "Type", mColumns.col_type);
#endif
  }
	fileTreeView.append_column_editable("Category", mColumns.col_category);



	append_page( fileBox );
	set_page_type( fileBox, Gtk::ASSISTANT_PAGE_CONTENT );
	set_page_title( fileBox, "Select file type(s) and category" );
	set_page_complete( fileBox, true );







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
			rowIndexFolder++;
			row[mColumns.col_id] = rowIndexFolder;
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
		rowIndexFolder--;
	}
};

//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_addFile()
{

		cout << "Add file type\n";
		Gtk::TreeModel::Row row = *(fileRefTreeModel->append());
		rowIndexFile++;
		row[mColumns.col_id] = rowIndexFile;
		row[mColumns.col_type] = " ";
		row[mColumns.col_category] = " ";

};


//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_delFile()
{
	cout << "Delete file type\n";
};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------











