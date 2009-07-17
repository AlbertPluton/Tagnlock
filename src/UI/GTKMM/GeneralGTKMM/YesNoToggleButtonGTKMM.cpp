
#include "YesNoToggleButtonGTKMM.h"




//-----------------------------------------------------------------------------


YesNoToggleButtonGTKMM::YesNoToggleButtonGTKMM()
{
	// Connect the signal to the switch label function
	this->signal_clicked().connect( sigc::mem_fun( *this, &YesNoToggleButtonGTKMM::switchLabel ) );
	
	switchLabel();
	
};


//-----------------------------------------------------------------------------

YesNoToggleButtonGTKMM::~YesNoToggleButtonGTKMM()
{

};		
		
//-----------------------------------------------------------------------------

		
void YesNoToggleButtonGTKMM::switchLabel()
{
	if( this->get_active() )
	{
		this->set_label("Yes");	
	}
	else
	{
		this->set_label("No");
	}
};
		
