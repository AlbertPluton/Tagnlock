

#include "FieldComboEditWidgetGTKMM.h"



//-----------------------------------------------------------------------------

FieldComboEditWidgetGTKMM::FieldComboEditWidgetGTKMM( Field* pField, int i ) : 	FieldEditWidgetGTKMM( pField, i ),
																																								labelOptions( "Options: ", 0.98, 0.5),
																																								addButton( Gtk::Stock::ADD ),
																																								delButton( Gtk::Stock::DELETE ),
																																								upButton( Gtk::Stock::GO_UP ),
																																								downButton( Gtk::Stock::GO_DOWN )
{

	// Cast the baseField pointer to a ComboField object for easy acces.
	try
	{
		comboField = static_cast<ComboField*>(pField);
	}
	catch( exception& e )
	{
		throw e;
	}
	
	// Add the three view to the scrolled window.
	treeScrolledWindow.add( treeView );

  // Only show the scrollbars when they are necessary.
  treeScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

	// Add the scrolled window and buttons to the box.
	hBoxOptions.pack_start( treeScrolledWindow );
	hBoxOptions.pack_start( vBoxButtons , Gtk::PACK_SHRINK );
	
	vBoxButtons.pack_start( addButton );
	vBoxButtons.pack_start( delButton );
	vBoxButtons.pack_start( upButton );
	vBoxButtons.pack_start( downButton );
	
	// Create the Tree model.
 	treeModel = Gtk::ListStore::create(m_Columns);
  treeView.set_model( treeModel );

	// Add the options to the tree.
	if( comboField->getComboSize() > 0 );
	{
		// Add the first option
		Gtk::TreeModel::Row row = *(treeModel->append());
		row[m_Columns.columnOption] = comboField->getComboElement( 0 );
				
		// Add further options
		for( int i = 1; i < comboField->getComboSize(); i++ )
		{
			row = *(treeModel->append());
			row[m_Columns.columnOption] = comboField->getComboElement( i );
		};
		
	}

	// Add the TreeView's view columns.
	treeView.append_column_editable("Options", m_Columns.columnOption);

	// Make the column editable.
	Gtk::CellRendererText* cellRenderer = (Gtk::CellRendererText*)treeView.get_column_cell_renderer( 0 );
	cellRenderer->property_editable_set() = true;

	// Attach the options to the table
	this->attach( labelOptions, 0, 1, 4, 5, attachX, attachY|Gtk::EXPAND ); 
	this->attach( hBoxOptions, 	1, columns, 4, 5, attachX, attachY|Gtk::EXPAND );	


	this->show_all();
	
};

//-----------------------------------------------------------------------------

FieldComboEditWidgetGTKMM::~FieldComboEditWidgetGTKMM()
{

}

//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::addedOption()
{

};


//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::removedOption()
{

};


//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::changedOption()
{

};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

