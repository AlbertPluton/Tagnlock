

#include "FieldComboEditWidgetGTKMM.h"
#include <sstream>
#include <string>


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
	
	
	selectedOption = -1;
	
	
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
		row[m_Columns.columnIndex] = 0;
		
		// Add further options
		for( int i = 1; i < comboField->getComboSize(); i++ )
		{
			row = *(treeModel->append());
			row[m_Columns.columnOption] = comboField->getComboElement( i );
			row[m_Columns.columnIndex] = i;
		};
		
	}

	// Add the TreeView's view columns.
	treeView.append_column_editable("Options", m_Columns.columnOption);

	// Make the column editable.
	Gtk::CellRendererText* cellRenderer = (Gtk::CellRendererText*)treeView.get_column_cell_renderer( 0 );
	cellRenderer->property_editable_set() = true;
	
	// Connect the signal from the renderer to the function changedOption.
	cellRenderer->signal_edited().connect( sigc::mem_fun( *this, &FieldComboEditWidgetGTKMM::changedOption) );

	// Connect the signals from the buttons.
	addButton.signal_clicked().connect( sigc::mem_fun( *this, &FieldComboEditWidgetGTKMM::addedOption) );
	delButton.signal_clicked().connect( sigc::mem_fun( *this, &FieldComboEditWidgetGTKMM::removedOption) );
	upButton.signal_clicked().connect( sigc::mem_fun( *this, &FieldComboEditWidgetGTKMM::movedOptionUp) );
	downButton.signal_clicked().connect( sigc::mem_fun( *this, &FieldComboEditWidgetGTKMM::movedOptionDown) );


 	treeSelection = treeView.get_selection();
  // When clicking on a field in the tree view of the category window, change the selection
 	treeSelection->signal_changed().connect( sigc::mem_fun(this, &FieldComboEditWidgetGTKMM::changedSelectedOption) );



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

	// Add default option to the base field.
	comboField->addComboElement( "NEW OPTION" );
		
		
	// Add it to the tree 
	Gtk::TreeModel::Row row = *(treeModel->append());
	row[m_Columns.columnOption] = comboField->getComboElement( comboField->getComboSize()-1 );
	row[m_Columns.columnIndex] = comboField->getComboSize()-1;	


	// Emit the update properties signal.	
	m_signal_changed_property.emit( );


};



//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::removedOption()
{

	if( selectedOption >= 0 )
	{

		// Open a dialog to ask if this is really whats required.
		Gtk::MessageDialog dialog("Do you really want to delete the selected option?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO  );

		//Show the dialog and wait for a user response:
		int result = dialog.run();

		//Handle the response:
		switch(result)
		{
		  case(Gtk::RESPONSE_YES):
		  {
		  	// Remove the selected option from the base field.
		  	comboField->removeComboElement( selectedOption );
		  	
		  	// Clear the tree model.
		  	treeModel->clear();
		  	
				// Add the options to the tree.
				if( comboField->getComboSize() > 0 );
				{
					// Add the first option
					Gtk::TreeModel::Row row = *(treeModel->append());
					row[m_Columns.columnOption] = comboField->getComboElement( 0 );
					row[m_Columns.columnIndex] = 0;
		
					// Add further options
					for( int i = 1; i < comboField->getComboSize(); i++ )
					{
						row = *(treeModel->append());
						row[m_Columns.columnOption] = comboField->getComboElement( i );
						row[m_Columns.columnIndex] = i;
					};

					treeSelection->unselect_all();
					selectedOption = -1;
				
				
					// Emit the update properties signal.	
					m_signal_changed_property.emit( );		
				
				}    	
		    
		    break;
		  }
		  default:
			{
		    break;
		  }
		}

	}

};


//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::movedOptionUp()
{
	// Perform the operation if the selected option is not the first.
	if( selectedOption > 0 )
	{
		string temp_1 = comboField->getComboElement( selectedOption - 1 );
		Gtk::TreeModel::Row row = *(*iterSelectedOption);
		Glib::ustring temp_2u = row[m_Columns.columnOption];
		string temp_2 = temp_2u.raw();
		
		// Alter the baseFiels.
		comboField->setComboElement( selectedOption - 1, temp_2 );
		comboField->setComboElement( selectedOption, temp_1 );
		
		// Alter the tree model.
		row[m_Columns.columnOption] = temp_1;
		Gtk::TreeModel::iterator tempIt = iterSelectedOption;
		tempIt--;
		row = *(*tempIt);		
		row[m_Columns.columnOption] = temp_2;
		
		// Emit the update properties signal.	
		m_signal_changed_property.emit( );

		// Keep the selection with the original option.
		iterSelectedOption--;
		selectedOption--;
		treeSelection->select( iterSelectedOption );
	};
};

//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::movedOptionDown()
{
	// Perform the operation if the selected option is not the last option.
	if( (selectedOption < comboField->getComboSize()-1) && ( selectedOption >= 0 ) )
	{
		string temp_1 = comboField->getComboElement( selectedOption + 1 );
		Gtk::TreeModel::Row row = *(*iterSelectedOption);
		Glib::ustring temp_2u = row[m_Columns.columnOption];
		string temp_2 = temp_2u.raw();
		comboField->setComboElement( selectedOption + 1, temp_2 );
		comboField->setComboElement( selectedOption, temp_1 );

		// Alter the tree model.
		row[m_Columns.columnOption] = temp_1;
		Gtk::TreeModel::iterator tempIt = iterSelectedOption;
		tempIt++;
		row = *(*tempIt);		
		row[m_Columns.columnOption] = temp_2;

		// Emit the update properties signal.	
		m_signal_changed_property.emit( );
		
		// Keep the selection with the original option.
		iterSelectedOption++;
		selectedOption++;
		treeSelection->select( iterSelectedOption );
	
	};
};

//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::changedOption( const Glib::ustring& path_string, const Glib::ustring& new_text )
{
	stringstream convert;
	int index;
	
	// Convert the path into an integer index.
	convert << path_string.raw();
	convert >> index;

	// Set the new text in the base field.
	comboField->setComboElement( index, new_text );
	
	
	// Emit the update properties signal.
	m_signal_changed_property.emit( );
	
	
};

//-----------------------------------------------------------------------------

void FieldComboEditWidgetGTKMM::changedSelectedOption()
{
	treeSelection = treeView.get_selection();
	
	if(treeSelection)
	{
		iterSelectedOption = treeSelection->get_selected();
		if( iterSelectedOption )
		{ 	
			// Obtain the index of the selected field from the row.
			selectedOption= (*iterSelectedOption)[m_Columns.columnIndex];	
		}	
		else
		{
			// TODO throw exception
		}
	}
	else
	{
		// TODO throw exception
	}	

};

//-----------------------------------------------------------------------------

