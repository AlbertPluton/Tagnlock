//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
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

		
Gtk::Widget* ComboFieldGTKMM::getEditWidget()
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
	
};


//-----------------------------------------------------------------------------

		
void ComboFieldGTKMM::getData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getData
#endif	
};


//-----------------------------------------------------------------------------

				
void ComboFieldGTKMM::setData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::setData
#endif	
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



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


