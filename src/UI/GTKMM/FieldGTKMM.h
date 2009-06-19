//
//	Author: A.L. Hertog
//	Date: 30 January 2009
//	License: GPL
//
//

#ifndef FIELDGTKMM_H
#define FIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"

//! This class holds pointer to the GTKMM opjects for a field.

class FieldGTKMM : public Gtk::EventBox
{

	public:
		
		//! The default constructor requires a pointer to a Field object to beable to determine what kind of entry field should be created.
		/*!
			\param field A pointer to the original class.
			\param i The index number of the orginal class.
		*/
		FieldGTKMM( Field* field, int i );
		
		//! The default destructor.
		~FieldGTKMM();

		//! Returns a pointer to the label widget.
		Gtk::Widget* getLabel();
		//! Returns a pointer to the required check button widget.
		Gtk::Widget* getRequired();
		//! Returns a pointer to the reset check button widget.		
		Gtk::Widget* getReset();
		//! Returns a pointer to the entry field widget.
		Gtk::Widget* getEntryField();
		
	


		//! Function to alter the index number when the original class has been rearagened.
		void setIndex( int i );
		
		//! The the index.
		int getIndex();
		
		
		

		// Some tuff for the signals

		virtual bool selected( GdkEventButton* event );

  	typedef sigc::signal<void, int> type_signal_selected;
  	
  	//! This is the signal to indicate a change of the selected field.
  	type_signal_selected get_signal_selected( void );


	
	private:

		Gtk::HBox hBox;


		Gtk::Widget* label; 		//Gtk::Label label;
		Gtk::Widget* required; 	// Gtk::CheckButton required;
		Gtk::Widget* reset;			//Gtk::CheckButton reset;
		Gtk::Widget* entryField;
		
		// Required when the field is a ComboField with ComboType ComboRadio.
		Gtk::RadioButton* radioButtons; // This is a pointer to the first element in an array;

		
		type_signal_selected signal_selected;
	
	
		// These can be used to reffer back to the original class.
		Field* baseField;
		int index;
		
		
		// These are to configure the spinbuttons at some maximum and minimum
		static const int defaultMaximum = 1000000;
		static const int defaultMinimum = -1000000;
	
};

#endif

