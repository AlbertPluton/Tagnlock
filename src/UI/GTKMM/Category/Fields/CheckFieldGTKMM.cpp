//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

	
#include "CheckFieldGTKMM.h"

//-----------------------------------------------------------------------------

	
CheckFieldGTKMM::CheckFieldGTKMM( Field* pField, FieldData* dat, int i ) : FieldGTKMM( pField, dat, i )
{

	// Fill the field with some data.
	if( data != NULL ) this->getData();
	
	// Connect the clicked signal to the changed signal of this class.
	checkButton.signal_clicked().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );

};


//-----------------------------------------------------------------------------

	
CheckFieldGTKMM::~CheckFieldGTKMM()
{

};


//-----------------------------------------------------------------------------

		
void CheckFieldGTKMM::updateProperties()
{
	this->updatePropertiesParentClass();
	// No properties for this field.
};


//-----------------------------------------------------------------------------

		
void CheckFieldGTKMM::getData()
{

	data->set( checkButton.get_active() );

};


//-----------------------------------------------------------------------------

				
void CheckFieldGTKMM::setData()
{

	checkButton.set_active( data->getBool() );

};



//-----------------------------------------------------------------------------

Gtk::Widget* CheckFieldGTKMM::getEntry()
{
	return (Gtk::Widget*)(&checkButton);
};

//-----------------------------------------------------------------------------

Gtk::Widget* CheckFieldGTKMM::getEditWidget()
{

	// Get the editWidget.
	FieldEditWidgetGTKMM* fieldEditWidgetGTKMM = FieldEditWidgetGTKMM::newEditWidget( this->getBaseField(), this->getIndex() );
		
	editWidget = (Gtk::Widget*)fieldEditWidgetGTKMM;
		
	// Connect the properties updated signal.
	fieldEditWidgetGTKMM->signal_changed_property().connect( sigc::mem_fun( *this, &CheckFieldGTKMM::updateProperties) );
			
	return editWidget;
};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


