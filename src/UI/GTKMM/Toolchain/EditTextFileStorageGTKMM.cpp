
//
//	Author: A.L. Hertog
//	Date: 22 October 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#include "EditTextFileStorageGTKMM.h"



//-----------------------------------------------------------------------------


EditTextFileStorageGTKMM::EditTextFileStorageGTKMM( ToolchainNode* pNode ) : 	EditToolchainNodeGTKMM( pNode ),
																																								labelLocation( "Location: ", 0.98, 0.5),
																																								labelFileName( "File name: ", 0.98, 0.5),
																																								labelIndividual( "Individual files: ", 0.98, 0.5)
{
	// Cast the base node pointer to a TextFileStorage object for easy acces.
	try
	{
		node = static_cast<TextFileStorage*>(pNode);
	}
	catch( exception& e )
	{
		throw e;
	}
	
	// Add the Location to the table
	this->attach( labelLocation, 0, 1, rows, rows+1, attachX, attachY );
	this->attach( entryLocation, 1, columns, rows, rows+1, attachX, attachY );
	entryLocation.set_text( node->getLocation() );
  entryLocation.set_tooltip_text("Enter the file name.");
	
	// Add the FileName to the table
	this->attach( labelFileName, 0, 1, rows+1, rows+2, attachX, attachY );
	this->attach( entryFileName, 1, columns, rows+1, rows+2, attachX, attachY );
	entryFileName.set_text( node->getFileName() );
  entryFileName.set_tooltip_text("Enter the location to store the file(s).");
	
	// Add the individual to the table
	this->attach( labelIndividual, 0, 1, rows+2, rows+3, attachX, attachY );
	this->attach( buttonIndividual, 1, columns, rows+2, rows+3, attachX, attachY );
	buttonIndividual.set_active( node->getIndividualFiles() );
  buttonIndividual.set_tooltip_text("Determines whether or not to store all data object in individual or in a single file.");
	
	// Connect signals
	entryLocation.signal_changed().connect( sigc::mem_fun( *this, &EditTextFileStorageGTKMM::changedLocation ) );
	entryFileName.signal_changed().connect( sigc::mem_fun( *this, &EditTextFileStorageGTKMM::changedFileName ) );
	buttonIndividual.signal_toggled().connect( sigc::mem_fun( *this, &EditTextFileStorageGTKMM::changedIndividual ) );
	
	this->show_all();
	
};

//-----------------------------------------------------------------------------

EditTextFileStorageGTKMM::~EditTextFileStorageGTKMM()
{


};

//-----------------------------------------------------------------------------

void EditTextFileStorageGTKMM::changedLocation()
{
	node->setLocation( entryLocation.get_text() );
	m_signal_changed.emit( );
};

//-----------------------------------------------------------------------------

void EditTextFileStorageGTKMM::changedFileName()
{
	node->setFileName( entryFileName.get_text() );
	m_signal_changed.emit( );
};

//-----------------------------------------------------------------------------

void EditTextFileStorageGTKMM::changedIndividual()
{
	node->setIndividualFiles( buttonIndividual.get_active() );
	m_signal_changed.emit( );
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


