//
//	Author: A.L. Hertog
//	Date: 12 May 2009
//	License: GPL
//
//


#include "CategoryTreeGTKMM.h"


//-----------------------------------------------------------------------------

CategoryTreeGTKMM::CategoryTreeGTKMM( Category* cat )
{

	categoryColumns.add( columnIndex					);
 	categoryColumns.add( columnFieldType			);
 	categoryColumns.add( columnFieldLabel			);
 	categoryColumns.add( columnFieldRequired	);
 	categoryColumns.add( columnFieldReset			);
 	
 	categoryTreeModel = Gtk::TreeStore::create(categoryColumns);
  
  this->append_column( "Type", 			columnFieldType 		);
  this->append_column( "Label", 		columnFieldLabel 		);
  this->append_column( "Required", 	columnFieldRequired	);
  this->append_column( "Reset", 		columnFieldReset		);
 	
 	this->set_model( categoryTreeModel );
 	
 	categoryTreeSelection = this->get_selection();
  // When clicking on a field in the tree view of the category window, change the selection
 	categoryTreeSelection->signal_changed().connect( sigc::mem_fun(this, &CategoryTreeGTKMM::selectionChange) );

	this->show_all();

	if( cat != NULL )
	{
		this->makeTreeModel( category );
	};

};


//-----------------------------------------------------------------------------

CategoryTreeGTKMM::~CategoryTreeGTKMM()
{

};

//-----------------------------------------------------------------------------

void CategoryTreeGTKMM::makeTreeModel( Category* cat )
{
	
	category = cat;
	
	Field* field = NULL;
	
	Gtk::TreeModel::Row row;
		
	for( int i = 0; i < category->getFieldsSize(); i++ )
	{
		row = *(categoryTreeModel->append());
		field = category->getFieldAt(i);
		row[columnIndex] = i;
		row[columnFieldType] = field->getType();
		row[columnFieldLabel] = field->getLabel();
		row[columnFieldRequired] = field->getRequired();
		row[columnFieldReset] = field->getReset();
	};

};

//-----------------------------------------------------------------------------

void CategoryTreeGTKMM::clearTreeModel( void )
{


	categoryTreeModel.clear();
		
 	categoryTreeModel = Gtk::TreeStore::create(categoryColumns);

	this->set_model( categoryTreeModel );

};


//-----------------------------------------------------------------------------

void CategoryTreeGTKMM::selectionChange( void )
{

	categoryTreeSelection = this->get_selection();
	
	if(categoryTreeSelection)
	{
		
		Gtk::TreeModel::iterator iter = categoryTreeSelection->get_selected();
		if( iter )
		{ 	
			// Obtain the index of the slected field from the row.
			int selected = (*iter)[columnIndex];
			// Emit the signal with the index of the selected field.
			signal_selectionChange.emit( selected );			
		}	
	}
	

};

//-----------------------------------------------------------------------------

void CategoryTreeGTKMM::updateProperties()
{

	// Get the selection
	Gtk::TreeModel::iterator iter = categoryTreeSelection->get_selected();

	//If anything is selected.
	if(iter) 
	{
  	Gtk::TreeModel::Row row = *iter;
		Field* field = category->getFieldAt( row[columnIndex] );

		row[columnFieldLabel] = field->getLabel();
		row[columnFieldRequired] = field->getRequired();
		row[columnFieldReset] = field->getReset();

	};

};

//-----------------------------------------------------------------------------

CategoryTreeGTKMM::type_signal_selectionChange CategoryTreeGTKMM::get_signal_selectionChange( void )
{
	return signal_selectionChange;
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------



