//
//	Author: A.L. Hertog
//	Date: 9 January 2009
//	License: GPL
//
//

#include "CategoryWindowGTKMM.h"
#include "DataWindowGTKMM.h"
#include "ToolchainWindowGTKMM.h"
#include <string>
using namespace std;


int main (int argc, char **argv)
{
	string fileName = "src/UI/GTKMM/GTK_GUI.glade";

//  CategoryWindowGTKMM engine( argc, argv, fileName);


 	ToolchainWindowGTKMM engine3( argc, argv, fileName);

	// TODO Why do I get undefined refrences if this line is commented out.
	DataWindowGTKMM engine2( argc, argv, fileName);

};
