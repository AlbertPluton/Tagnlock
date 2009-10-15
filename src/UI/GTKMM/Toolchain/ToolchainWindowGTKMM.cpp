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
	selectedRow = NULL;

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
	
	if( treeView )
	{
		// Create the Tree model
		refTreeViewModel = Gtk::TreeStore::create(treeViewColumns);
		treeView->set_model(refTreeViewModel);

		// Append columns
		treeView->append_column( "Name", treeViewColumns.col_name );
		treeView->append_column( "Description", treeViewColumns.col_description );

		//Connect signal:
		treeView->signal_row_activated().connect(sigc::mem_fun(*this, &ToolchainWindowGTKMM::treeViewRowSelected) );

	}
	else
	{
		// TODO throw
	}
	
  if(toolchainWindow)
  {
		connectSignals();
    toolchainWindow->show_all();
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
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::saveButton_clicked) );
  }
  else
  {
  	// TODO throw error
  }


  // Save as button
  refXml->get_widget("toolbutton1", pToolButton);
  if(pToolButton)
  {
    pToolButton->signal_clicked().connect( sigc::mem_fun( this, &ToolchainWindowGTKMM::saveAsButton_clicked) );
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
		
		// TODO add empty row??
	};
	
	
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

	
	// Add the row to the current toolchain.
	if( (selectedRow == NULL) )
	{
		// No row is selected, insert the row at the end of the toolchain
		Toolchain* toolchain = this->getCurrentToolchain();
		dialog.chooseOperationNode( toolchain );

		// Display the toolchain with the new node.
		this->displayToolchain();

	}
	else
	{
		// Insert the row at the index of the selected row.
		ToolchainNode* toolchainNode = this->getCurrentToolchainNode();
		ToolchainNode* parent = toolchainNode->getParentNode();
		dialog.chooseOperationNode( node, toolchainNode->getNodeIndex() );

		// Display the toolchain with the new node.
		this->displayToolchain();
		
	}
	
	
	
	
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::modifyToolchainNode()
{

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

void ToolchainWindowGTKMM::saveButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::saveAsButton_clicked()
{
	this->saveAsToolchain();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::openButton_clicked()
{
	if( this->loadToolchain() )
	{
		this->displayToolchain();
  };  
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::addButton_clicked()
{
	this->addToolchainOperation();
};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::deleteButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::upButton_clicked()
{

};

//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::downButton_clicked()
{

};


//-----------------------------------------------------------------------------

void ToolchainWindowGTKMM::treeViewRowSelected(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
  Gtk::TreeModel::iterator iter = refTreeViewModel->get_iter(path);
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
//    std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] << ", Name=" << row[m_Columns.m_col_name] << std::endl;
		
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

