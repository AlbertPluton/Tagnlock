//
//	Author: A.L. Hertog
//	Date: 13 May 2009
//	License: GPL
//
//


#include "FieldEditWindowGTKMM.h"



//-----------------------------------------------------------------------------

FieldEditWindowGTKMM::FieldEditWindowGTKMM( Field* pField ) : typeLabel("Type: ", 0.98, 0.5), labelLabel("Label: ", 0.98, 0.5), requiredLabel("Required: ", 0.98, 0.5), resetLabel("Reset: ", 0.98, 0.5)
{
	field = pField;
	
	rows = 4;
	columns = 2;
	
	this->resize(	3, 2 );
	this->set_row_spacings(10);
		
	// Add some info on the type of field.
	type.set_label( field->getType() );	
	type.set_alignment(0.1, 0.5);
	this->attach( typeLabel, 0, 1, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::SHRINK );
	this->attach( type, 1, 2, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::SHRINK);

	// Display the label used.
	label.set_text( field->getLabel() );	
	this->attach( labelLabel, 0, 1, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::EXPAND );
	this->attach( label, 1, 2, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::EXPAND );

	// Display a button to edit the required property.
	required.set_active( field->getRequired() );	
	this->attach( requiredLabel, 0, 1, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::EXPAND );
	this->attach( required, 1, 2, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::EXPAND );

	// Add a button to edit the reset property.
	reset.set_active( field->getReset() );	
	this->attach( resetLabel, 0, 1, 3, 4, Gtk::FILL|Gtk::EXPAND, Gtk::EXPAND );
	this->attach( reset, 1, 2, 3, 4, Gtk::FILL|Gtk::EXPAND, Gtk::EXPAND );

	
	
	
	
	this->show_all();
	
};

//-----------------------------------------------------------------------------

FieldEditWindowGTKMM::~FieldEditWindowGTKMM()
{

};

//-----------------------------------------------------------------------------

void FieldEditWindowGTKMM::change( Field* pField )
{
	field = pField;
	
	type.set_label( field->getType() );	
	label.set_text( field->getLabel() );
	required.set_active( field->getRequired() );
	reset.set_active( field->getReset() );	
	
	
	this->show_all();
}


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------


