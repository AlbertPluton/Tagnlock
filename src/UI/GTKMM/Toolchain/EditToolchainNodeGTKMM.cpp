



#include "EditToolchainNodeGTKMM.h"

#include "EditExecuteSystemCommandGTKMM.h"
#include "EditTextFileStorageGTKMM.h"

//-----------------------------------------------------------------------------

EditToolchainNodeGTKMM::EditToolchainNodeGTKMM( ToolchainNode* pNode ) :	labelType("Type: ", 0.98, 0.5),
																																					labelName("Name: ", 0.98, 0.5),
																																					labelDescription("Description: ", 0.98, 0.5)
{
	
	// Set the pointer to the toolchainNode.
	node = pNode;

	// Set some properties of the table.
	attachX = Gtk::FILL|Gtk::EXPAND;
	attachY = Gtk::EXPAND;
	rows = 5;
	columns = 5;
	this->set_row_spacings(10);
		
	// Add the type
	type.set_label( node->getType() );	
	type.set_alignment(0, 0.5);
	this->attach( labelType, 0, 1, 0, 1, attachX, attachY);
	this->attach( type, 1, 3, 0, 1, attachX, attachY);	
	
	// Add the Name label and entry
	this->attach( labelName, 0, 1, 1, 2, attachX, attachY );
	this->attach( entryName, 1, columns, 1, 2, attachX, attachY );
	entryName.set_text( node->getName() );
	
	// Add the Description name and entry
	this->attach( labelDescription, 0, 1, 2, 3, attachX, attachY );
	this->attach( entryDescription, 1, columns, 2, 5, attachX, attachY );
	entryDescription.set_text( node->getDescription() );
	
	
	entryName.signal_changed().connect( sigc::mem_fun(this, &EditToolchainNodeGTKMM::changedName) );
	entryDescription.signal_changed().connect( sigc::mem_fun(this, &EditToolchainNodeGTKMM::changedDescription) );
	
	this->show_all();
	
};


//-----------------------------------------------------------------------------

EditToolchainNodeGTKMM::~EditToolchainNodeGTKMM( )
{

};


//-----------------------------------------------------------------------------


void EditToolchainNodeGTKMM::changedName()
{
	node->setName( entryName.get_text() );
	m_signal_changed.emit( );	
};

//-----------------------------------------------------------------------------

void EditToolchainNodeGTKMM::changedDescription()
{
	node->setDescription( entryDescription.get_text() );
	m_signal_changed.emit( );
};


//-----------------------------------------------------------------------------

EditToolchainNodeGTKMM* EditToolchainNodeGTKMM::newNodeEditWidget( ToolchainNode* pNode )
{

	EditToolchainNodeGTKMM* node = NULL;
	
	if( typeid(*pNode) == typeid(ExecuteSystemCommand) )
	{
		EditExecuteSystemCommandGTKMM* fullNode = new EditExecuteSystemCommandGTKMM( pNode );
		node = fullNode;
	}
	else if( typeid(*pNode) == typeid(TextFileStorage) )
	{
		EditTextFileStorageGTKMM* fullNode = new EditTextFileStorageGTKMM( pNode );
		node = fullNode;
	}
	else if( (typeid(*pNode) == typeid(Toolchain)) || (typeid(*pNode) == typeid(ToolchainNode)) )
	{
		node = new EditToolchainNodeGTKMM( pNode );
	}
	else
	{
		// TODO throw
		cout << "ERROR in EditToolchainNodeGTKMM::newNodeEditWidget: unknown object type of pNode.\n";
	}
	
	return node;
	
};

//-----------------------------------------------------------------------------

EditToolchainNodeGTKMM::type_signal_changed EditToolchainNodeGTKMM::signal_changed()
{
  return m_signal_changed;
}


//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------



