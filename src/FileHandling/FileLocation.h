//
//	Author: A.L. Hertog
//	Date: 25 September 2009
//	License: GPL
//
//

#include <iostream>
#include <string>
using namespace std;

//! A class to store file names 
class FileLocation
{

	public:

		FileLocation( string fileName );
		~FileLocation();
		
		string getUri();
		string getFileName();


	private:
	
		string name;



};
