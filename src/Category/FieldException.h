//
//	Author: A.L. Hertog
//	Date: 15 September 2008
//	Copyrights Pluton IT B.V. http://www.pluton.nl
//	License: GPL-v2
//
//


#ifndef FIELDEXCEPTION_H
#define FIELDEXCEPTION_H

#include <exception>

#include <string>
using namespace std;


//! A class which defines exceptions which can occur during operations in the field class and its children.


class FieldException : public exception
{


	public:

		//! The constructor
		/*!
			\param errorNumber is the index number of error which caused this exception.
			\sa FieldException::errorString[]
		*/
		FieldException( int errorNumber );
	
		/*!
			\param errorNumber is the index number of error which caused this exception.
			\param type the type of field in which the exception occurred.
			\param label the label of the specific field.
		*/
		FieldException( int errorNumber, string type, string label );

		/*!
			\param errorNumber is the index number of error which caused this exception.
			\param type the type of field in which the exception occurred.
			\param label the label of the specific field.
			\param info additional information about the error. 
		*/
		FieldException( int errorNumber, string type, string label, string info );

		//! A copy constructor
		FieldException( const FieldException& fieldEx );

	
		//! The destructor
		~FieldException() throw();
	
	
	
		//! Set function for the field type
		/*!
			Use this function to set the type of field in which this exception occurred.
		*/
		void setFieldType( string type );
		
		//! Set function for the field label
		/*!
			Use this function to set the field label. This to be able to identify the field in which this exception occurred.
		*/	
		void setFieldLabel( string label );
	
		
		string getFieldType();
		string getFieldLabel();
		string getErrorString();
		string getInfoString();
		int getError();
	
		//! Add additional information 
		/*!
			Add additional information to this exception. For example one can use this function to add the file name and line number of the category file which was been processed.
		*/
		void addInfo( const string& info );
	
		virtual const char* what() const throw();

	
	private:
	
		string fieldType;
		string fieldLabel;
		string infoString;
		int error;
		
		//! This array contains all the error which can cause this exception to be thrown.
		static const string errorString [];
																		

}; 

#endif
