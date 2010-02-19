//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//
#include "ComboFieldGTKMM.h"

//-----------------------------------------------------------------------------

	
ComboFieldGTKMM::ComboFieldGTKMM( Field* pField, FieldData* dat, int i ) : FieldGTKMM(  pField, dat, i )
{

	comboField = NULL;
	try
	{
		// Cast field to a ComboField
		comboField = static_cast<ComboField*>(baseField);
	}
	catch (exception& e)
	{
		throw e;
	}			
		

	string fieldType = baseField->getType();
	
		
	if( fieldType.compare("Combo") == 0 )	//-------------------------------
	{
		try
		{

			// Make a new ComboBox object named comboEntryField, this does not refer to comboEntry-Field but to a combo-EntryField.
			comboBoxText = new Gtk::ComboBoxText();
			
			for( int i = 0; i < comboField->getComboSize(); i++ )
			{
				comboBoxText->append_text( comboField->getComboElement( i ) );
			}		
	
			// Connect the changed signal to the changed signal of this class.
			comboBoxText->signal_changed().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );	
			
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
			comboBoxEntry = new Gtk::ComboBoxEntryText();
			
			for( int i = 0; i < comboField->getComboSize(); i++ )
			{
				comboBoxEntry->append_text( comboField->getComboElement( i ) );
			}		

			// Connect the changed signal to the changed signal of this class.
			comboBoxEntry->signal_changed().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );	
			

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
			radioBox = new Gtk::VBox();

			// Create a number of new radiobuttons in an array.
			radioButtons = new Gtk::RadioButton[ comboField->getComboSize() ]; 

			// Get the group from the first radiobutton.
			Gtk::RadioButton::Group group = (radioButtons[0]).get_group();
			
			// Add the first radio button to the VBox.
			radioBox->pack_start( *radioButtons );
			
			// Set the text from getComboElement for the first radiobutton.
			(radioButtons[0]).set_label( comboField->getComboElement( 0 ) );
		
			// Add the rest of the radiobuttons to the same group, give them the text from getComboElement() and add them to the table.
			for( int i = 1; i < comboField->getComboSize(); i++ )
			{
				(radioButtons[i]).set_group( group );
				(radioButtons[i]).set_label( comboField->getComboElement( i ) );
				radioBox->pack_start( *(radioButtons + i) );
			}

			radioBox->show_all();
	
#ifdef TODO_DEF
#warning TODO in ComboFieldGTKMM::ComboFieldGTKMM: Connect the signal of the radio buttons 
#endif	
			// Connect the toggled signal to the changed signal of this class.
//			radioButtons.signal_clicked().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );	

			
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
	
	
	// Fill the field with some data.
	if( data != NULL ) this->getData();

	this->show_all();

};


//-----------------------------------------------------------------------------

	
ComboFieldGTKMM::~ComboFieldGTKMM()
{

};


//-----------------------------------------------------------------------------

		
void ComboFieldGTKMM::updateProperties()
{
	string fieldType = baseField->getType();

	if( fieldType.compare("Combo") == 0 )	//-------------------------------
	{
		try
		{
			// Clear the old items from the box.
			comboBoxText->clear_items();
			
			// Load the new items.
			for( int i = 0; i < comboField->getComboSize(); i++ )
			{
				comboBoxText->append_text( comboField->getComboElement( i ) );
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
			// Clear the old items from the box.
			comboBoxEntry->clear_items();
			
			// Load the new items.
			for( int i = 0; i < comboField->getComboSize(); i++ )
			{
				comboBoxEntry->append_text( comboField->getComboElement( i ) );
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
			// Delete any old stuff;
			delete radioButtons;
			delete radioBox;
		
			// Create a widget ot hold the radiobuttons
			radioBox = new Gtk::VBox();

			if( comboField != NULL )
			{
				// Create a number of new radiobuttons in an array.
				radioButtons = new Gtk::RadioButton[ comboField->getComboSize() ]; 

				// Get the group from the first radiobutton.
				Gtk::RadioButton::Group group = (radioButtons[0]).get_group();
			
				// Add the first radio button to the VBox.
				radioBox->pack_start( *radioButtons );
			
				// Set the text from getComboElement for the first radiobutton.
				(radioButtons[0]).set_label( comboField->getComboElement( 0 ) );
		
				// Add the rest of the radiobuttons to the same group, give them the text from getComboElement() and add them to the table.
				for( int i = 1; i < comboField->getComboSize(); i++ )
				{
					(radioButtons[i]).set_group( group );
					(radioButtons[i]).set_label( comboField->getComboElement( i ) );
					radioBox->pack_start( *(radioButtons + i) );
				}
	
				radioBox->show_all();
				
				
#ifdef TODO_DEF
#warning TODO in ComboFieldGTKMM::ComboFieldGTKMM: Connect the signal of the radio buttons 
#endif	
				// Connect the toggled signal to the changed signal of this class.
//				radioButtons.signal_clicked().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );	
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



	else
	{
		// TODO Send error because the field type is unknown.
	}
	
	this->updatePropertiesParentClass();
	
};


//-----------------------------------------------------------------------------

		
void ComboFieldGTKMM::getData()
{

	string fieldType = baseField->getType();

	if( fieldType.compare("Combo") == 0 )	//-------------------------------
	{
		data->set( comboBoxText->get_active_text() );
	}
	else if( fieldType.compare("ComboEntry") == 0 )	//---------------------------
	{
		Gtk::Entry* entry = comboBoxEntry->get_entry();
		string active = entry->get_text();
		data->set( active );
		entry->set_text( "" ); // To clear the field
	}
	else if( fieldType.compare("ComboRadio") == 0 )	//---------------------------
	{
		// Loop over all radio buttons
		for( int i = 1; i < comboField->getComboSize(); i++ )
		{
			// If the button is active store the label.
			if( (radioButtons[i]).get_active() )
			{
				string label = (radioButtons[i]).get_label();
				data->set( label );
				break;
			}	
			
		}
	}
	else
	{
		// TODO Send error because the field type is unknown.
	}
	

};


//-----------------------------------------------------------------------------

				
void ComboFieldGTKMM::setData()
{

	string fieldType = baseField->getType();

	if( fieldType.compare("Combo") == 0 )	//-------------------------------
	{
		string dataString = data->getString();
		if( dataString.compare( "" ) != 0 )
		{		
			comboBoxText->set_active_text( data->getString() );
		}
		else
		{
			comboBoxText->set_active(-1);
		}
	}
	else if( fieldType.compare("ComboEntry") == 0 )	//---------------------------
	{
		
		string dataString = data->getString();
		
		// If the data is not empty
		if( dataString.compare( "" ) != 0 )
		{
			// Loop over all elements
			for( int i = 0; i < comboField->getComboSize(); i++ )
			{
				// If the data matches the element.
				if( dataString.compare( comboField->getComboElement(i) ) == 0 )
				{
					// Set it active
					comboBoxEntry->set_active_text( dataString );
					break;
				}				
			};
			
			// If this point is reached it means that the data is not empty but it was not found among the standard elements.
			// Therefor the user must have entered something him self. Lets add it to the combo and set it active.
			comboBoxEntry->append_text( dataString );
			comboBoxEntry->set_active_text( dataString );
			
		};
		
	}
	else if( fieldType.compare("ComboRadio") == 0 )	//---------------------------
	{
		string label = "";
		// Set by default the first one active.
		radioButtons[0].set_active();
		// Loop over all radio buttons
		for( int i = 0; i < comboField->getComboSize(); i++ )
		{	
			// See if the labels match
			label = (radioButtons[i]).get_label();
			if( label.compare( data->getString() ) == 0 )
			{
				(radioButtons[i]).set_active( );		
			}
		}
	}



	else
	{
		// TODO Send error because the field type is unknown.
	}
};



//-----------------------------------------------------------------------------

Gtk::Widget* ComboFieldGTKMM::getEntry()
{
	string fieldType = baseField->getType();

	if( fieldType.compare("Combo") == 0 )	//-------------------------------
	{
		return (Gtk::Widget*)comboBoxText;
	}
	
	else if( fieldType.compare("ComboEntry") == 0 )	//---------------------------
	{
		return (Gtk::Widget*)comboBoxEntry;
	}

	else if( fieldType.compare("ComboRadio") == 0 )	//---------------------------
	{
		return (Gtk::Widget*)radioBox;
	}
	else
	{
		// TODO Send error because the field type is unknown.
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getEntry
#endif
	}
	
	return NULL;
};

//-----------------------------------------------------------------------------

Gtk::Widget* ComboFieldGTKMM::getEditWidget()
{

	// Get the editWidget.
	FieldEditWidgetGTKMM* fieldEditWidgetGTKMM = FieldEditWidgetGTKMM::newEditWidget( this->getBaseField(), this->getIndex() );
		
	// Cast it to a Gtk::Widget.
	editWidget = (Gtk::Widget*)fieldEditWidgetGTKMM;
		
	// Connect the properties updated signal.
	fieldEditWidgetGTKMM->signal_changed_property().connect( sigc::mem_fun( *this, &ComboFieldGTKMM::updateProperties) );	
		
	return editWidget;
};


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


