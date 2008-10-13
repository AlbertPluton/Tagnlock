//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//

#ifndef FIELDDATA_H
#define FIELDDATA_H


template <class T>
class FieldData
{


	public:

		FieldData();
		FieldData( T dat );
		~FieldData();
		
		T getData();
		void setData( T dat );


	private:

		T data;


};


//=============================================================================


FieldData::FieldData()
{

};


//-----------------------------------------------------------------------------


FieldData::FieldData( T dat )
{
	data = dat
}


//-----------------------------------------------------------------------------


FieldData::~FieldData()
{

};


//-----------------------------------------------------------------------------


T FieldData::getData()
{
	return data;
};


//-----------------------------------------------------------------------------


void FieldData::setData( T dat )
{
	data = dat;
};


//-----------------------------------------------------------------------------





#endif
