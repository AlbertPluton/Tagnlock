//
//	Author: A.L. Hertog
//	Date: 15 October 2009
//	License: GPL
//
//



#ifndef DIALOGOPERATIONCHOOSERGTKMM_H
#define DIALOGOPERATIONCHOOSERGTKMM_H



#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "Toolchain.h"

#include <iostream>
#include <string>
using namespace std;



//! This class represents a dialog used to choose the type of operation node should be added to the toolchain.


class DialogOperationChooserGTKMM : public Gtk::Dialog
{
	
	public:
		
		//! The default constructor with a pointer to the parent window.
		DialogOperationChooserGTKMM( Gtk::Window* parent );
		
		//! The default destructor.
		~DialogOperationChooserGTKMM( );		
		
		//! Function displaying the dialog and adding the new node to the parent
		void chooseOperationNode( ToolchainNode* parent);

		//! Function displaying the dialog and adding the new node to the parent at the specified location.
		void chooseOperationNode( ToolchainNode* parent, int index );

	
	private:
		
		// Radiobuttons representing the possible operations
		Gtk::RadioButton radioTextFileStorage;
		Gtk::RadioButton radioExecuteSystemCommand;

};






#endif

