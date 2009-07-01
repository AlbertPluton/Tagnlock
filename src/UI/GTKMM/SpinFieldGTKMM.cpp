//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
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

		
Gtk::Widget* SpinFieldGTKMM::getEditWidget()
{
	if( editWidget == NULL )
	{
		try
		{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getEditWidget 
#endif	
//			editWindow = 
		}
		catch( exception& e )
		{
			throw e;
		}	
	}
	return editWidget;
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


};


//-----------------------------------------------------------------------------

		
void SpinFieldGTKMM::getData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getData
#endif	
};


//-----------------------------------------------------------------------------

				
void SpinFieldGTKMM::setData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::setData
#endif	
};



//-----------------------------------------------------------------------------

Gtk::Widget* SpinFieldGTKMM::getEntry()
{
	return (Gtk::Widget*)(&spinButton);
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


