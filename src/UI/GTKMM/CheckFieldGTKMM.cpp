//
//	Author: A.L. Hertog
//	Date: 22 June 2009
//	License: GPL
//
//

	
#include "CheckFieldGTKMM.h"

//-----------------------------------------------------------------------------

	
CheckFieldGTKMM::CheckFieldGTKMM( Field* pField, FieldData* dat, int i ) : FieldGTKMM( pField, dat, i )
{

	// Attach the checkButton to the table.
	table.attach( checkButton, 2, columns-2, 0, 1, tableAttachX, tableAttachY, tablePaddingX, tablePaddinY	);
	
	// Fill the field with some data.
	if( data != NULL ) this->getData();
	
	// Connect the clicked signal to the changed signal of this class.
	checkButton.signal_clicked().connect( sigc::mem_fun( *this, &FieldGTKMM::changed) );

};


//-----------------------------------------------------------------------------

	
CheckFieldGTKMM::~CheckFieldGTKMM()
{

};


//-----------------------------------------------------------------------------

		
Gtk::Widget* CheckFieldGTKMM::getEditWidget()
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

		
void CheckFieldGTKMM::updateProperties()
{
	this->updatePropertiesParentClass();
	// No properties for this field.
};


//-----------------------------------------------------------------------------

		
void CheckFieldGTKMM::getData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::getData
#endif	
};


//-----------------------------------------------------------------------------

				
void CheckFieldGTKMM::setData()
{
#ifdef TODO_DEF
#warning TODO in ...FieldGTKMM::setData
#endif	
};



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


