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

};

//-----------------------------------------------------------------------------

string FileLocation::getFileLocationUri()
{

};

//-----------------------------------------------------------------------------

string FileLocation::getFileLocation()
{

};

//-----------------------------------------------------------------------------



