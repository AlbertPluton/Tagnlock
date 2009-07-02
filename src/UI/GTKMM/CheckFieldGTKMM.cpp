//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
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
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getData
#endif	
};


//-----------------------------------------------------------------------------

				
void CheckFieldGTKMM::setData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::setData
#endif	
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


