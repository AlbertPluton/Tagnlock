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
//	EngineGTKMM engine( argc, argv, fileName);

// CategoryWindowGTKMM engine( argc, argv, fileName);

// DataWindowGTKMM engine( argc, argv, fileName);

 	ToolchainWindowGTKMM engine( argc, argv, fileName);
}
