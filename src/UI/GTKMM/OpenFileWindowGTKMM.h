//
//	Author: A.L. Hertog
//	Date: 7 April 2009
//	License: GPL
//
//


#ifndef OPENFILEWINDOWGTKMM_H
#define OPENFILEWINDOWGTKMM_H

#include <gtkmm.h>

class OpenFileWindowGTKMM : public Gtk::Window
{

	public:
		OpenFileWindowGTKMM();
		virtual ~OpenFileWindowGTKMM();
		
		
	protected:
		//Signal handlers
		virtual void on_button_open_clicked();
		virtual void on_button_folder_clicked();
		
		//Child widgets
		Gtk::VButtonBox buttonBox;
		Gtk::Button button_Open, button_Folder;
	


};



#endif
