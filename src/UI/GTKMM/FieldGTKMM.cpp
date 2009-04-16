//
//	Author: A.L. Hertog
//	Date: 30 January 2009
//	License: GPL
//
//

#include "FieldGTKMM.h"

#include "Field.h"
#include "TextField.h"
#include "CheckField.h"
#include "ComboField.h"
#include "SpinField.h"

#include <string>
using namespace std;

#include <iostream>


//-----------------------------------------------------------------------------

FieldGTKMM::FieldGTKMM( Field* field ) 
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing FieldGTKMM	object.\n";
#endif


	label = new Gtk::Label( field->getLabel() );
	required = new Gtk::CheckButton( "", field->getRequired() );
	reset = new Gtk::CheckButton( "", field->getReset() );

	string fieldType = field->getType();



	if( fieldType.compare("TextField") == 0 )	//-------------------------------
	{
		entryField = new Gtk::Entry();
	}
	
	
	
	else if( fieldType.compare("CheckField") == 0 )	//-------------------------------
	{
		entryField = new Gtk::CheckButton( "", false );
	}
	
	
	
	else if( fieldType.compare("SpinField") == 0 )	//---------------------------
	{
#ifdef TODO_DEF
#warning TODO in file __FILE__ at line __LINE__. Make the spin button work.
#endif		

		try
		{
			// Cast field to a SpinField object
			SpinField* spinField = NULL;
			spinField = static_cast<SpinField*>(field);
	
			if( spinField != NULL )
			{	
				// Create a SpinButton, set its variables and set entryField equal to it.
				Gtk::SpinButton* spinEntryField = new Gtk::SpinButton( spinField->getStepsize(), spinField->getDecimals() );
				
				Gtk::Adjustment* adjustment = spinEntryField->get_adjustment();
				
				if( spinField->getMinimum() != NULL )
				{
				 	adjustment->set_lower( *(spinField->getMinimum()) );
				}
				if( spinField->getMaximum() != NULL )
				{
				 	adjustment->set_upper( *(spinField->getMaximum()) );
				}
				
				spinEntryField->set_numeric();
				spinEntryField->set_snap_to_ticks( spinField->getAdhereStep() );
			
				spinEntryField->set_update_policy( Gtk::UPDATE_ALWAYS );
				
				entryField = spinEntryField;
			}
			else
			{
				// TODO throw exception
			}
		}
		catch (exception& e)
		{
			throw e;
		}
	}



	else if( fieldType.compare("Combo") == 0 )	//-------------------------------
	{
		try
		{
			// Cast field to a ComboField
			ComboField* comboField = NULL;
			comboField = static_cast<ComboField*>(field);
	
			if( comboField != NULL )
			{	
				// Make a new ComboBox object named comboEntryField, this does not refer to comboEntry-Field but to a combo-EntryField.
				Gtk::ComboBoxText* comboEntryField = new Gtk::ComboBoxText();
				
				for( int i = 0; i < comboField->getComboSize(); i++ )
				{
					comboEntryField->append_text( comboField->getComboElement( i ) );
				}		

				entryField = comboEntryField;
			}
			else
			{
				// TODO throw exception
			}
		}
		catch (exception& e)
		{
			throw e;
		}	
	}



	else if( fieldType.compare("ComboEntry") == 0 )	//---------------------------
	{
		try
		{
			// Cast field to a ComboField
			ComboField* comboField = NULL;
			comboField = static_cast<ComboField*>(field);
	
			if( comboField != NULL )
			{	
				Gtk::ComboBoxEntryText* comboEntryEntryField = new Gtk::ComboBoxEntryText();
				
				for( int i = 0; i < comboField->getComboSize(); i++ )
				{
					comboEntryEntryField->append_text( comboField->getComboElement( i ) );
				}		

				entryField = comboEntryEntryField;
			}
			else
			{
				// TODO throw exception
			}
		}
		catch (exception& e)
		{
			throw e;
		}	
	}



	else if( fieldType.compare("ComboRadio") == 0 )	//---------------------------
	{
		try
		{
		
			// Create a widget ot hold the radiobuttons
			entryField = new Gtk::VBox();
			
			// Cast field to a ComboField
			ComboField* comboField = NULL;
			comboField = static_cast<ComboField*>(field);

			// Create a number of new radiobuttons in an array.
			radioButtons = new Gtk::RadioButton[ comboField->getComboSize() ]; 

			// Get the group from the first radiobutton.
			Gtk::RadioButton::Group group = (radioButtons[0]).get_group();
			
			// Add the first radio button to the VBox.
			((Gtk::VBox*)entryField)->pack_start( *radioButtons );
			
			// Set the text form getComboElement for the first radiobutton.
			(radioButtons[0]).set_label( comboField->getComboElement( 0 ) );
		
			// Add the rest of the radiobuttons to the same group, give them the text from getComboElement() and add them to the entryField widget.
			for( int i = 1; i < comboField->getComboSize(); i++ )
			{
				(radioButtons[i]).set_group( group );
				(radioButtons[i]).set_label( comboField->getComboElement( i ) );
				((Gtk::VBox*)entryField)->pack_start( *(radioButtons + i) );
			}
			
		}
		catch (exception& e)
		{
			throw e;
		}	

	}



	else
	{
		// TODO Send error because the field type is unknown.
	}

	
	
	// Add the widgets to the parrent HBox
	this->pack_start( *label, 			false, 	false, 	5 );
	this->pack_start( *entryField, 	true, 	true, 	5 );
	this->pack_start( *required, 		false,	false, 	5 );
	this->pack_start( *reset, 			false, 	false, 	5 );
	
	label->show();
	entryField->show();
	required->show();
	reset->show();
	entryField->show();

 	this->show_all();

};

//-----------------------------------------------------------------------------

FieldGTKMM::~FieldGTKMM()
{

#ifdef DEBUG_MESSAGES_DEF	
	cout << "Destroyed a FieldGTKMM object.\n";
#endif


	delete label;
	delete required;
	delete reset;
	delete entryField;

	delete [] radioButtons;
 

};


//-----------------------------------------------------------------------------

Gtk::Widget* FieldGTKMM::getLabel()
{
	return label;
};


//-----------------------------------------------------------------------------

Gtk::Widget* FieldGTKMM::getRequired()
{
	return required;
};


//-----------------------------------------------------------------------------

Gtk::Widget* FieldGTKMM::getReset()
{
	return reset;
};

//-----------------------------------------------------------------------------

Gtk::Widget* FieldGTKMM::getEntryField()
{
	return entryField;
};

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

