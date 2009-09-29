//
//	Author: A.L. Hertog
//	Date: 29 September 2009
//	License: GPL
//
//


#include "URIobject.h"


//-----------------------------------------------------------------------------

URIobject::URIobject( string fileName )
{ 
	UriobjectStateA state;
  state.uri = &uri;
  if (uriParseUriA(&state, fileName.c_str()) != URI_SUCCESS) 
  {
  				// TODO throw
          /* Failure */
          uriFreeUriMembersA(&uri);
  }
  uriFreeUriMembersA(&uri);
};

//-----------------------------------------------------------------------------

URIobject::URIobject( UriUriA uriCstyle )
{
	uri = uriCstyle;
};

//-----------------------------------------------------------------------------

URIobject::~URIobject()
{

};

//-----------------------------------------------------------------------------

UriUriA URIobject::getUri()
{
	return uri;
};

//-----------------------------------------------------------------------------

string URIobject::getUriString()
{

  char * uriCString;
  int charsRequired;

  if( uriToStringCharsRequiredA(&uri, &charsRequired) != URI_SUCCESS )
  {
		/* Failure */
  }
  charsRequired++; // Incrementing charsRequired by 1 is required since uriToStringCharsRequiredA() returns the length of the string as strlen() does, but uriToStringA() works with the number of maximum characters to be written including the zero-terminator.

  uriCString = malloc(charsRequired * sizeof(char));

  if( uriString == NULL )
  {
	  /* Failure */
  }

  if( uriToStringA(uriCString, &uri, charsRequired, NULL) != URI_SUCCESS )
  {
		/* Failure */
  }

	string uriString = uriCString;
	free( uriCString );
	return uriString;

};

//-----------------------------------------------------------------------------

string URIobject::getFileName()
{
  const char * const uriCString = getUriCString().c_str();
  const int bytesNeeded = strlen(uriCString) + 1 - 7;
  char * CFileName = malloc(bytesNeeded * sizeof(char));

  if( uriUriStringToUnixFilenameA(uriCString, CFIleName) != URI_SUCCESS )
  {
		/* Failure */
		free( CFileName );
  }

	string fileName = CFileName;
  free( CFileName );
  return fileName;
  
};

//-----------------------------------------------------------------------------

string URIobject::getFolder()
{
		// TODO
};


//-----------------------------------------------------------------------------

void URIobject::normalizeURI()
{
	const unsigned int dirtyParts = uriNormalizeSyntaxMaskRequiredA(&uri);
	if (uriNormalizeSyntaxExA(&uri, dirtyParts) != URI_SUCCESS) 
	{
		      /* Failure */
	}
};

//-----------------------------------------------------------------------------

URIobject URIobject::operator+ (URIobject param)
{
	string left = this->getUriString();
	string right = param->getUriString();
	return URIobject( left + right );
	
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------




