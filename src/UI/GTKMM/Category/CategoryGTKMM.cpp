//
//	Author: A.L. Hertog
//	Date: 24 June 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#include "CategoryGTKMM.h"

#include <iostream>

//-----------------------------------------------------------------------------

Gtk::AttachOptions CategoryGTKMM::tableAttachX = defaultTableAttachX;
Gtk::AttachOptions CategoryGTKMM::tableAttachY = defaultTableAttachY;
		
int CategoryGTKMM::columns = defaultColumns; 
int CategoryGTKMM::tablePaddingX = defaultPaddingX;
int CategoryGTKMM::tablePaddingY = defaultPaddingY;
		
		
//-----------------------------------------------------------------------------

CategoryGTKMM::CategoryGTKMM( )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing CategoryGTKMM	object.\n";
#endif

	tableAttachX = Gtk::FILL|Gtk::EXPAND;
	tableAttachY = Gtk::EXPAND;

	objectData = NULL;
	categoryTree = new CategoryTreeGTKMM();

	categoryFieldEditWindow = NULL;
	categoryFieldEditWidget = NULL;

	this->set_homogeneous(false);
	this->show();
	this->set_child_visible();	


	// Connect the signal of the Configuration base class to go parse.
//	signal_parse().connect( sigc::mem_fun(this, &CategoryGTKMM::parseToConfig) );

	// Extract configuration data from the map
	this->updateFromConfig();



};

//-----------------------------------------------------------------------------

CategoryGTKMM::CategoryGTKMM( Gtk::ScrolledWindow* catTreeWindow, Gtk::ScrolledWindow* editWindow  )
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing CategoryGTKMM	object.\n";
#endif

	tableAttachX = Gtk::FILL|Gtk::EXPAND;
	tableAttachY = Gtk::EXPAND;

	objectData = NULL;
	categoryTree = new CategoryTreeGTKMM();
	categoryTreeWindow = catTreeWindow;
	categoryTreeWindow->add( (Gtk::Widget&)(*categoryTree) );

	categoryFieldEditWindow = editWindow;
	categoryFieldEditWidget = NULL;

	categoryTree->get_signal_selectionChange().connect( sigc::mem_fun(this, &CategoryGTKMM::fieldSelected) );

	this->set_homogeneous(false);
	this->show();
	this->set_child_visible();	



};

//-----------------------------------------------------------------------------

CategoryGTKMM::~CategoryGTKMM()
{
#ifdef DEBUG_MESSAGES_DEF
	cout << "Destroyed a CategoryGTKMM object.\n";
#endif
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::addField( FieldGTKMM* field )
{

	int index = field->getIndex();


	// Attach the label.
	this->attach( *(field->getLabel()), 0, 1, index, index+1, tableAttachX, tableAttachY, tablePaddingX, tablePaddingY );
	
	// Attach the entry field.
	this->attach( *(field->getEntry()), 1, columns-2, index, index+1, tableAttachX, tableAttachY, tablePaddingX, tablePaddingY );

	// Attach the required button.
	this->attach( *(field->getRequired()), columns-2, columns-1, index, index+1, tableAttachX, tableAttachY, tablePaddingX, tablePaddingY );


	// Attach the reset button.
	this->attach( *(field->getReset()), columns-1, columns, index, index+1, tableAttachX, tableAttachY, tablePaddingX, tablePaddingY );
	

};

//----------------------------------------------------------------------------

void CategoryGTKMM::makeNewTable( Category* category )
{

	this->hide_all();

	FieldGTKMM* fieldGTKMM = NULL;
	int size = category->getFieldsSize();
	Field* field = NULL;
	
	// Disconnect excisting signals
/*	if( connections.size() > 0 )
	{
		for( int i = 0; i < connections.size(); i++ )
		{
			connections[i].disconnect();
		};		
		connections.clear();
	}
*/	
	for( int i = 0; i < size; i++ )
	{
		field = category->getFieldAt( i );
		if( objectData != NULL )
		{
			fieldGTKMM = FieldGTKMM::newFieldGTKMM( field, objectData->getDataAt(i), i );
		}
		else
		{
			fieldGTKMM = FieldGTKMM::newFieldGTKMM( field, i );		
		};
	
		this->addField( fieldGTKMM );
		
		fields.push_back( fieldGTKMM );
		
		// Create the connection the the childs signal and add the connection to the vector.
//		connections.push_back( (fieldGTKMM->get_signal_selected()).connect( sigc::mem_fun(this, &CategoryGTKMM::fieldSelected) ) );
	}
	
	categoryTree->makeTreeModel( category );
	
	this->show_all();
	
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::makeNewTable( ObjectData* object )
{
	makeNewTable( object->getCategory() );
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::fillTable( ObjectData* object )
{

	objectData = object;	

	for( int i = 0; i < fields.size(); i++ )
	{
		(fields[i])->setFieldData( object->getDataAt(i) );
		(fields[i])->setData();
	};
};


//-----------------------------------------------------------------------------

void CategoryGTKMM::readFromTable( ObjectData* object )
{
	for( int i = 0; i < fields.size(); i++ )
	{
		(fields[i])->setFieldData( object->getDataAt(i) );
		(fields[i])->getData();
	}
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::update( )
{

#ifdef TODO_DEF
#warning TODO in file __FILE__ at line __LINE__.
#endif

};

//-----------------------------------------------------------------------------

void CategoryGTKMM::clear(  )
{
	categoryTree->clearTreeModel();
	
	for( int i = 0; i < fields.size(); i++ )
	{
		FieldGTKMM* field = fields[i];
//		this->remove( (Gtk::Widget&)*field );
		this->remove( *(field->getLabel()) );
		this->remove( *(field->getEntry()) );
		this->remove( *(field->getRequired()) );
		this->remove( *(field->getReset())	);
		delete field;
	}
	
	// Clear out the fields vector	
	fields.clear();
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::fieldSelected( int fieldIndex )
{

	
	if(	(categoryFieldEditWidget != NULL) && (categoryFieldEditWindow != NULL) )
	{
		// Remove the old editWidget from the editWindow
		categoryFieldEditWindow->remove( );
	}


	// Pass the signal generated by the Field on to the EngineGTKMM.
	signal_selectionChange.emit( fieldIndex );
	
	// Get the new editWidget
	categoryFieldEditWidget = fields[ fieldIndex ]->getEditWidget();
	
	// Add the editWidget to the editWindow
	if( categoryFieldEditWindow != NULL ) categoryFieldEditWindow->add( *categoryFieldEditWidget );
	
	try
	{
		FieldEditWidgetGTKMM* temp_class = static_cast<FieldEditWidgetGTKMM*>(categoryFieldEditWidget);
		temp_class->signal_changed_property().connect( sigc::mem_fun(categoryTree, &CategoryTreeGTKMM::updateProperties) );
	}
	catch( exception& e )
	{
		// TODO Throw error.
	}
	
};

//-----------------------------------------------------------------------------

CategoryGTKMM::type_signal_selectionChange CategoryGTKMM::get_signal_selectionChange( void )
{
	return signal_selectionChange;
};

//-----------------------------------------------------------------------------


void CategoryGTKMM::setObjectData( ObjectData* data )
{
	objectData = data;
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::setColumns( int c  )
{
	columns = c;
};

//-----------------------------------------------------------------------------

int CategoryGTKMM::getColumns()
{
	return columns;
};


//-----------------------------------------------------------------------------

ObjectData* CategoryGTKMM::getObjectData()
{
	return objectData;
};

//-----------------------------------------------------------------------------

void CategoryGTKMM::parseToConfig()
{

	
	
	

};

//-----------------------------------------------------------------------------

void CategoryGTKMM::updateFromConfig()
{


};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

