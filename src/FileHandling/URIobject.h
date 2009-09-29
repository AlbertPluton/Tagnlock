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

		//! Constructor which creates an URI from the string fileName.
		URIobject( string fileName );
		
		//! Constructor which creates on object by setting uri to the c style uri.
		URIobject( UriUriA uriCstyle );
		
		//! Destructor
		~URIobject();
		
		
		
		//! Get the c style uri.
		UriUriA getUri();
		
		//! Get the uri as a string.
		string getUriString();
		
		//! Get the file name.
		string getFileName();
		
		
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

	private:

		UriUriA uri;



};



#endif
