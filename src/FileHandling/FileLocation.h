//
//	Author: A.L. Hertog
//	Date: 25 September 2009
//	License: GPL
//
//

#include <iostream>
#include <string>
using namespace std;

//! A class to store file names and locations
class FileLocation
{

	public:

		FileLocation( string uriString );
		~FileLocation();
		
		string getUri();
		string getFileName();
		string getFileLocationUri();
		string getFileLocation();

	private:
	
		string uri;



};
