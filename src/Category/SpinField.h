//
//	Author: A.L. Hertog
//	Date: 09 October 2008
//	License: GPL
//
//

#ifndef SPINFIELD_H
#define SPINFIELD_H

#include "Field.h"

//! A class which defines a spin field.

class SpinField : public Field
{

	public:
	
		//! The constructor 
		/*!
			\sa Field::Field()
		*/	
		SpinField( string fieldLabel, bool fieldRequired, bool fieldReset );
		

		//! Expanded constructor
		/*
			\param minimum is the lowest possible value. If the pointer is equal to NULL there is no limit.
			\param maximum is the highest possible value. If the pointer is equal to NULL there is no limit.
			\param stepsize is the increment size of the field. Should not be equal to 0 unless adStep equals FALSE, in this way only manual entries are possible.
			\param adStep indicates if manually entered values are rounded to the nearest multiplication of the step size.
			\param decimals	is the number of decimals visible in the field.
			\param adDec indicates if manually entered values are displayed according to the value of decimals. If FALSE the fully entered value is displayed.
		*/
		SpinField( string fieldLabel, bool fieldRequired, bool fieldReset, double* minimum, 
							double* maximum, double stepsize, bool adStep, int decimals, bool adDec );
		

		
		//! A Construct which creates a SpinField from a description.
		/*!
			This constructor is used by Field::newField( vector<string> * description )
			\param description vector containing strings from a category definition file
		*/
		SpinField( vector<string> * description );


		//! The destructor	
		~SpinField();

		
		//! Get function for the type
		/*!
			\return The type of this field: SpinField.
		*/
		string getType();

		
		//! A virtual function to get a full description of the field with all its options.
		/*!
			This function returns information about this field. This can be used to generate a category definition file. 
			\return A pointer to a vector of strings. These strings contain all information of this field: type, label, required, reset, min, max, step, adhereStep, dec, adhereDec. 
		*/
		vector<string> getDescription();
		
		//! Returns a pointer to the lowest possible value of the spin field. NULL means that there is no limit to this value.	
		double* getMinimum();
		//! Returns a pointer to the highest possible value of the spin field. NULL means that there is no limit to this value.		
		double* getMaximum();
		//! Returns the increment size of the field.		
		double getStepsize();		
		//! Indicates whether or not manually entered values are rounded of to the nearest multiplication of the step size. Thus TRUE when rounding of.
		bool getAdhereStep();		
		//! Returns the number of decimals displayed in the field.
		int getDecimals();			
		//! Indicates whether manually entered values are displayed according to the number of decimals displayed. If FALSE the fully entered value is displayed.
		bool getAdhereDec();		

		//! Set the lowest possible value of the spin field. Set it equal to NULL to indicate that there is no limit.
		void setMinimum( double* minimum );	
		//! Set the highest possible value of the spin field. Set it equal to NULL to indicate that there is no limit.	
		void setMaximum( double* maximum );		
		//! Set the increment size of the spin field. This value should not be equal to zero unless adhereStep is FALSE, in this way only manual entries are possible.
		void setStepsize( double stepsize );	
		//! Indicated if manually entered values are rounded to the nearest multiplication of the step size.
		void setAdhereStep( bool adhere );		
		//! Set the number of displayed decimals.
		void setDecimals( int decimals );			
		//! Indicated if manually entered values are displayed according to the value of decimals. If FALSE the fully entered value is displayed.
		void setAdhereDec( bool adhere );			
		
		

	private:

		double* min;
		double* max;
		double step;
		int dec;
		bool adhereStep, adhereDec;



		//void readMinimum(); 		//!	Used in the constructor to get min from the definition file.
		//void readMaximum();			//!	Used in the constructor to get max from the definition file.
		//void readStepsize();		//! Used in the constructor to get step form the definition file.
		//void read

};


#endif


