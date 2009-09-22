//
//	Author: A.L. Hertog
//	Date: 22 Augustus 2009
//	License: GPL
//
//


#include "DataAssistantGTKMM.h"



#define confirmTableWidth 	12

#define confirmTableLabelStart	0
#define confirmTableLabelEnd 	  confirmTableWidth
#define confirmTableLabelHeight 1

#define confirmTableDataStart 	1
#define confirmTableDataEnd   	confirmTableWidth-2
#define confirmTableDataHeight  5
#define confirmTableDataEntryHeight 1

#define confirmTableSepStart	0
#define confirmTableSepEnd		confirmTableWidth-1
#define confirmTableSepHeight 1

#define confirmTableHeight 	4*confirmTableLabelHeight + 1*confirmTableDataEntryHeight + 2*confirmTableDataHeight + 2*confirmTableSepHeight



//-----------------------------------------------------------------------------


DataAssistantGTKMM::DataAssistantGTKMM( EngineGTKMM* parentWindow ) : 
																							nameTable( 1, 3 ),																							
																							nameButton( Gtk::Stock::SAVE_AS ),
																							addFolder( Gtk::Stock::ADD ),
																							delFolder( Gtk::Stock::DELETE ),
																							addFile( Gtk::Stock::ADD ),
																							delFile( Gtk::Stock::DELETE ),
																							loadCat( "Open Category" ),
																							confirmTable( confirmTableWidth, confirmTableHeight, false ),
																							confirmLabel( "<b>Please confirm your settings for the datahandler to be created.</b>", Gtk::ALIGN_LEFT ),
																							confirmName( "Datahandler name:", Gtk::ALIGN_LEFT ),
																							confirmFolder( "Folders to be search for source files:", Gtk::ALIGN_LEFT ),
																							confirmType( "Desired file type(s) and associated categories:", Gtk::ALIGN_LEFT )																		
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing a DataAssisTantGTKMM object.\n";
#endif

	parent = parentWindow;


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

// TODO
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
	set_page_title( folderBox, "Select source folder(s)" );

// TODO
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

	fileButtonBox.pack_start( loadCat, Gtk::PACK_SHRINK );
	fileButtonBox.pack_start( delFile, Gtk::PACK_SHRINK );
	fileButtonBox.pack_start( addFile, Gtk::PACK_SHRINK );

  fileButtonBox.set_spacing(5);
  fileButtonBox.set_layout( Gtk::BUTTONBOX_END );
  
	addFile.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_addFile ) );
	delFile.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_delFile ) );
	loadCat.signal_clicked().connect( sigc::mem_fun( *this, &DataAssistantGTKMM::on_loadCat ) );

  //Create and fill the combo models
  // The file type combo
  fileRefTreeModelTypeCombo = Gtk::ListStore::create(columnsTypeCombo);
  Gtk::TreeModel::Row row = *(fileRefTreeModelTypeCombo->append());
  row[columnsTypeCombo.col_choice] = "*.pdf";
  row = *(fileRefTreeModelTypeCombo->append());
  row[columnsTypeCombo.col_choice] = "*.*";

	// The category combo
	fileRefTreeModelCategoryCombo = Gtk::ListStore::create(columnsCategoryCombo);
	for( int i = 0; i < categories.size(); i++ )
	{
		row = *(fileRefTreeModelCategoryCombo->append());	
		row[columnsTypeCombo.col_choice] = categories[i]->getName();
	}


	//Create the Tree model:
	fileRefTreeModel = Gtk::ListStore::create( mColumns );
	fileTreeView.set_model( fileRefTreeModel );
	fileTreeSelection = fileTreeView.get_selection();
	rowIndexFile = -1;
    
	// Add the first file type row.
	on_addFile();

  //Add the TreeView's view columns:

//  fileTreeView.append_column_editable("ID", mColumns.col_id);

  //Create a Combo CellRenderer for the type column
  Gtk::TreeView::Column* pColumn = Gtk::manage( new Gtk::TreeView::Column("File type") ); 
  Gtk::CellRendererCombo* pRenderer = Gtk::manage( new Gtk::CellRendererCombo);
  pColumn->pack_start(*pRenderer);
  fileTreeView.append_column(*pColumn);
  //Make this View column represent the m_col_itemchosen model column:
#ifdef GLIBMM_PROPERTIES_ENABLED
  pColumn->add_attribute(pRenderer->property_text(), mColumns.col_type);
#else
  pColumn->add_attribute(*pRenderer, "text", mColumns.col_type);
#endif
	// Set the entry combo to use the combo model.
	pRenderer->property_model() = fileRefTreeModelTypeCombo;
  // This must be a text column, in fileRefTreeModelCombo
#ifdef GLIBMM_PROPERTIES_ENABLED
  pRenderer->property_text_column() = 0; 
#else
  pRenderer->set_property("text_column", 0);
#endif
  //Allow the user to edit the column:
  //This is done automatically when we use View::append_column(model_column), but that uses a simple Text CellRenderer.
#ifdef GLIBMM_PROPERTIES_ENABLED
  pRenderer->property_editable() = true;
#else
  pRenderer->set_property("editable", true);
#endif
  pRenderer->signal_edited().connect( sigc::mem_fun(*this, &DataAssistantGTKMM::on_cellrenderer_type_edited) );


  //Create a Combo CellRenderer for the category column
  pColumn = Gtk::manage( new Gtk::TreeView::Column("Category") ); 
  pRenderer = Gtk::manage( new Gtk::CellRendererCombo);
  pColumn->pack_start(*pRenderer);
  fileTreeView.append_column(*pColumn);
  //Make this View column represent the m_col_itemchosen model column:
#ifdef GLIBMM_PROPERTIES_ENABLED
  pColumn->add_attribute(pRenderer->property_text(), mColumns.col_category);
#else
  pColumn->add_attribute(*pRenderer, "text", mColumns.col_category);
#endif
	// Set the entry combo to use the combo model.
	pRenderer->property_model() = fileRefTreeModelCategoryCombo;
  // This must be a text column, in fileRefTreeModelCombo
#ifdef GLIBMM_PROPERTIES_ENABLED
  pRenderer->property_text_column() = 0; 
#else
  pRenderer->set_property("text_column", 0);
#endif
  //Allow the user to edit the column:
  //This is done automatically when we use View::append_column(model_column), but that uses a simple Text CellRenderer.
#ifdef GLIBMM_PROPERTIES_ENABLED
  pRenderer->property_editable() = true;
#else
  pRenderer->set_property("editable", true);
#endif
	// Make the sure this combo box does not allow user typed in put, only the possibility to select something from the list.
	pRenderer->property_has_entry() = false;
	// Conect the signal to the signal handler function.
  pRenderer->signal_edited().connect( sigc::mem_fun(*this, &DataAssistantGTKMM::on_cellrenderer_category_edited) );


	col = fileTreeView.get_column(0);
	col->set_resizable( true );
	col->set_min_width(150);
	
	
	append_page( fileBox );
	set_page_type( fileBox, Gtk::ASSISTANT_PAGE_CONTENT );
	set_page_title( fileBox, "Select file type(s) and associated category" );

//TODO
	set_page_complete( fileBox, true );







	// Page 4 Overview ------------------------------------

	confirmLabel.set_use_markup(true); // required for bold text.
		
	confirmFolderScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	confirmFileScrolledWindow.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	confirmFolderScrolledWindow.add( confirmFolderTreeView );
	confirmFileScrolledWindow.add( confirmFileTreeView );
	confirmFolderTreeView.set_model( folderRefTreeModel );
	confirmFileTreeView.set_model( fileRefTreeModel );

	// Add every thing to the table
	int ypos1 = 0;
	int ypos2 = confirmTableLabelHeight;
	
	confirmTable.attach( confirmLabel, confirmTableLabelStart, confirmTableLabelEnd, ypos1, ypos2, Gtk::FILL, Gtk::SHRINK, 5, 5 ); ypos1 = ypos2; ypos2 += confirmTableLabelHeight;
	
	confirmTable.attach( confirmName, confirmTableLabelStart, confirmTableLabelEnd, ypos1, ypos2, Gtk::FILL, Gtk::SHRINK, 5, 5 ); ypos1 = ypos2; ypos2 += confirmTableLabelHeight;
  confirmTable.attach( confirmNameEntry, confirmTableDataStart, confirmTableDataEnd, ypos1, ypos2, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 5 ); ypos1 = ypos2; ypos2 += confirmTableDataEntryHeight;
	confirmTable.attach( confirmSep1, confirmTableSepStart, confirmTableSepEnd, ypos1, ypos2, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK, 5, 5 ); ypos1 = ypos2; ypos2 += confirmTableSepHeight;
	
	
	confirmTable.attach( confirmFolder, confirmTableLabelStart, confirmTableLabelEnd, ypos1, ypos2, Gtk::FILL, Gtk::SHRINK, 5, 5 ); ypos1 = ypos2; ypos2 += confirmTableLabelHeight;
  confirmTable.attach( confirmFolderScrolledWindow, confirmTableDataStart, confirmTableDataEnd, ypos1, ypos2, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 5 ); ypos1 = ypos2; ypos2 += confirmTableDataHeight;
	confirmTable.attach( confirmSep2, confirmTableSepStart, confirmTableSepEnd, ypos1, ypos2, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK, 5, 5 ); ypos1 = ypos2; ypos2 += confirmTableSepHeight;
	
	confirmTable.attach( confirmType, confirmTableLabelStart, confirmTableLabelEnd, ypos1, ypos2, Gtk::FILL, Gtk::SHRINK, 5, 5 ); ypos1 = ypos2; ypos2 += confirmTableLabelHeight;
	confirmTable.attach( confirmFileScrolledWindow, confirmTableDataStart, confirmTableDataEnd, ypos1, ypos2, Gtk::EXPAND|Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 5 ); ypos1 = ypos2; ypos2 += confirmTableDataHeight;
	append_page( confirmTable );
  set_page_type( confirmTable, Gtk::ASSISTANT_PAGE_CONFIRM);
  set_page_title( confirmTable, "Confirm");
	


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

void DataAssistantGTKMM::activate()
{

	show_all();
	updateCategories(); 
	
};

//-----------------------------------------------------------------------------

void DataAssistantGTKMM::updateCategories( )
{

	// Update the list of categories known to the program.
	vector<Category*> * cat = parent->getCatVec();

	// Clear the list
	fileRefTreeModelCategoryCombo->clear();

	// Put the categories in rows to display in the combo button.
	Gtk::TreeModel::Row row;
	for( int i = 0; i < cat->size(); i++ )
	{
		row = *(fileRefTreeModelCategoryCombo->append());	
		row[columnsTypeCombo.col_choice] = (*cat)[i]->getName();
	}

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
		row[mColumns.col_type] = "click here";
		row[mColumns.col_category] = "click here";

		checkFileDone();

};


//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_delFile()
{
	cout << "Delete file type\n";
	
	Gtk::TreeModel::iterator iter = fileTreeSelection->get_selected();
	
	if( iter )
	{
		fileRefTreeModel->erase(iter);
		checkFileDone();
	};
	
};


//-----------------------------------------------------------------------------

void DataAssistantGTKMM::on_loadCat()
{
	parent->loadCategory();
	updateCategories( );
};
		
//-----------------------------------------------------------------------------
		
void DataAssistantGTKMM::on_cellrenderer_type_edited( const Glib::ustring& path_string, const Glib::ustring& new_text)
{
  Gtk::TreePath path(path_string);

  //Get the row from the path:
  Gtk::TreeModel::iterator iter = fileRefTreeModel->get_iter(path);
  if(iter)
  {
      //Store the user's new text in the model:
      Gtk::TreeRow row = *iter;
      row[mColumns.col_type] = new_text;
      checkFileDone();
  }
}

//-----------------------------------------------------------------------------


void DataAssistantGTKMM::on_cellrenderer_category_edited( const Glib::ustring& path_string, const Glib::ustring& new_text)
{
  Gtk::TreePath path(path_string);

  //Get the row from the path:
  Gtk::TreeModel::iterator iter = fileRefTreeModel->get_iter(path);
  if(iter)
  {
      //Store the user's new text in the model:
      Gtk::TreeRow row = *iter;
      row[mColumns.col_category] = new_text;
      checkFileDone();
  }
}

//-----------------------------------------------------------------------------

void DataAssistantGTKMM::checkFileDone()
{
	// Get all rows as itertor
	Gtk::TreeModel::Children rows = fileRefTreeModel->children(); 
	
	Gtk::TreeModel::iterator r; 
	
	// A single row
	Gtk::TreeModel::Row row;
	
	bool complete = false;
	
	// Loop over all rows
	for(r=rows.begin(); r!=rows.end(); r++)
	{
 		row=*r; 
 		

 		Glib::ustring ustr1 = row[mColumns.col_type];
 		Glib::ustring ustr2 = row[mColumns.col_category];

		bool a = ustr1.compare("click here") != 0;
		bool b = ustr2.compare("click here") != 0;

		if( a && b )
		{
			complete = true;
		}
		else
		{			
			complete = false;
			break;
		}

	};
	
	set_page_complete( fileBox, complete );
	
};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------











