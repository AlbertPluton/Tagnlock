

#include "FieldSpinEditWindowGTKMM.h"



//-----------------------------------------------------------------------------

FieldSpinEditWindowGTKMM::FieldSpinEditWindowGTKMM( Field* pField ) : FieldEditWindowGTKMM( pField ), 
																																			labelMax("Maximum value: ", 0.98, 0.5), 
																																			labelMin("Minimum value: ", 0.98, 0.5),
																																			labelStepsize("Stepsize: ", 0.98, 0.5),
																																			labelAdhereStep("Adhere the stepsize: ", 0.98, 0.5),
																																			labelDec("Number of decimal digits: ", 0.98, 0.5),
																																			labelAdhereDec("Adhere decimals: ", 0.98, 0.5)
{


		// Cast the baseField pointer to a SpinField object for easy acces.
		SpinField* spinField = static_cast<SpinField*>(pField);

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
		
		spinMax.set_sensitive( checkMax.get_active() );

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
		
		spinMin.set_sensitive( checkMin.get_active() );
				
		if( max != NULL ){ adjustment->set_upper( *max ); } else { adjustment->set_upper( 1000000 );  } 		
		adjustment->set_lower( -1000000 );
		adjustment->set_step_increment( 1 );
		adjustment->set_page_increment( 10 );
		spinMin.set_numeric();
		spinMin.set_update_policy( Gtk::UPDATE_ALWAYS );
		spinMin.update();

		
		
		// Setup the stepsize line --------------------------------------
		this->attach( labelStepsize, 0, 1, 6, 7, attachX, attachY ); 
		this->attach( spinStepsize, 1, columns, 6, 7, attachX, attachY ); 
		
		
		// Setup the adhere step line -----------------------------------
		this->attach( labelAdhereStep, 0, 1, 7, 8, attachX, attachY ); 
		this->attach( toggleAdhereStep, 1, columns, 7, 8, attachX, attachY ); 
		
		
		// Setup the decimal line --------------------------------------
		this->attach( labelDec, 0, 1, 8, 9, attachX, attachY ); 
		this->attach( spinDec, 1, columns, 8, 9, attachX, attachY ); 
		
		
		// Setup the adhere decimal line -----------------------------------
		this->attach( labelAdhereDec, 0, 1, 9, 10, attachX, attachY ); 
		this->attach( toggleAdhereDec, 1, columns, 9, 10, attachX, attachY ); 
		
		
/*
		Gtk::Label labelMax, labelMin, labelStepsize, labelAdhereStep, labelDec labelAdhereDec;
		Gtk::CheckButton checkMax, checkMin;
		Gtk::SpinButton spinMax, spinMin, spinStepsize, spinDec;
		YesNoToggleButtonGTKMM toggleAdhereStep, toggleAdhereDec;
*/	
		
	this->show_all();		
};

//-----------------------------------------------------------------------------

FieldSpinEditWindowGTKMM::~FieldSpinEditWindowGTKMM()
{

}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------




