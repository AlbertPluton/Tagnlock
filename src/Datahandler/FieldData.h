//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//

#ifndef FIELDDATA_H
#define FIELDDATA_H





//! This class is used as a front end to the standard data types.
/*!
	By using this class it is possible to place different data types in the same list. 
*/ 

template<class data_type>
class FieldData
{


	public:

		//! The default constructor.
		FieldData();

		//! Constructor which initializes the data.
		FieldData( data_type data1 );		

		//! The default destructor.
		~FieldData();
		

		//! Returns the the data from the current object.
		data_type getData();
		
		//! Fuction to set the data.
		void setData( data_type data1 );
		
		
		
		
		//! Returns the type of subclass is used to store the data.
		//FieldDataType getType();
		
		
		//! Compare the value of two FieldData objects for equality
		bool operator== ( FieldData* data2 );
		
		//! Compare the value of two FieldData objects for inequality
		bool operator!= ( FieldData* data2 );


	private:

		data_type data;

};


//-----------------------------------------------------------------------------


template<class data_type>
FieldData<data_type>::FieldData()
{

};

//-----------------------------------------------------------------------------
template<class data_type>
FieldData<data_type>::FieldData( data_type data1 )
{

};
	
//-----------------------------------------------------------------------------

template<class data_type>
FieldData<data_type>::~FieldData()
{

};

//-----------------------------------------------------------------------------

template<class data_type>
data_type FieldData<data_type>::getData()
{

};

//-----------------------------------------------------------------------------

template<class data_type>
void FieldData<data_type>::setData( data_type data1 )
{

};

//-----------------------------------------------------------------------------

//template<class data_type>
//FieldDataType FieldData<data_type>::getType()
//{

//};

//-----------------------------------------------------------------------------

template<class data_type>
bool FieldData<data_type>::operator== ( FieldData* data2 )
{

};

//-----------------------------------------------------------------------------

template<class data_type>
bool FieldData<data_type>::operator!= ( FieldData* data2 )
{

};

//-----------------------------------------------------------------------------


#endif
