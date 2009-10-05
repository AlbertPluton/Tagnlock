//
//	Author: A.L. Hertog
//	Date: 17 July 2009
//	License: GPL
//
//


#include "DisplayFile.h"
#include "DisplayFilePDF.h"


//-----------------------------------------------------------------------------

DisplayFile::DisplayFile( URIobject nameURI )
{
	fileNameURI = nameURI;
	this->widget = NULL;
	cout << "Creating an DisplayFile object.\n";
};


//-----------------------------------------------------------------------------

DisplayFile::~DisplayFile()
{

};


//-----------------------------------------------------------------------------

DisplayFile* DisplayFile::getDisplay( URIobject fileNameURI )
{
	string::size_type idx;
	string extension = "";
	string fileName = fileNameURI.getUriString();

	// Find the file type
	idx = fileName.rfind('.');
	if(idx != string::npos)
	{
		  extension = fileName.substr(idx+1);
	}


	// return the correct display object.
	if( extension.compare("") == 0 )
	{
		return NULL;
	}
	else if( (extension.compare("pdf") == 0) || (extension.compare("PDF") == 0) )
	{
//		#ifdef WITH_POPPLER
			return new DisplayFilePDF( fileName );
//		#endif
	}
	else
	{
		// TODO Throw error, File type unknown
		return NULL;
	}


};


//-----------------------------------------------------------------------------

Gtk::Widget* DisplayFile::getDisplayWidget()
{
	return (this->widget);
};


//-----------------------------------------------------------------------------

URIobject DisplayFile::getFileName()
{
	return fileNameURI;
};

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

