//
//	Author: A.L. Hertog
//	Date: 22 October 2009
//	License: GPL
//
//


#ifndef EDITTOOLCHAINNODEGTKMM_H
#define EDITTOOLCHAINNODEGTKMM_H

#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "Datahandler.h"

#include "Toolchain.h"



#include <iostream>
#include <string>
#include <sstream>
using namespace std;


//! A class to display some widgets which are used to edit a toolchainNode in the toolchain window.

class EditToolchainNodeGTKMM : public Gtk::Table
{


	public:

		//! Default constructor
		EditToolchainNodeGTKMM( ToolchainNode* pNode );

		//! Default destructor.
		~EditToolchainNodeGTKMM( );

		//! Looks at the type of pNode and returns the correct edit widget.
		static EditToolchainNodeGTKMM* newNodeEditWidget( ToolchainNode* pNode );


		//! The signal to indicate a change in the configuration of this node.
		typedef sigc::signal<void> type_signal_changed;
		
		//! Returns the signal changed.
		type_signal_changed signal_changed();


	protected:

		Gtk::AttachOptions attachX;
		Gtk::AttachOptions attachY;
		
		int rows, columns;

		// The signal to indicate a change in the configuration of this field.
	 	type_signal_changed m_signal_changed;		


	private:

		// Call back functions
		void changedName();
		void changedDescription();

		Gtk::Label labelType, type, labelName, labelDescription;
		Gtk::Entry entryName, entryDescription;

		ToolchainNode* node;


		

		
};


#endif

