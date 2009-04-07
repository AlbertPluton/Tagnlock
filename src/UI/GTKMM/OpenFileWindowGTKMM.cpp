//
//	Author: A.L. Hertog
//	Date: 7 April 2009
//	License: GPL
//
//


#include "OpenFileWindowGTKMM.h"
#include <iostream>


//-----------------------------------------------------------------------------

OpenFileWindowGTKMM::OpenFileWindowGTKMM() : button_Open("Open"), button_Folder("Choose Folder")
{
  set_title("Gtk::FileSelection example");

  add(buttonBox);

  buttonBox.pack_start(button_Open);
  button_Open.signal_clicked().connect(sigc::mem_fun(*this, &OpenFileWindowGTKMM::on_button_open_clicked) );

  buttonBox.pack_start(button_Folder);
  button_Folder.signal_clicked().connect(sigc::mem_fun(*this, &OpenFileWindowGTKMM::on_button_folder_clicked) );

  show_all_children();
}

//-----------------------------------------------------------------------------


OpenFileWindowGTKMM::~OpenFileWindowGTKMM()
{
}

//-----------------------------------------------------------------------------


void OpenFileWindowGTKMM::on_button_folder_clicked()
{
  Gtk::FileChooserDialog dialog("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button("Select", Gtk::RESPONSE_OK);

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Select clicked." << std::endl;
      std::cout << "Folder selected: " << dialog.get_filename()
          << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

//-----------------------------------------------------------------------------


void OpenFileWindowGTKMM::on_button_open_clicked()
{
  Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  Gtk::FileFilter filter_text;
  filter_text.set_name("Text files");
  filter_text.add_mime_type("text/plain");
  dialog.add_filter(filter_text);

  Gtk::FileFilter filter_cpp;
  filter_cpp.set_name("C/C++ files");
  filter_cpp.add_mime_type("text/x-c");
  filter_cpp.add_mime_type("text/x-c++");
  filter_cpp.add_mime_type("text/x-c-header");
  dialog.add_filter(filter_cpp);

  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}


