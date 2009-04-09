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
		try
		{
			// Cast field to a SpinField object
			SpinField* spinField = NULL;
			spinField = dynamic_cast<SpinField*>(field);
	
			if( spinField != NULL )
			{	
				// Create a SpinButton, set its variables and set entryField equal to it.
				Gtk::SpinButton* spinEntryField = new Gtk::SpinButton( spinField->getStepsize(), spinField->getDecimals() );
				spinEntryField->set_range( *(spinField->getMinimum()), *(spinField->getMaximum()) );
				spinEntryField->set_snap_to_ticks( spinField->getAdhereStep() );
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
			comboField = dynamic_cast<ComboField*>(field);
	
			if( comboField != NULL )
			{	
				Gtk::ComboBox* comboEntryField = new Gtk::ComboBox();
				

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
	// TODO 
	#ifdef TODO_DEF
	#warning TODO in file __FILE__ at line __LINE__.
	#endif
	else if( fieldType.compare("ComboEntry") == 0 )	//---------------------------
	{
		entryField = new Gtk::Entry();
	}
	else if( fieldType.compare("ComboRadio") == 0 )	//---------------------------
	{
		entryField = new Gtk::Entry();
	}
	else
	{
		// TODO Send error because the field type is unknown.
	}
	
	
	// Add the widgets to the parrent HBox
	this->pack_end( *label, 			false, 	false, 	5 );
	this->pack_end( *entryField, 	true, 	true, 	5 );
	this->pack_end( *required, 		false,	false, 	5 );
	this->pack_end( *reset, 			false, 	false, 	5 );
	
};

//-----------------------------------------------------------------------------

FieldGTKMM::~FieldGTKMM()
{
	delete label;
	delete required;
	delete reset;
	delete entryField;
	cout << "Destroyed a FieldGTKMM object.\n";
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

