
//
//	Author: A.L. Hertog
//	Date: 18 june 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

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
		
