//
//	Author: A.L. Hertog
//	Date: 28 October 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#include "DialogFieldChooserGTKMM.h"


//-----------------------------------------------------------------------------


DialogFieldChooserGTKMM::DialogFieldChooserGTKMM( Gtk::Window* parent )	:	
																																					Dialog( "Select a field type", parent ),
																																					radioTextField("Text entry"),
																																					radioSpinField("Spin button"),
																																					radioCheckField("Check button"),
																																					radioComboField("Combo field"),
																																					radioComboEntryField("Combo entry field"),
																																					radioComboRadioField("Radio buttons")
{

	// Request a minimum with
	this->set_size_request( 250 ); 
	
	// Put the radio buttons in the same group.
	Gtk::RadioButtonGroup group = radioTextField.get_group();
	radioSpinField.set_group( group );
	radioCheckField.set_group( group );
	radioComboField.set_group( group );
	radioComboEntryField.set_group( group );
	radioComboRadioField.set_group( group );				
	
	// Place the radio buttons in the dialog.
	Gtk::VBox* vBox = this->get_vbox();
	vBox->pack_start( radioTextField );
	vBox->pack_start( radioSpinField );
	vBox->pack_start( radioCheckField );
	vBox->pack_start( radioComboField );
	vBox->pack_start( radioComboEntryField );
	vBox->pack_start( radioComboRadioField );
			
		
	// Add buttons
	this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
 	this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	
	show_all();


};


//-----------------------------------------------------------------------------

DialogFieldChooserGTKMM::~DialogFieldChooserGTKMM()
{



};


//-----------------------------------------------------------------------------

bool DialogFieldChooserGTKMM::chooseField( Category* cat )
{

	bool succes = false;

	// Display the dialog and obtain the result. 
	int result = this->run();
	
  //Handle the response
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {		     
    	// Make a field specified by the selected radio button
    	if( radioTextField.get_active() )
    	{
				TextField* field = new TextField( "Label me", false, false );
				cat->addField( field );    		
				succes = true;
    	}
    	else if( radioSpinField.get_active() )
    	{
				SpinField* field = new SpinField( "Label me", false, false );
				cat->addField( field );    		    		
				succes = true;
    	}
    	else if( radioCheckField.get_active() )
    	{
				CheckField* field = new CheckField( "Label me", false, false );
				cat->addField( field );    		    		    		
				succes = true;				
    	}
    	else if( radioComboField.get_active() )
    	{
    		vector<string>* combo = new vector<string>;
    		combo->push_back( "Option 1" );
				ComboField* field = new ComboField( "Label me", false, false, combo, Combo );
				cat->addField( field );    		  		    		
				succes = true;				
    	}
    	else if( radioComboEntryField.get_active() )
    	{
    		vector<string>* combo = new vector<string>;
    		combo->push_back( "Option 1" );
				ComboField* field = new ComboField( "Label me", false, false, combo, ComboEntry );
				cat->addField( field );     		 		    		
				succes = true;				
    	}
    	else if( radioComboRadioField.get_active() )
    	{
    		vector<string>* combo = new vector<string>;
    		combo->push_back( "Option 1" );
				ComboField* field = new ComboField( "Label me", false, false, combo, ComboRadio );
				cat->addField( field );     		 		    		
				succes = true;				
    	}    	    	    	    	
    	else
    	{
    		// TODO throw
    		cout << "ERROR in DialogFieldCHooserGTKMM::chooseField: unknown radio button selection.\n";
    	}
    	
      break;
    }
     default:
    {
      break;
    }	
	};	
	
	return succes;
	
};



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

