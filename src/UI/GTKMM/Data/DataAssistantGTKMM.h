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

#include <iostream>
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
		Gtk::Label introLabel;


		// Page 1 Name ----------------------------------------
		Gtk::Label nameLabel;
		Gtk::Entry nameEntry;
		Gtk::Button nameButton;
		Gtk::Table nameTable;


		// Page 2 Folder selecting ----------------------------
		Gtk::VBox folderBox;
		Gtk::HButtonBox folderButtonBox;
		Gtk::Button addFolder, delFolder;

		Gtk::ScrolledWindow folderScrolledWindow;
		Gtk::TreeView folderTreeView;
		Glib::RefPtr<Gtk::ListStore> folderRefTreeModel;
		Glib::RefPtr<Gtk::TreeSelection> folderTreeSelection;
		
		int rowIndex;





		// Page 3 File type and Category selecting -------------------------
		Gtk::Table fileTable;
		Gtk::Label fileLabel;
		Gtk::ComboBoxEntryText fileEntry;

	

		// Page 5 Confirm -------------------------------------
		Gtk::Label confirmLabel;


		//Tree model columns:
		class ModelColumns : public Gtk::TreeModel::ColumnRecord
		{
		public:

			ModelColumns()
			{ add(col_id); add(col_folder); add(col_recursive); add(col_type); add(col_category); }

			Gtk::TreeModelColumn<unsigned int> col_id;
			Gtk::TreeModelColumn<Glib::ustring> col_folder;
			Gtk::TreeModelColumn<bool> col_recursive;
			Gtk::TreeModelColumn<Glib::ustring> col_type;
			Gtk::TreeModleColumn<Glib::ustring> col_category;
			
		};
		
		ModelColumns mColumns;


		// FUCNTIONS --------------------------------------------------------------

		// Page 0 Intro ---------------------------------------

		// Page 1 Name ----------------------------------------
		void on_nameButton();

		// Page 2 Folder selecting ----------------------------
		void on_addFolder();
		void on_delFolder();


		// Page 3 File type selecting -------------------------
		void on_entry_changed();

		// Page 4	Category selecting --------------------------


		// Page 5 Confirm -------------------------------------

};


#endif








