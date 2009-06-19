//
//	Author: A.L. Hertog
//	Date: 12 May 2009
//	License: GPL
//
//


#include "CategoryTreeGTKMM.h"


//-----------------------------------------------------------------------------

CategoryTreeGTKMM::CategoryTreeGTKMM()
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

};


//-----------------------------------------------------------------------------

CategoryTreeGTKMM::~CategoryTreeGTKMM()
{

};

//-----------------------------------------------------------------------------

void CategoryTreeGTKMM::makeTreeModel( Category* cat )
{
	
	Field* field = NULL;
	
	Gtk::TreeModel::Row row;
		
	for( int i = 0; i < cat->getFieldsSize(); i++ )
	{
		row = *(categoryTreeModel->append());
		field = cat->getFieldAt(i);
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

CategoryTreeGTKMM::type_signal_selectionChange CategoryTreeGTKMM::get_signal_selectionChange( void )
{
	return signal_selectionChange;
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------



