//
//	Author: A.L. Hertog
//	Date: 22 October 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef EDITTEXTFILESTORAGEGTKMM_H
#define EDITTEXTFILESTORAGEGTKMM_H


#include <libglademm.h>
#include <libglademm/xml.h>
#include <gtkmm.h>

#include "Toolchain.h"

#include "YesNoToggleButtonGTKMM.h"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;


#include "EditToolchainNodeGTKMM.h"



class EditTextFileStorageGTKMM : public EditToolchainNodeGTKMM
{

	public:

		EditTextFileStorageGTKMM( ToolchainNode* pNode );

		~EditTextFileStorageGTKMM();




	private:
	
		TextFileStorage* node;
		
		Gtk::Label labelLocation, labelFileName, labelIndividual;
		Gtk::Entry entryLocation, entryFileName;
		YesNoToggleButtonGTKMM buttonIndividual;
		
		// Call back functions
		void changedLocation();
		void changedFileName();
		void changedIndividual();



};

#endif

