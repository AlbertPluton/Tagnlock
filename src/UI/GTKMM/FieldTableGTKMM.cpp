//
//	Author: A.L. Hertog
//	Date: 9 April 2009
//	License: GPL
//
//

#include "FieldTableGTKMM.h"

#include <iostream>

//-----------------------------------------------------------------------------

FieldTableGTKMM::FieldTableGTKMM()
{

#ifdef DEBUG_MESSAGES_DEF
	cout << "Constructing FieldTableGTKMM	object.\n";
#endif

	this->show();
	this->set_child_visible();	

};

//-----------------------------------------------------------------------------

FieldTableGTKMM::~FieldTableGTKMM()
{
#ifdef DEBUG_MESSAGES_DEF
	cout << "Destroyed a FieldTableGTKMM object.\n";
#endif
};

//-----------------------------------------------------------------------------

void FieldTableGTKMM::addField( Gtk::Widget* field )
{
	this->pack_start( *field,	true, true, 2 );
};

//-----------------------------------------------------------------------------

void FieldTableGTKMM::deleteField( int index )
{

#ifdef TODO_DEF
#warning TODO in file __FILE__ at line __LINE__.
#endif

};

//-----------------------------------------------------------------------------

void FieldTableGTKMM::makeNewTable( Category* category )
{

	FieldGTKMM* fieldGTKMM = NULL;
	int size = category->getFieldsSize();
	Field* field = NULL;
	
	for( int i = 0; i < size; i++ )
	{
		field = category->getFieldAt( i );
		fieldGTKMM = new FieldGTKMM( field );
		this->addField( (Gtk::Widget*)fieldGTKMM );
	}
	
	this->show_all();
	
};

//-----------------------------------------------------------------------------

void FieldTableGTKMM::makeNewTable( ObjectData* object )
{
#ifdef TODO_DEF
#warning TODO in file __FILE__ at line __LINE__.
#endif
};

//-----------------------------------------------------------------------------

void fillTable( ObjectData* object )
{
#ifdef TODO_DEF
#warning TODO in file __FILE__ at line __LINE__.
#endif
};



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------





