//
//	Author: A.L. Hertog
//	Date: 7 October 2009
//	License: GPL
//
//

#include "ToolchainWindowGTKMM.h"

#include "DialogOperationChooserGTKMM.h"

//-----------------------------------------------------------------------------

ToolchainWindowGTKMM::ToolchainWindowGTKMM(  int argc, char **argv, string gladeFileName ) : EngineGTKMM( argc, argv, gladeFileName )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing a ToolchainWindowGTKMM object.\n";
#endif

	toolchainWindow = NULL;
	treeView = NULL;
	textView = NULL;

  //Load the Glade file and instiate its widgets:
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
		try
		{
		  refXml = Gnome::Glade::Xml::create( gladeFileName );
		}
		catch(const Gnome::Glade::XmlError& ex)
		{
		  std::cerr << ex.what() << std::endl;
		  // TODO do something to exit, catch or throw.
		  //return 1;
		}
	#else
		std::auto_ptr<Gnome::Glade::XmlError> error;
		refXml = Gnome::Glade::Xml::create( gladeFileName, "", "", error);
		if(error.get())
		{
		  std::cerr << error->what() << std::endl;
		  // TODO do something to exit, catch or throw.
		  //return 1;
		}
	#endif	

	// Get the Glade-instantiated windows, dialogs, etc.
	refXml->get_widget("ToolchainWindow", toolchainWindow);
	refXml->get_widget("treeview1", treeView);
	refXml->get_widget("textview1", textView);
	refXml->get_widget("scrolledwindow5", editView);
	
	if( treeView )
	{
		// Create the Tree model
		refTreeViewModel = Gtk::TreeStore::create(treeViewColumns);
		treeView->set_model(refTreeViewModel);

		// Append columns
		treeView->append_column( "Name", treeViewColumns.col_name );
		treeView->append_column( "Description", treeViewColumns.col_description );

		// Connect signal:
		//treeView->signal_row_activated().connect(sigc::mem_fun(*this, &ToolchainWindowGTKMM::treeViewRowSelected) );

		// Get a selection object
		refTreeViewSelection = treeView->get_selection();
		
		// Connect signal
		refTreeViewSelection->signal_changed().connect(sigc::mem_fun(*this, &ToolchainWindowGTKMM::treeViewRowSelected) );
		
	}
	else
	{
		// TODO throw
	}
	
  if(toolchainWindow)
  {
		connectSignals();
    toolchainWindow->show_all();
    displayToolchain();
 		
 		kit->run();
	};
}

//-----------------------------------------------------------------------------

ToolchainWindowGTKMM::~ToolchainWindowGTKMM( )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Destroying a ToolchainWindowGTKMM object.\n";
#endif	

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::connectSignals()
{

  //Get the Glade-instantiated Button, and connect a signal handler:
  Gtk::ToolButton* pToolButton = 0;


  // New button
  refXml->get_widget("toolbutton5", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::newButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }


  // Save button
  refXml->get_widget("toolbutton2", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::saveToolchain) );
  }
  else
  {
  	// TODO throw error
  }


  // Save as button
  refXml->get_widget("toolbutton1", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &EngineGTKMM::saveAsToolchain) );
  }
  else
  {
  	// TODO throw error
  }
  
  // Open button
  refXml->get_widget("toolbutton4", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::openButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Add button
  refXml->get_widget("toolbutton6", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::addButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Add child button
  refXml->get_widget("toolbutton10", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::addChildButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }  
  
  
  // Delete button
  refXml->get_widget("toolbutton7", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::deleteButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Up button
  refXml->get_widget("toolbutton12", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::upButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Down button
  refXml->get_widget("toolbutton13", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::downButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }    
  
   
  // Left button
  refXml->get_widget("toolbutton3", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::leftButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }
  
  
  // Right button
  refXml->get_widget("toolbutton9", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::rightButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }    
   
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::displayToolchain( )
{


	Gtk::TreeModel::Row row;
	Toolchain* toolchain = NULL;
	
	// Clear out old data.
	refTreeViewModel->clear();
	
	
	// Loop over all the toolchains in the engine.
	for( int i = 0; i < this->getToolchainsSize(); i++ )
	{
		toolchain = this->getToolchain(i);

		// Add the toolchain to the treeview
		row = *(refTreeViewModel->append());
		row[treeViewColumns.col_name] = toolchain->getName();
		row[treeViewColumns.col_description] = toolchain->getDescription();
		row[treeViewColumns.col_nodePointer] = toolchain;		
				
		// Add childeren of the toolchain to the treeview
		addChilderenToTree( toolchain, &row );
		
		// Add an empty row for clear views on the different Toolchain objects.
		refTreeViewModel->append();
	};

	// TODO make the expand more sefisticated remember what was expended and what not.
	treeView->expand_all();
	
	
	// TODO should this be here
	// Set the current selection in the treeview
	if( this->getCurrentToolchainNode() )
	{
		for( Gtk::TreeModel::iterator iter = refTreeViewModel->children().begin(); iter != refTreeViewModel->children().end(); iter++ )
		{
			if(iter)
			{
				if( (*iter)[treeViewColumns.col_nodePointer] == this->getCurrentToolchainNode() )
				{
					refTreeViewSelection->select(iter);
					treeView->show_all();
					break;
				}
			}		
		}
  }
	
};

//-----------------------------------------------------------------------------


void ToolchainWindowGTKMM::addToolchainOperation()
{
	
	ToolchainNode* node = NULL;
	
	
	// Start a dialog to select the operation type
	DialogOperationChooserGTKMM dialog( (Gtk::Window*)this );
	
	
	// Add a toolchain if one excits
	if( this->getToolchainsSize() == 0 )
	{			
		this->newButton_clicked();
	}

	
	// Add the row to the current toolchain if no row is selected.
	Gtk::TreeModel::iterator iter = refTreeViewSelection->get_selected();
	if( !iter )
	{
		// No row is selected, insert the row at the end of the toolchain
		Toolchain* toolchain = this->getCurrentToolchain();
		dialog.chooseOperationNode( toolchain );

		// Display the toolchain with the new node.
		this->displayToolchain();

	}
	else
	{
		// See if not an empty row is selected
		if( (*iter)[treeViewColumns.col_nodePointer] )
		{
			// Insert the row at the index of the selected row.
			ToolchainNode* toolchainNode = this->getCurrentToolchainNode();
			ToolchainNode* parent = toolchainNode->getParentNode();
			
			// See if a Toolchain object is selected
			if( !parent )
			{
				dialog.chooseOperationNode( toolchainNode );
			}
			else // A toolchainNode is selected
			{
				dialog.chooseOperationNode( parent, toolchainNode->getNodeIndex() + 1 );
			}

			// Display the toolchain with the new node.
			this->displayToolchain();
		}

	}
	
	
	
	
};


//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::addChildToolchainOperation()
{
	ToolchainNode* node = NULL;
	
	
	// Start a dialog to select the operation type
	DialogOperationChooserGTKMM dialog( (Gtk::Window*)this );
	
	
	// Add a toolchain if one excits
	if( this->getToolchainsSize() == 0 )
	{			
		this->newButton_clicked();
	}

	
	// Add the row to the current toolchain if no row is selected.
	Gtk::TreeModel::iterator iter = refTreeViewSelection->get_selected();
	if( !iter )
	{
		// No row is selected, insert the row at the end of the toolchain
		Toolchain* toolchain = this->getCurrentToolchain();
		dialog.chooseOperationNode( toolchain );

		// Display the toolchain with the new node.
		this->displayToolchain();

	}
	else
	{
		// See if not an empty row is selected
		if( (*iter)[treeViewColumns.col_nodePointer] )
		{
			ToolchainNode* toolchainNode = this->getCurrentToolchainNode();
	
			// See if a Toolchain object is selected
			if( toolchainNode )
			{
				dialog.chooseOperationNode( toolchainNode );
				
				// Display the toolchain with the new node.
				this->displayToolchain();
			}


		}

	}
		
};


//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::modifyToolchainNode()
{
	
	ToolchainNode* node = this->getCurrentToolchainNode();
	if( node )
	{

		updateTextView();
		
		// Remove the old edit widget
		if( editConnection1 )
		{
			editView->remove();
			editConnection1.disconnect();
			editConnection2.disconnect();
		}
		
		
		
		// Create a new edit widget
		EditToolchainNodeGTKMM* editWidget = EditToolchainNodeGTKMM::newNodeEditWidget( node );
		Gtk::Widget* widget = editWidget;
		editView->add( *widget );
		
		// Connect signals
		editConnection1 = editWidget->signal_changed().connect( sigc::mem_fun(*this, &ToolchainWindowGTKMM::displayToolchain) ); 
		editConnection2 = editWidget->signal_changed().connect( sigc::mem_fun(*this, &ToolchainWindowGTKMM::updateTextView) ); 
	}
	
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::newButton_clicked()
{
	// Create a new toolchain and add it to the list.
	Toolchain* newToolchain = new Toolchain();	
	this->addToolchain( newToolchain );
	
	// Give the toolchain a default name and description
	stringstream ss;
	ss << "Toolchain #" << this->getToolchainsSize();
	newToolchain->setName( ss.str() );
	newToolchain->setDescription( "Describe me!" );

	// Display the new toolchain	
	this->displayToolchain();
};
	
	
		
//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::openButton_clicked()
{
	this->loadToolchain();
	this->displayToolchain();
}
		
//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::addButton_clicked()
{
	this->addToolchainOperation();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::addChildButton_clicked()
{
	this->addChildToolchainOperation();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::deleteButton_clicked()
{
	ToolchainNode* node = this->getCurrentToolchainNode();
	ToolchainNode* parent = node->getParentNode();
	
	if( node && parent )
	{
		// Remove the node from the toolchain
		if( parent->removeNode( node ) ) delete node;
	}
	else if( node ) // The node is a toolchain object
	{
		// TODO Ask before delete if alterations have been made.
		int index = this->getCurrentToolchainIndex();
		this->deleteToolchain( index );
	}
	
	displayToolchain();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::upButton_clicked()
{
	ToolchainNode* node = this->getCurrentToolchainNode();
	if( node->moveNodeUp() ) displayToolchain();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::downButton_clicked()
{
	ToolchainNode* node = this->getCurrentToolchainNode();
	if( node->moveNodeDown() ) displayToolchain();
};


//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::leftButton_clicked()
{
	ToolchainNode* node = this->getCurrentToolchainNode();
	if( node->moveNodeLeft() ) displayToolchain();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::rightButton_clicked()
{
	ToolchainNode* node = this->getCurrentToolchainNode();
	if( node->moveNodeRight() ) displayToolchain();
};


//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::treeViewRowSelected( ) //const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
  Gtk::TreeModel::iterator iter = refTreeViewSelection->get_selected();
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    // Change the current ToolchainNode and Toolchain objects.
		this->setCurrentToolchainNode( row[treeViewColumns.col_nodePointer] );
		modifyToolchainNode();
  }

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::updateTextView()
{
	
	ToolchainNode* node = this->getCurrentToolchainNode();
	if( node )
	{
		// Fill the text edit widget
		Glib::RefPtr<Gtk::TextBuffer> buffer = textView->get_buffer();
		Glib::ustring text = node->toString();
		buffer->set_text( text );
	}
	
};

//-----------------------------------------------------------------------------
		
		
void ToolchainWindowGTKMM::addChilderenToTree( ToolchainNode* parent, Gtk::TreeModel::Row* parentRow )
{

	Gtk::TreeModel::Row childRow;
	ToolchainNode* node = NULL;	

	// Loop over all childeren
	for( int i = 0; i < parent->getNodeVectorSize(); i++ )
	{
		// Get the child node
		node = parent->getChildNode(i);
		
		// Make a new child row
		childRow = *(refTreeViewModel->append(parentRow->children()));
		
		// Add data to the row
		childRow[treeViewColumns.col_name] = node->getName();
		childRow[treeViewColumns.col_description] = node->getDescription();
		childRow[treeViewColumns.col_nodePointer] = node;
		
		
		// If this node has childeren of its own, add them to the tree.
		if( node->getNodeVectorSize() > 0 )
		{
			addChilderenToTree( node, &childRow );
		}
		
	};

};



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

