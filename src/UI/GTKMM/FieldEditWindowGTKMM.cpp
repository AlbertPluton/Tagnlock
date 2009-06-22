//
//	Author: A.L. Hertog
//	Date: 13 May 2009
//	License: GPL
//
//


#include "FieldEditWindowGTKMM.h"

#include "FieldSpinEditWindowGTKMM.h"
#include "FieldComboEditWindowGTKMM.h"

//-----------------------------------------------------------------------------

FieldEditWindowGTKMM::FieldEditWindowGTKMM( Field* pField, int i ) : typeLabel("Type: ", 0.98, 0.5), labelLabel("Label: ", 0.98, 0.5), requiredLabel("Required: ", 0.98, 0.5), resetLabel("Reset: ", 0.98, 0.5)
{
#ifdef DEBUG_MESSAGES_DEF	
	cout << "Constructing a FieldEditWindowGTKMM object.\n";
#endif	

	baseField = pField;
	index = i;

	attachX = Gtk::FILL|Gtk::EXPAND;
	attachY = Gtk::EXPAND;
	
	rows = 4;
	columns = 3;
	
	this->set_row_spacings(10);
	
		
	// Add some info on the type of field.
	type.set_label( baseField->getType() );	
	type.set_alignment(0, 0.5);
	this->attach( typeLabel, 0, 1, 0, 1, attachX, attachY);
	this->attach( type, 1, 3, 0, 1, attachX, attachY);

	// Display the label used.
	label.set_text( baseField->getLabel() );	
	this->attach( labelLabel, 0, 1, 1, 2, attachX, attachY );
	this->attach( label, 1, columns, 1, 2, attachX, attachY );

	// Display a button to edit the required property.
	required.set_active( baseField->getRequired() );	
	this->attach( requiredLabel, 0, 1, 2, 3, attachX, attachY );
	this->attach( required, 1, columns, 2, 3, attachX, attachY );

	// Add a button to edit the reset property.
	reset.set_active( baseField->getReset() );	
	this->attach( resetLabel, 0, 1, 3, 4, attachX, attachY );
	this->attach( reset, 1, columns, 3, 4, attachX, attachY );

	
	// Connect the signals
	label.signal_changed().connect( sigc::mem_fun(this, &FieldEditWindowGTKMM::changeLabel) );	
	required.signal_clicked().connect( sigc::mem_fun(this, &FieldEditWindowGTKMM::changeRequired) );
	reset.signal_clicked().connect( sigc::mem_fun(this, &FieldEditWindowGTKMM::changeReset) );

	
	
	this->show_all();
	
};

//-----------------------------------------------------------------------------

FieldEditWindowGTKMM::~FieldEditWindowGTKMM()
{
#ifdef DEBUG_MESSAGES_DEF	
	cout << "Destroyed a FieldEditWindowGTKMM object.\n";
#endif
};

//-----------------------------------------------------------------------------

FieldEditWindowGTKMM* FieldEditWindowGTKMM::newEditWindow( Field* pField, int i )
{

	FieldEditWindowGTKMM* editWindow = NULL;

	// Obtain the type from the original field.	
	string fieldType = pField->getType();


	if( fieldType.compare("SpinField") == 0 )	//-------------------------------
	{
		editWindow = new FieldSpinEditWindowGTKMM( pField, i );
		return editWindow;
	}	
	else if( (fieldType.compare("Combo") == 0) || (fieldType.compare("ComboEntry") == 0) || (fieldType.compare("ComboRadio") == 0) )	//-------------------------------
	{
		editWindow = new FieldComboEditWindowGTKMM( pField, i );
		return editWindow;
	}	
	else if( (fieldType.compare("CheckField") == 0) || (fieldType.compare("TextField") == 0) ) //--------------------------------
	{
		editWindow = new FieldEditWindowGTKMM( pField, i );
		return editWindow;
	}
	else
	{
#ifdef TODO_DEF
#warning TODO throw error field type not correct
#endif		
		cout << "Error: Field type not correct. Occoured in: FieldEditWindowGTKMM::generateTypeDependend()\n";
	}	
	
	return NULL;

};

//-----------------------------------------------------------------------------

void FieldEditWindowGTKMM::changeLabel()
{
	baseField->setLabel( label.get_text() );
	m_signal_changed_property.emit( 1 );
};		

//-----------------------------------------------------------------------------

void FieldEditWindowGTKMM::changeRequired()
{
	baseField->setRequired( required.get_active() );
	m_signal_changed_property.emit( 1 );	
};

//-----------------------------------------------------------------------------

void FieldEditWindowGTKMM::changeReset()
{
	baseField->setReset( reset.get_active() );
	m_signal_changed_property.emit( 1 );		
};

//-----------------------------------------------------------------------------

FieldEditWindowGTKMM::type_signal_changed_property FieldEditWindowGTKMM::signal_changed_property()
{
  return m_signal_changed_property;
}

//-----------------------------------------------------------------------------

