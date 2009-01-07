//
//	Author: A.L. Hertog
//	Date: 1 January 2009
//	License: GPL
//
//


#ifndef ENGINE_H
#define ENGINE_H

#include "Category.h"
#include "Datahandler.h"
#include "Toolchain.h"


#include <vector>
using namespace std;


//! The hart of the program.
/*! 
	The class Engine is the hart of the program binding UI, categories, data and toolchains together.
	Each UI should inherit from this class to aces the program components.
*/



class Engine
{


	public:
	
		//! The default constructor
		Engine();

		//! The destructor
		~Engine();




		// --- Functions relating to Category -------------------------------------

		//! Adds a category to the end of the vector categories.
		void addCategory( Category* cat );

		//! Returns the category at the desired index.
		Category* getCategory( int index );

		//! Delete the category at the desired index from the vector.
		void deleteCategory( int index );

		//! The return value of this function indicates wheather or not a category object has been modified.
		bool getCategoryModified( int index );
		
		//! This function is used to alter teh boolean indicating that changes have been made to a certain category object.
		/*!
		This function should for example be used in functions like addField and newField.
		\param index the category which has been (un)changed
		\param mod the value to which the boolean should be set TRUE to indicate modifications.
		*/
		void setCategoryModified( int index, bool mod );

		//! Add an exciting field to a category
		/*!
			\param indexCategory indicates to which category in the vector the field should be added.
			\param field is a pointer to the new field.
		*/
		void addField( int indexCategory, Field* field );

		//! This virtual function is UI dependent. It should ask the user what kind of new field to add field to a category.
		/*!
			\param indexCategory indicates to which category in the vector the field should be added.
		*/
		virtual void newField( int indexCategory ){};

		//! This virtual function is UI dependent. It should display all fields in the desired category.
		virtual void displayCategory( int index ){};




		// --- Functions relating to Datahandler ----------------------------------

		//! Adds a Datahandler to the end of the vector data.
		void addDatahandler( Datahandler* newData );

		//! Returns the Datahandler at the desired index.
		Datahandler* getDatahandler( int index );

		//! Delete the Datahandler at the desired index from the vector.
		void deleteDatahandler( int index );

		//! The return value of this function indicates wheather or not a datahandler object has been modified.
		bool getDataModified( int index );
		
		//! This function is used to alter teh boolean indicating that changes have been made to a certain datahandler object.
		/*!
		This function should for example be used in a function like readDataFromUI.
		\param index the datahandler which has been (un)changed
		\param mod the value to which the boolean should be set TRUE to indicate modifications.
		*/
		void setDataModified( int index, bool mod );		
		
		//! This virtual function is UI dependent. It should display the specified data object of the desired Datahandler.
		/*!
			\param indexDatahandler This index indicates which Datahandler object to use.
			\param indexObjectData This index indicates of which object the data should be shown.
		*/
		virtual void displayDatahandlerObject( int indexDatahandler, int indexObjectData ){};

		//! This virtual function is UI dependent. It should display the current data object of the next Datahandler.
		/*
				The variable currentDatahandler should be incremented.
		*/
		virtual void displayNextDatahandler(){};

		//! This virtual function is UI dependent. It should display the current data object of the previous Datahandler.
		/*
				The variable currentDatahandler should be decremented.
		*/
		virtual void displayPreviousDatahandler(){};

		//! This virtual function is UI dependent. It should display the next data object of the current Datahandler.
		virtual void displayNextObjectData(){};		

		//! This virtual function is UI dependent. It should display the previous data object of the current Datahandler.
		virtual void displayPreviousObjectData(){};		

		//! This virutal function is UI dependent. It should read newly entered data from the UI to the current Datahandler and corresponding ObjectData object and FieldData object.
		virtual void readDataFromUI(){};


		// --- Functions relating to Toolchain ------------------------------------

		//! adds a Toolchain to the end of the vector toolchains.
		void addToolchain( Toolchain* chain );
	
		//! Returns the Toolchain an the desired index.
		Toolchain* getToolchain( int index );

		//! Execute a Toolchain
		void executeToolchain( int index );

		//! Delete the Toolchain at the desired index from the vector.
		void deleteToolchain( int index );

		//! The return value of this function indicates wheather or not a toolchain has been modified.
		bool getToolchainModified( int index );
		
		//! This function is used to alter teh boolean indicating that changes have been made to a certain toolchain.
		/*!
		This function should for example be used in a function like ???TODO???.
		\param index the toolchain which has been (un)changed
		\param mod the value to which the boolean should be set TRUE to indicate modifications.
		*/
		void setToolchainModified( int index, bool mod );		


		//! This virutal function is UI dependent. It should display the desired toolchain.
		virtual void dispalyToolchain( int index ){};



	private:


		vector<Category*> categories;
		vector<bool> categoryModified;		// Used to keep track of objects which are modified.
		int currentCategory;

		vector<Datahandler*> data;
		vector<bool> dataModified;				// Used to keep track of objects which are modified.
		int currentData;

		vector<Toolchain*> toolchains;		
		vector<bool> toolchainModified;		// Used to keep track of objects which are modified.
		int currentToolchain;




};

#endif

