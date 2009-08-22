//
//	Author: A.L. Hertog
//	Date: 22 Augustus 2009
//	License: GPL
//
//


#ifndef DATAASSISTANTGTKMM_H
#define DATAASSISTANTGTKMM_H

#include <gtkmm.h>

#include "Datahandler.h"
#include "Category.h"

#include <string>
using namespace std;



//! This class forms an assistant UI to guide the user in the process of creating a new datahandler.

class DataAssistantGTKMM : public Gtk::Assistant
{

	public:

		//! The default constructor.
		DataAssistantGTKMM( ); 

		//! The default destructor.
		~DataAssistantGTKMM(); 

  


	private:


    virtual void on_cancel(void);
    virtual void on_intro_finished(void);
    virtual void on_summary_finished(void);


		vector<string> folders;
		vector<string> fileTypes;
		vector<Category*> categories;


		// Page 0 Intro ---------------------------------------
		Gtk::Label* introLabel;


		// Page 1 Name ----------------------------------------
		Gtk::FileChooserWidget nameChooser;


		// Page 2 Folder selecting ----------------------------

		Gtk::HButtonBox folderButtonBox;
		Gtk::Button addFolder, delFolder;

		Gtk::FileChooserWidget folderChooser;

		Gtk::ScrolledWindow folderScrolledWindow;
		Gtk::TreeView folderTreeView;
		Glib::RefPtr<Gtk::ListStore> folderRefTreeModel;

			//Tree model columns:
			class ModelColumns : public Gtk::TreeModel::ColumnRecord
			{
			public:

				ModelColumns()
				{ add(col_id); add(col_folder); add(col_recursive); }

				Gtk::TreeModelColumn<unsigned int> col_id;
				Gtk::TreeModelColumn<Glib::ustring> col_folder;
				Gtk::TreeModelColumn<bool> col_recursive;
			};
		



		// Page 3 File type selecting -------------------------


		// Page 4	Category selecting --------------------------


		// Page 5 Overview ------------------------------------


};


#endif








