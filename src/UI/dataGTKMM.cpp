//
//	Author: A.L. Hertog
//	Date: 9 January 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
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

	DataWindowGTKMM engine( argc, argv, fileName);

};
