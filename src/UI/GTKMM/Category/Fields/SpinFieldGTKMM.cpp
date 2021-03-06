//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//
#include "SpinFieldGTKMM.h"

//-----------------------------------------------------------------------------

	
SpinFieldGTKMM::SpinFieldGTKMM( Field* pField, FieldData* dat, int i ) : FieldGTKMM( pField, dat, i )
{

	// Fill the button with some data
	if( data != NULL ) this->getData();
	
	// Connect the signals.
	spinButton.signal_value_changed().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );

	this->updateProperties();

};


//-----------------------------------------------------------------------------

	
SpinFieldGTKMM::~SpinFieldGTKMM()
{

};


//-----------------------------------------------------------------------------


void SpinFieldGTKMM::updateProperties()
{

	SpinField* spinField = NULL;

	// Cast the baseField pointer to a SpinField object for easy acces.
	try
	{
		spinField = static_cast<SpinField*>(baseField);
	}
	catch( exception& e )
	{
		throw e;
	}
	
	Gtk::Adjustment* adjustment = spinButton.get_adjustment();

	// Obtain the maximum/minimum value the spin field can get.
	// A NULL pointer means no boundary.
	double* max = spinField->getMaximum();
	double* min = spinField->getMinimum();

	if( max != NULL ) 
	{
		adjustment->set_upper( *max );
	}
	else
	{
		adjustment->set_upper( defaultMaximum );
	}
	
	if( min != NULL ) 
	{
		adjustment->set_lower( *min );
	}
	else
	{
		adjustment->set_lower( defaultMinimum );
	}	
	
	adjustment->set_step_increment( spinField->getStepsize() );
	adjustment->set_page_increment( 10 * spinField->getStepsize() );
	spinButton.set_snap_to_ticks( spinField->getAdhereStep() );
	spinButton.set_numeric();
	spinButton.set_digits( spinField->getDecimals() );

	if( spinField->getAlwaysUpdate() ) 
	{
		spinButton.set_update_policy( Gtk::UPDATE_ALWAYS );
	}
	else
	{
		spinButton.set_update_policy( Gtk::UPDATE_IF_VALID );	
	}

	spinButton.update();

	this->updatePropertiesParentClass();

};


//-----------------------------------------------------------------------------

		
void SpinFieldGTKMM::getData()
{

	data->set( spinButton.get_value() );

};


//-----------------------------------------------------------------------------

				
void SpinFieldGTKMM::setData()
{

	spinButton.set_value( data->getDouble() );
	
};



//-----------------------------------------------------------------------------

Gtk::Widget* SpinFieldGTKMM::getEntry()
{
	return (Gtk::Widget*)(&spinButton);
};

//-----------------------------------------------------------------------------

Gtk::Widget* SpinFieldGTKMM::getEditWidget()
{

	// Get the editWidget.
	FieldEditWidgetGTKMM* fieldEditWidgetGTKMM = FieldEditWidgetGTKMM::newEditWidget( this->getBaseField(), this->getIndex() );
		
	// Cast it to a Gtk::Widget.
	editWidget = (Gtk::Widget*)fieldEditWidgetGTKMM;
		
	// Connect the properties updated signal.
	fieldEditWidgetGTKMM->signal_changed_property().connect( sigc::mem_fun( *this, &SpinFieldGTKMM::updateProperties) );
	
	return editWidget;
};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


