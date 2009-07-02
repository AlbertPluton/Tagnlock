

#include "FieldSpinEditWidgetGTKMM.h"
#include <cmath>


//-----------------------------------------------------------------------------

FieldSpinEditWidgetGTKMM::FieldSpinEditWidgetGTKMM( Field* pField, int i )	: FieldEditWidgetGTKMM( pField, i ), 
																																							labelMax("Maximum value: ", 0.98, 0.5), 
																																							labelMin("Minimum value: ", 0.98, 0.5),
																																							labelStepsize("Stepsize: ", 0.98, 0.5),
																																							labelAdhereStep("Adhere the stepsize: ", 0.98, 0.5),
																																							labelDec("Number of decimal digits: ", 0.98, 0.5),
																																							labelAlwaysUpdate("Always update: ", 0.98, 0.5)
{


	// Cast the baseField pointer to a SpinField object for easy acces.
	try
	{
		spinField = static_cast<SpinField*>(pField);
	}
	catch( exception& e )
	{
		throw e;
	}

	// Obtain the maximum/minimum value the spin field can get.
	// A NULL pointer means no boundary.
	double* max = spinField->getMaximum();
	double* min = spinField->getMinimum();

	Gtk::Adjustment* adjustment = NULL;


	// Setup the maximum value line ---------------------------------
	this->attach( labelMax, 0, 1, 4, 5, attachX, attachY ); 
	hBoxMax.pack_start( checkMax, false, false, 5 );	
	hBoxMax.pack_start( spinMax, 	true, true, 5 );
	this->attach( hBoxMax, 	1, columns, 4, 5, attachX, attachY );
	adjustment = spinMax.get_adjustment();
			
	// If the pointer max equals to NULL it means there is no maximum.
	// In this case the checkMax button should not be selected.
	if( max == NULL )
	{
		checkMax.set_active( false );
	}
	else
	{
		checkMax.set_active( true );			
		spinMax.set_value( *max );
	}
	
	// The check button determinse whether or not the a boundary is used.
	// If not, deactivate the maximum value spinbuttorn.
	spinMax.set_sensitive( checkMax.get_active() );

#ifdef TODO_DEF
#warning TODO FieldSpinEditWidgetGTKMM::FieldSpinEditWidgetGTKMM: Not so nicely solved the problem of having no upper or lower boundary by setting it to -+1000000.
#endif
	if( min != NULL ){ adjustment->set_lower( *min ); } else { adjustment->set_lower( -1000000 );  } 
	adjustment->set_upper( 1000000 );
	adjustment->set_step_increment( 1 );
	adjustment->set_page_increment( 10 );		
	spinMax.set_numeric();
	spinMax.set_update_policy( Gtk::UPDATE_ALWAYS );
	spinMax.update();
	

	
	// Setup the minimum value line ---------------------------------
	this->attach( labelMin, 0, 1, 5, 6, attachX, attachY ); 
	hBoxMin.pack_start( checkMin, false, false, 5 );	
	hBoxMin.pack_start( spinMin, 	true, true, 5 );
	this->attach( hBoxMin, 	1, columns, 5, 6, attachX, attachY );
	adjustment = spinMin.get_adjustment();
	
	// If the pointer min equals to NULL it means there is no minimum.
	// In this case the checkMin button should not be selected.
	if( min == NULL )
	{
		checkMin.set_active( false );
	}
	else
	{
		checkMin.set_active( true );			
		spinMin.set_value( *min );
	}		

	// The check button determinse whether or not the a boundary is used.
	// If not, deactivate the minimum value spinbuttorn.		
	spinMin.set_sensitive( checkMin.get_active() );

#ifdef TODO_DEF
#warning TODO FieldSpinEditWidgetGTKMM::FieldSpinEditWidgetGTKMM: Not so nicely solved the problem of having no upper or lower boundary by setting it to -+1000000.
#endif				
	if( max != NULL ){ adjustment->set_upper( *max ); } else { adjustment->set_upper( 1000000 );  } 		
	adjustment->set_lower( -1000000 );
	adjustment->set_step_increment( 1 );
	adjustment->set_page_increment( 10 );
	spinMin.set_numeric();
	spinMin.set_update_policy( Gtk::UPDATE_IF_VALID );	
	spinMin.update();

	
	
	
	// Setup the stepsize line --------------------------------------
	this->attach( labelStepsize, 0, 1, 6, 7, attachX, attachY ); 
	this->attach( spinStepsize, 1, columns, 6, 7, attachX, attachY ); 
	adjustment = spinStepsize.get_adjustment();
	adjustment->set_upper( 1000000 );  		
	adjustment->set_lower( -1000000 );
	// Set teh increment rate depending on the number of digits the base field has.
	if( spinField->getDecimals() != 0 )
	{	
		double value = 1.0 / pow(10.0, spinField->getDecimals());
		adjustment->set_step_increment( value );
		adjustment->set_page_increment( 10*value );	
	}
	else
	{
		adjustment->set_step_increment( 1 );
		adjustment->set_page_increment( 10 );
	}
	spinStepsize.set_numeric();
	spinStepsize.set_digits( spinField->getDecimals() );
	spinStepsize.set_update_policy( Gtk::UPDATE_ALWAYS );	
	spinStepsize.set_value( spinField->getStepsize() );
	spinStepsize.update();
	
	
	
	
	// Setup the adhere step line -----------------------------------
	this->attach( labelAdhereStep, 0, 1, 7, 8, attachX, attachY ); 
	this->attach( toggleAdhereStep, 1, columns, 7, 8, attachX, attachY ); 
	toggleAdhereStep.set_active( spinField->getAdhereStep() );


	
	
	// Setup the decimal line --------------------------------------
	this->attach( labelDec, 0, 1, 8, 9, attachX, attachY ); 
	this->attach( spinDec, 1, columns, 8, 9, attachX, attachY ); 
	adjustment = spinDec.get_adjustment();
	adjustment->set_upper( 1000000 );  		
	adjustment->set_lower( 0 );
	adjustment->set_step_increment( 1 );
	adjustment->set_page_increment( 10 );	
	spinDec.set_numeric();
	spinDec.set_digits( 0 );
	spinDec.set_snap_to_ticks(true);
	spinDec.set_update_policy( Gtk::UPDATE_IF_VALID );	
	spinDec.set_value( spinField->getDecimals() );
	spinDec.update();
	
	
	
	// Setup the adhere decimal line -----------------------------------
	this->attach( labelAlwaysUpdate, 0, 1, 9, 10, attachX, attachY ); 
	this->attach( toggleAlwaysUpdate, 1, columns, 9, 10, attachX, attachY ); 
	toggleAlwaysUpdate.set_active( spinField->getAlwaysUpdate() );
	
	
		
		
		
	// Connect the signals
	spinMax.signal_value_changed().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::changeMax) );	
	checkMax.signal_clicked().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::activateMax) );
	
	spinMin.signal_value_changed().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::changeMin) );	
	checkMin.signal_clicked().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::activateMin) );
	
	spinStepsize.signal_value_changed().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::changeStepsize) );	
	toggleAdhereStep.signal_clicked().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::changeAdhereStep) );
	
	spinDec.signal_value_changed().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::changeDec) );		
	toggleAlwaysUpdate.signal_clicked().connect( sigc::mem_fun(this, &FieldSpinEditWidgetGTKMM::changeAlwaysUpdate) );			
	
		
	this->show_all();		
};

//-----------------------------------------------------------------------------

FieldSpinEditWidgetGTKMM::~FieldSpinEditWidgetGTKMM()
{

};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::changeMax( )
{

	// Update the value of the max
	double max = spinMax.get_value();
	spinField->setMaximum( &max );

	// Get the adjustment object of the MINimum spinbutton
	Gtk::Adjustment* adjustment_min = spinMin.get_adjustment();
	// Set the highest possible value for the minimum to max.
	adjustment_min->set_upper( max );	
	
	m_signal_changed_property.emit( );

};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::changeMin( )
{
	double min = spinMin.get_value();
	spinField->setMinimum( &min );

	// Get the adjustment object of the MAXimum spinbutton
	Gtk::Adjustment* adjustment_max = spinMax.get_adjustment();
	// Set the lowest possible value for the maximum to min.
	adjustment_max->set_lower( min );
	
	m_signal_changed_property.emit( );

};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::activateMax( )
{
	// Get the adjustment object of the MINimum spinbutton
	Gtk::Adjustment* adjustment_min = spinMin.get_adjustment();
	
	if( checkMax.get_active() )
	{
		// Set the spinbutton sensitive to input.
		spinMax.set_sensitive( true );
		
		// Update the maximum value.
		double max = spinMax.get_value();
		spinField->setMaximum( &max );	
		
		// Set the highest possible value for the minimum to max.
		adjustment_min->set_upper( max );		
	}
	else
	{
		spinMax.set_sensitive( false );
		spinField->setMaximum( NULL );
#ifdef TODO_DEF
#warning TODO FieldSpinEditWidgetGTKMM::activateMax: Not so nicely solved the problem of having no upper or lower boundary by setting it to -+1000000.
#endif			
		adjustment_min->set_upper( 1000000 );
	}
	
	
	m_signal_changed_property.emit( );
	
		
};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::activateMin( )
{
	// Get the adjustment object of the MAXimum spinbutton
	Gtk::Adjustment* adjustment_max = spinMax.get_adjustment();

	if( checkMin.get_active() )
	{
		// Set the spinbutton sensitive to input.
		spinMin.set_sensitive( true );
		
		// Update the minimum value.
		double min = spinMin.get_value();
		spinField->setMinimum( &min );	
		
		// Set the lowest possible value for the maximum to min.
		adjustment_max->set_lower( min );
	}
	else
	{
		spinMin.set_sensitive( false );
		spinField->setMinimum( NULL );
#ifdef TODO_DEF
#warning TODO FieldSpinEditWidgetGTKMM::activateMin: Not so nicely solved the problem of having no upper or lower boundary by setting it to -+1000000.
#endif			
		adjustment_max->set_lower( -1000000 );
	}
	
	m_signal_changed_property.emit( );
		
};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::changeStepsize( )
{
	spinField->setStepsize( spinStepsize.get_value() );
	
	m_signal_changed_property.emit( );
	
};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::changeDec( )
{
	// Update the number of decimals of the base field
	spinField->setDecimals( spinDec.get_value() );


	// Update the stepsize accordingly.

	Gtk::Adjustment* adjustment = spinStepsize.get_adjustment();

	// Set the increment rate depending on the number of digits the base field has.
	double value = 1;
	if( spinField->getDecimals() != 0 )
	{	
		value = 1.0 / pow(10.0, spinField->getDecimals());	
		adjustment->set_step_increment( value );
		adjustment->set_page_increment( 10*value  );	
	}
	else
	{
		value = 1;
		adjustment->set_step_increment( 1 );
		adjustment->set_page_increment( 10 );
	}

	// Increase the stepsize if it is to small.
	if( spinStepsize.get_value() < value ) spinStepsize.set_value( value );
	
#ifdef TODO_DEF
#warning TODO FieldSpinEditWidgetGTKMM::changeDec: Get the "what you see is what you get" to work.
#endif			
/*
	// Round of the stepsize, this is to make sure no nasty things remain unseen in the spinbutton but keep incrementing the value. In other words what you see is what you get.
	double remainder = fmod(spinStepsize.get_value(), value);
	double temp = spinStepsize.get_value();
	if( remainder != 0) spinStepsize.set_value( spinStepsize.get_value() - remainder );
  cout << "value: " << value << "\tspinStepsize.get_value(): " << spinStepsize.get_value() << "\tremainer: " << remainder << "\ttemp" << temp << "\n";
*/

	// Set the number of digits in the Stepsize spinbutton.
	spinStepsize.set_digits( spinField->getDecimals() );
	
	spinStepsize.update();

	spinField->setStepsize( spinStepsize.get_value() );

	m_signal_changed_property.emit( );

};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::changeAdhereStep( )
{
	spinField->setAdhereStep( toggleAdhereStep.get_active() );

	m_signal_changed_property.emit( );
};

//-----------------------------------------------------------------------------

void FieldSpinEditWidgetGTKMM::changeAlwaysUpdate( )
{
	spinField->setAlwaysUpdate( toggleAlwaysUpdate.get_active() );
	

	m_signal_changed_property.emit( );
	
};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------




