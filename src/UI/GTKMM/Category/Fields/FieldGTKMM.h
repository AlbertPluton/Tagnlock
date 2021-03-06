//
//	Author: A.L. Hertog
//	Date: 30 January 2009
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//

#ifndef FIELDGTKMM_H
#define FIELDGTKMM_H

#include <gtkmm.h>
#include "Field.h"
#include "FieldData.h"
#include "FieldEditWidgetGTKMM.h"



//! This class holds pointer to the GTKMM opjects for a field.

class FieldGTKMM : public Gtk::EventBox
{

	public:
		
	
		//! Constructor which specifies the base field, index  and the corresponding data field. It is preferred to use the NewFieldGTKMM functions to create new objects because these are able to create the derived class based on the type of field.
		/*!
			\param pField A pointer to the original field object.
			\param dat A pointer to the correspond FieldData object.
			\param i The index of the base class.
		*/		
		FieldGTKMM( Field* pField, FieldData* dat = NULL, int i = -1 );
		
		//! The default destructor.
		~FieldGTKMM();



		//! Creates a new FieldGTKMM object specified by pField.
		static FieldGTKMM* newFieldGTKMM( Field* pField );
		
		//! Creates a new FieldGTKMM object specified by pField with a link to the pData as FieldData object. 
		static FieldGTKMM* newFieldGTKMM( Field* pField, FieldData* pData );

		//! Creates a new FieldGTKMM object specified by pField and with the index given. 
		static FieldGTKMM* newFieldGTKMM( Field* pField,  int i );

		//! Creates a new FieldGTKMM object specified by pField with a link to the pData as FieldData object and the index of the pField. 
		static FieldGTKMM* newFieldGTKMM( Field* pField, FieldData* pData, int i );

		


	
		//! Returns a widget edit the properties of the base field.
		virtual Gtk::Widget* getEditWidget(){};
		
		//! Updates the properties of the widgets.
		/*!
			This function should be called by the edit widget when the user has alterd some properties of a field.
		*/
		virtual void updateProperties(){};
		
		
	
		//! Extracts data from the FieldData object specified for this field and displays it in the widget.
		virtual void setData(){};
		
		//! Extracts the data which was entered in the widget and stores it in the FieldData object.
		virtual void getData(){};

			
		//! Returns a pointer to the base Field object.
		Field* getBaseField();
		
		//! Change the FieldData object
		void setFieldData( FieldData* pData ); 
		
		
		//! Set the index of the base class.
		void setIndex( int i );
		
		//! Function to get the index.
		int getIndex( );
		
		
		
		

		// Some stuff for the signals

		//! Function converting the signal signal_button_press_event from the eventbox base class to a signal_selected.
		virtual bool selected( GdkEventButton* event );


		//! Function emiting a changed signal.
		virtual void changed( );

		//! Signal indicating that the user has clicked on this field.
  	typedef sigc::signal<void, Field*, int> type_signal_selected;
  	
  	//! Signal indicating the user has entered/altered data in this field.
  	typedef sigc::signal<void, Field*, int> type_signal_changed;
  	
  	//! This is the signal to indicate a change of the selected field.
  	type_signal_selected get_signal_selected( void );

		//! Get function for signal_changed
		type_signal_changed get_signal_changed( void );






		//! Returns a pointer to the label widget.
		Gtk::Widget* getLabel();
		//! Returns a pointer to the required check button widget.
		Gtk::Widget* getRequired();
		//! Returns a pointer to the reset check button widget.		
		Gtk::Widget* getReset();
		//! Returns the entry widget.
		virtual Gtk::Widget* getEntry(){};
	
	
	
	protected:	

		//! This functiond updates the properties of the widgets defined in this class. This class beeing the parent class of Check-, Combo-, Spin- and Text-FieldGTKM.
		void updatePropertiesParentClass();


			
		// Widgets to house information.
		Gtk::Label label; 		
		Gtk::CheckButton required; 	
		Gtk::CheckButton reset;		
		
	
		
		type_signal_selected signal_selected;
		type_signal_changed signal_changed;
		
	
		// These can be used to refer back to the original class and its data.
		Field* baseField;
		FieldData* data;
		int index;


		Gtk::Widget* editWidget;
};

#endif

