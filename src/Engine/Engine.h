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


		//! This virtual function is UI dependent. It should display all fields in the desired category.
		virtual void displayCategory( int index );




		// --- Functions relating to Datahandler ----------------------------------

		//! Adds a Datahandler to the end of the vector data.
		void addDatahandler( Datahandler* data );

		//! Returns the Datahandler at the desired index.
		Datahandler* getDatahandler( int index );

		//! Delete the Datahandler at the desired index from the vector.
		void deleteDatahandler( int index );

		
		//! This virtual function is UI dependent. It should display the specified data object of the desired Datahandler.
		/*!
			\param indexDatahandler This index indicates which Datahandler object to use.
			\param indexObjectData This index indicates of which object the data should be shown.
		*/
		virtual void displayDatahandlerObject( int indexDatahandler, int indexObjectData );

		//! This virtual function is UI dependent. It should display the current data object of the next Datahandler.
		/*
				The variable currentDatahandler should be incremented.
		*/
		virtual void displayNextDatahandler();

		//! This virtual function is UI dependent. It should display the current data object of the previous Datahandler.
		/*
				The variable currentDatahandler should be decremented.
		*/
		virtual void displayPreviousDatahandler();

		//! This virtual function is UI dependent. It should display the next data object of the current Datahandler.
		virtual void displayNextObjectData();		

		//! This virtual function is UI dependent. It should display the previous data object of the current Datahandler.
		virtual void displayPreviousObjectData();		



		// --- Functions relating to Toolchain ------------------------------------

		//! adds a Toolchain to the end of the vector toolchains.
		void addToolchain( Toolchain* chain );
	
		//! Returns the Toolchain an the desired index.
		Toolchain* getToolchain( int index );

		//! Delete the Toolchain at the desired index from the vector.
		void deleteToolchain( int index );




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

