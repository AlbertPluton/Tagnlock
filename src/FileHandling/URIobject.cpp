//
//	Author: A.L. Hertog
//	Date: 29 September 2009
//	License: GPL
//
//


#include "URIobject.h"


//-----------------------------------------------------------------------------

URIobject::URIobject(  )
{ 
	setUri( "" );
};


//-----------------------------------------------------------------------------

URIobject::URIobject( string stringUri )
{ 
#ifdef TODO_DEF
#warning TODO in URIobject::URIobject: Make the Uri work with white spaces some how, and than uncomment setUri.
#endif	
	//setUri( stringUri );
	uriString = stringUri;
};

//-----------------------------------------------------------------------------
/*
URIobject::URIobject( UriUriA uriCstyle )
{
	uri = uriCstyle;
};
*/
//-----------------------------------------------------------------------------
/*
URIobject::URIobject( const URIobject& uriObject )
{
	uri = uriObject.uri;
	uriString = uriObject.uriString;
};
*/
//-----------------------------------------------------------------------------



URIobject::~URIobject()
{

};


//-----------------------------------------------------------------------------

void URIobject::setUri( string stringUri )
{
	UriParserStateA state;
  state.uri = &(this->uri);
  const char * const uriCString = stringUri.c_str();
  if (uriParseUriA(&state, uriCString) != URI_SUCCESS) 
  {
  				// TODO throw
          /* Failure */
          cout << "ERROR: URIobject::setUri, line " << __LINE__ << "\n";
          uriFreeUriMembersA(&uri);
  }
  uriFreeUriMembersA(&uri);
};

//-----------------------------------------------------------------------------

UriUriA URIobject::getUri()
{
	return uri;
};

//-----------------------------------------------------------------------------


string URIobject::getUriString()
{

	return uriString;

/*
  char * uriCString;
  int charsRequired;

  if( uriToStringCharsRequiredA(&uri, &charsRequired) != URI_SUCCESS )
  {
		// Failure 
		cout << "ERROR: URIobject::getUriString, line " << __LINE__ << "\n";
  }
  charsRequired++; // Incrementing charsRequired by 1 is required since uriToStringCharsRequiredA() returns the length of the string as strlen() does, but uriToStringA() works with the number of maximum characters to be written including the zero-terminator.

  uriCString = new char[charsRequired]; //malloc(charsRequired * sizeof(char));

  if( uriCString == NULL )
  {
	  // Failure 
	  cout << "ERROR: URIobject::getUriString, line " << __LINE__ << "\n";
  }

  if( uriToStringA(uriCString, &uri, charsRequired, NULL) != URI_SUCCESS )
  {
		// Failure 
		cout << "ERROR: URIobject::getUriString, line " << __LINE__ << "\n";
  }

	string uriString = uriCString;
	free( uriCString );
	return uriString;
*/

};


//-----------------------------------------------------------------------------

string URIobject::getFileName()
{
	return getFileName( uriString );  
};


//-----------------------------------------------------------------------------


string URIobject::getFileName( string stringUri )
{
  const char * const uriCString =  stringUri.c_str();
  const int bytesNeeded = strlen(uriCString) + 1 - 7;
  char * CFileName = new char[bytesNeeded]; //malloc(bytesNeeded * sizeof(char));

  if( uriUriStringToUnixFilenameA(uriCString, CFileName) != URI_SUCCESS )
  {
		/* Failure */
		cout << "ERROR: URIobject::getFileName, line " << __LINE__ << "\n";
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

void URIobject::normalizeUri()
{
	const unsigned int dirtyParts = uriNormalizeSyntaxMaskRequiredA(&uri);
	if (uriNormalizeSyntaxExA(&uri, dirtyParts) != URI_SUCCESS) 
	{
    /* Failure */
    cout << "ERROR: URIobject::normalizeUri, line " << __LINE__ << "\n";
	}
};

//-----------------------------------------------------------------------------

URIobject URIobject::operator+ (URIobject param)
{
	string left = this->getUriString();
	string right = param.getUriString();
	return URIobject( left + right );
	
};

//-----------------------------------------------------------------------------

/*
URIobject URIobject::operator= (URIobject param)
{
	uri = param.uri;
	uriString = param.uriString;
};
*/

//-----------------------------------------------------------------------------


const char* URIobject::replaceWhiteSpaces( const char* str )
{
	string slash = ("\\");
	string returnString = "";
	int i = 0;
	int c;
	
	while( str[i] )
	{
		c = str[i];
		if( isspace(c) )
		{
			returnString += slash ;
		}		
		returnString.push_back( str[i] );
		i++;
	}
	
	const char* returnCString = returnString.c_str();
	return returnCString;
	
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------




