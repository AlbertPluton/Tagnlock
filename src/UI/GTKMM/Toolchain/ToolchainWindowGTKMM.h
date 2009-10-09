//
//	Author: A.L. Hertog
//	Date: 7 October 2009
//	License: GPL
//
//

#ifndef TOOLCHAINWINDOWGTKMM
#define TOOLCHAINWINDOWGTKMM



#include "EngineGTKMM.h"

#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include <iostream>
#include <string>
using namespace std;




//! This class is an interface to the toolchain window and the engine. It is used to create new and alter exciting toolchains.

class ToolchainWindowGTKMM : public EngineGTKMM
{

	public:
		
		//! Default constructor
		ToolchainWindowGTKMM( int argc, char **argv, string gladeFileName );
		
		//! Default destructor
		~ToolchainWindowGTKMM();

	private:



};

#endif

