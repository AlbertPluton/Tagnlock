//
//	Author: A.L. Hertog
//	Date: 25 September 2009
//	License: GPL
//
//


#include "FileLocation.h"


FileLocation::FileLocation( string uriString )
{
	uri = uriString;
};

//-----------------------------------------------------------------------------


FileLocation::~FileLocation()
{

};

//-----------------------------------------------------------------------------

		
string FileLocation::getUri()
{
	return uri;
};

//-----------------------------------------------------------------------------

string FileLocation::getFileName()
{
	// Find the last slash in the uri 
	size_t found;
  found = uri.find_last_of("/\\");
  return uri.substr(found+1);
};

//-----------------------------------------------------------------------------

string FileLocation::getFileLocationUri()
{
	// Find the last slash in the uri 
	size_t found;
  found = uri.find_last_of("/\\");
  return uri.substr(0,found);
};

//-----------------------------------------------------------------------------

string FileLocation::getFileLocation()
{
	#warning "Using not so smart way to convert uri to normal location"
	// Remove "file://"
	return uri.substr( 6 );	
};

//-----------------------------------------------------------------------------



