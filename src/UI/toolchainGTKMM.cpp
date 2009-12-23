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

 	ToolchainWindowGTKMM engine( argc, argv, fileName);

};
