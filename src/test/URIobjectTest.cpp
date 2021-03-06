//
//	Author: A.L. Hertog
//	Date: 30 September 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//



#include "URIobject.h"

#include <iostream>
#include <string>
using namespace std;


int main (int argc, char **argv)
{  

	string testString = "file:///home/Bart/test.txt";
	URIobject uri( testString );
	
	string uriString = uri.getUriString();
	string nameString = uri.getFileName( testString );
	
	cout << "testString: \"" << testString << "\"\n";
	cout << "uriString: \"" << uriString << "\"\n";
	cout << "nameString: \"" << nameString << "\"\n";

	return 0;
};
