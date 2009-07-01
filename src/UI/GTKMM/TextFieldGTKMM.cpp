//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
//
//
#include "TextFieldGTKMM.h"

//-----------------------------------------------------------------------------

	
TextFieldGTKMM::TextFieldGTKMM( Field* pField, FieldData* dat, int i ) : FieldGTKMM( pField, dat, i )
{
	// Attach the entry to the table
	table.attach( textEntry, 2, columns-2, 0, 1, tableAttachX, tableAttachY, tablePaddingX, tablePaddinY	);

	// Fill the field with data.
 	if( data != NULL ) this->getData();

	// Connect signals to indicate a change in data.
	textEntry.signal_changed().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );

};


//-----------------------------------------------------------------------------

	
TextFieldGTKMM::~TextFieldGTKMM()
{

};


//-----------------------------------------------------------------------------

		
Gtk::Widget* TextFieldGTKMM::getEditWidget()
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

		
void TextFieldGTKMM::updateProperties()
{
	this->updatePropertiesParentClass();
	// No properties for this field.
};


//-----------------------------------------------------------------------------

		
void TextFieldGTKMM::getData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getData
#endif	
};


//-----------------------------------------------------------------------------

				
void TextFieldGTKMM::setData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::setData
#endif	
};



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


