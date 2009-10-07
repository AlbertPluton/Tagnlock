//
//	Author: A.L. Hertog
//	Date: 29 September 2009
//	License: GPL
//
//



#ifndef URIobject_H
#define URIobject_H

#include "Uri.h"

#include <iostream>
#include <string>
using namespace std;

//! A class to interface the c lib uriparser
class URIobject
{

	public:
	
		//! Default constructor
		URIobject( );

		//! Constructor which creates an URI from the string fileName.
		URIobject( string stringUri );
		
		//! Constructor which creates on object by setting uri to the c style uri.
//		URIobject( UriUriA uriCstyle );
		
		//! Normal copy constructor.
//		URIobject( const URIobject& uriObject );
		
		//! Destructor
		~URIobject();
		
				
		//! Convert the uriString to an UriUriA object.
		void setUri( string stringUri );
		
				
		//! Get the c style uri.
		UriUriA getUri();
		
		//! Get the uri as a string.
		string getUriString();
		
		//! Get the file name.
		string getFileName();
		
		//! Get the file name.
		string getFileName( string uriString );
		
		//! Return the folder TODO ????
		string getFolder();
		
		
		//! Normalize the uri by removing unnecesarry refrences, ../../ etc.
		void normalizeUri();

		//! Overload the + operator. 
		/*!
			Example: Now you will be able to add a folder file:///home/boss/ with a file text.txt
			uriTotal = uriFolder + uriFile;
		*/
		URIobject operator+ (URIobject);


		//! Overload the = operator.
//		URIobject operator= (URIobject);

	private:

		const char* replaceWhiteSpaces( const char* str );

		UriUriA uri;
		string uriString;


};



#endif
