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




//-----------------------------------------------------------------------------

FieldGTKMM::FieldGTKMM( Field* field ) : 
				label( field->getLabel() ),
				required( "", field->getRequired() ),
				reset( "", field->getReset() )
{

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

};

//-----------------------------------------------------------------------------

FieldGTKMM::~FieldGTKMM()
{
	delete entryField;
};


//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

