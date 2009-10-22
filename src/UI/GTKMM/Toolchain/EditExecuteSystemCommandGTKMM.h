//
//	Author: A.L. Hertog
//	Date: 22 October 2009
//	License: GPL
//
//


#ifndef EDITEXECUTESYSTEMCOMMANDGTKMM_H
#define EDITEXECUTESYSTEMCOMMANDGTKMM_H


#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "Datahandler.h"

#include "Toolchain.h"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "EditToolchainNodeGTKMM.h"

//! Class used to edit the poperties of an ExecuteSystemCommand toolchain operation node.

class EditExecuteSystemCommandGTKMM : public EditToolchainNodeGTKMM
{

	public:
	
		//! Default constructor
		EditExecuteSystemCommandGTKMM( ToolchainNode* pNode );
		
		//! Default destructor
		~EditExecuteSystemCommandGTKMM( );
	
	
	private:


		ExecuteSystemCommand* node;
	
		Gtk::Label labelCommand, labelArguments;
		Gtk::Entry entryCommand, entryArguments;
	
		// Callback functions
		void changedCommand();
		void changedArguments();		
	
};




#endif

