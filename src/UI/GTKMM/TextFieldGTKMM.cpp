//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
//
//
#include "TextFieldGTKMM.h"

//-----------------------------------------------------------------------------

	
TextFieldGTKMM::TextFieldGTKMM( Field* pField, FieldData* dat, int i ) : FieldGTKMM( pField, dat, i )
{
	// Fill the field with data.
 	if( data != NULL ) this->getData();

	// Connect signals to indicate a change in data.
	textEntry.signal_changed().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );

};


//-----------------------------------------------------------------------------

	
TextFieldGTKMM::~TextFieldGTKMM()
{

};


//-----------------------------------------------------------------------------

			
void TextFieldGTKMM::updateProperties()
{
	this->updatePropertiesParentClass();
	// No properties for this field.
};


//-----------------------------------------------------------------------------

		
void TextFieldGTKMM::getData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getData
#endif	
};


//-----------------------------------------------------------------------------

				
void TextFieldGTKMM::setData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::setData
#endif	
};



//-----------------------------------------------------------------------------

Gtk::Widget* TextFieldGTKMM::getEntry()
{
	return (Gtk::Widget*)(&textEntry);
};


//-----------------------------------------------------------------------------


Gtk::Widget* TextFieldGTKMM::getEditWidget()
{
	// Get the editWidget.
	FieldEditWidgetGTKMM* fieldEditWidgetGTKMM = FieldEditWidgetGTKMM::newEditWidget( this->getBaseField(), this->getIndex() );
		
	// Cast it to Gtk::Widget
	editWidget = (Gtk::Widget*)fieldEditWidgetGTKMM;
		
	// Connect the properties updated signal.
	fieldEditWidgetGTKMM->signal_changed_property().connect( sigc::mem_fun( *this, &TextFieldGTKMM::updateProperties) );
	
		
	return editWidget;
};


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


