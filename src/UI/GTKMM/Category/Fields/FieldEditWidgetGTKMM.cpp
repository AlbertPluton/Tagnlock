//
//	Author: A.L. Hertog
//	Date: 13 May 2009
//	License: GPL
//
//


#include "FieldEditWidgetGTKMM.h"

#include "FieldSpinEditWidgetGTKMM.h"
#include "FieldComboEditWidgetGTKMM.h"

//-----------------------------------------------------------------------------

FieldEditWidgetGTKMM::FieldEditWidgetGTKMM( Field* pField, int i ) : 	typeLabel("Type: ", 0.98, 0.5), 
																																			labelLabel("Label: ", 0.98, 0.5), 
																																			requiredLabel("Required: ", 0.98, 0.5), 
																																			resetLabel("Reset: ", 0.98, 0.5)
{
#ifdef DEBUG_MESSAGES_DEF	
	cout << "Constructing a FieldEditWidgetGTKMM object.\n";
#endif	

	baseField = pField;
	index = i;

	attachX = Gtk::FILL|Gtk::EXPAND;
	attachY = Gtk::EXPAND;
	
	rows = 4;
	columns = 5;
	
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
	label.signal_changed().connect( sigc::mem_fun(this, &FieldEditWidgetGTKMM::changeLabel) );	
	required.signal_clicked().connect( sigc::mem_fun(this, &FieldEditWidgetGTKMM::changeRequired) );
	reset.signal_clicked().connect( sigc::mem_fun(this, &FieldEditWidgetGTKMM::changeReset) );

	
	
	this->show_all();
	
};

//-----------------------------------------------------------------------------

FieldEditWidgetGTKMM::~FieldEditWidgetGTKMM()
{
#ifdef DEBUG_MESSAGES_DEF	
	cout << "Destroyed a FieldEditWidgetGTKMM object.\n";
#endif
};

//-----------------------------------------------------------------------------

FieldEditWidgetGTKMM* FieldEditWidgetGTKMM::newEditWidget( Field* pField, int i )
{

	FieldEditWidgetGTKMM* editWindow = NULL;

	// Obtain the type from the original field.	
	string fieldType = pField->getType();


	if( fieldType.compare("SpinField") == 0 )	//-------------------------------
	{
		editWindow = new FieldSpinEditWidgetGTKMM( pField, i );
		return editWindow;
	}	
	else if( (fieldType.compare("Combo") == 0) || (fieldType.compare("ComboEntry") == 0) || (fieldType.compare("ComboRadio") == 0) )	//-------------------------------
	{
		editWindow = new FieldComboEditWidgetGTKMM( pField, i );
		return editWindow;
	}	
	else if( (fieldType.compare("CheckField") == 0) || (fieldType.compare("TextField") == 0) ) //--------------------------------
	{
		editWindow = new FieldEditWidgetGTKMM( pField, i );
		return editWindow;
	}
	else
	{
#ifdef TODO_DEF
#warning TODO throw error field type not correct
#endif		
		cout << "Error: Field type not correct. Occoured in: FieldEditWidgetGTKMM::generateTypeDependend()\n";
	}	
	
	return NULL;

};

//-----------------------------------------------------------------------------

void FieldEditWidgetGTKMM::changeLabel()
{
	baseField->setLabel( label.get_text() );
	m_signal_changed_property.emit( );
};		

//-----------------------------------------------------------------------------

void FieldEditWidgetGTKMM::changeRequired()
{
	baseField->setRequired( required.get_active() );
	m_signal_changed_property.emit( );	
};

//-----------------------------------------------------------------------------

void FieldEditWidgetGTKMM::changeReset()
{
	baseField->setReset( reset.get_active() );
	m_signal_changed_property.emit( );		
};

//-----------------------------------------------------------------------------

FieldEditWidgetGTKMM::type_signal_changed_property FieldEditWidgetGTKMM::signal_changed_property()
{
  return m_signal_changed_property;
}

//-----------------------------------------------------------------------------

