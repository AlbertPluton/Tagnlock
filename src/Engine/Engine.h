//
//	Author: A.L. Hertog
//	Date: 1 January 2009
//	License: GPL
//
//


#ifndef ENGINE_H
#define ENGINE_H

#include "Category.h"
#include "Field.h"
#include "Datahandler.h"
#include "ObjectData.h"
#include "Toolchain.h"
#include "ToolchainNode.h"


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



		// --- Functions relating to the general program flow ---------------------

		virtual void quit(){};


		// --- Functions relating to Category -------------------------------------

		//! Adds a category to the end of the vector categories and sets currentCategory to this value. 
		void addCategory( Category* cat );

		//! Retruns a pointer to the current category.
		Category* getCurrentCategory();

		//! Returns the category at the desired index.
		Category* getCategory( int index );

		//! Returns the size of the categories vector.
		int getCategoriesSize();

		//! Delete the category at the desired index from the vector.
		void deleteCategory( int index );

		//! Returns a pointer to categories.
		vector<Category*>* getCatVec();

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
		
		
		//! Returns the index of the current field.
		int getIndexCurrentField();
		
		//! Returns a pointer to the current field.
		Field* getCurrentField();
		
		//! Set the pointer currentField to field.
		void setCurrentField( int field );

		// Returns the size of the categories vector.
		int getNumberOfCategories();

		//! Returns the index of the current Category.
		int getIndexCurrentCategory();
		
		//! Sets the currentCategory index.
		void setCurrentCategory( int index );

		//! This virtual function is UI dependent. The UI should give the user the option to load a category from a file.
		virtual bool loadCategory(){};

		//! This virtual function is UI dependent. The UI should give the user the option to save a category to a file.
		virtual bool saveCategory(){};

		//! This virtual function is UI dependent. It should ask the user what kind of field to add to the current category.
		/*!
			The new field is added behind the current field.
		*/
		virtual void newField(){};
		
		//! This virtual function is UI dependent. It should be able to modify all atributes of the current field.
		virtual void modifyField(){};

		//! This virtual function is UI dependent. It should display all fields in the desired category.
		virtual void displayCategory( int index ){};




		// --- Functions relating to Datahandler ----------------------------------

		//! Adds a Datahandler to the end of the vector data.
		void addDatahandler( Datahandler* newData );

		//! Returns a pointer to the current Datahandler.
		Datahandler* getCurrentDatahandler( );

		//! Returns the Datahandler at the desired index.
		Datahandler* getDatahandler( int index );

		//! Delete the Datahandler at the desired index from the vector.
		void deleteDatahandler( int index );

		//! The return value of this function indicates wheather or not a datahandler object has been modified.
		bool getDatahandlerModified( int index );
		
		//! This function is used to alter the boolean indicating that changes have been made to a certain datahandler object.
		/*!
		This function should for example be used in a function like readDataFromUI.
		\param index the datahandler which has been (un)changed
		\param mod the value to which the boolean should be set TRUE to indicate modifications.
		*/
		void setDatahandlerModified( int index, bool mod );		

		//! Returns the index of the current Datahandler.
		int getCurrentDatahandlerIndex();
		
		//! Sets the currentDatahandler index.
		void setCurrentDatahandler( int index );
		
		//! This virtual function is UI dependent. It should display the current data object of the current Datahandler.
		virtual void displayDatahandlerObject(){};

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

		//! Execute a Toolchain on the current Datahandler object.
		void executeToolchain( int index );

		//! Execute a Toolchain on the indicated Datahandler object.
		void executeToolchain( int indexToolchain, int indexData );

		//! Delete the Toolchain at the desired index from the vector.
		void deleteToolchain( int index );

		//! The return value of this function indicates wheather or not a toolchain has been modified.
		bool getToolchainModified( int index );
		
		//! This function is used to alter teh boolean indicating that changes have been made to a certain toolchain.
		/*!
		This function should for example be used in functions like addToolchainOperation and modifyToolchainNode.
		\param index the toolchain which has been (un)changed
		\param mod the value to which the boolean should be set TRUE to indicate modifications.
		*/
		void setToolchainModified( int index, bool mod );		

		//! Returns the index of the current toolchain.
		int getCurrentToolchain();
		
		//! Sets the currentToolchain index.
		void setCurrentToolchain( int index );

		//! Returns a pointer to the current ToolchainNode object
		ToolchainNode* getCurrentToolchainNode();
		
		//! Sets the currentToolchainNode pointer to node.
		void setCurrentToolchainNode( ToolchainNode* node );

		//! This virutal function is UI dependent. It should display the current toolchain.
		virtual void dispalyToolchain(){};
		
		//! This virutal function is UI dependent. It should handel modifications to the current toolchain.
		/*!
			The function should ask the user what kind of Operation to add. The new node should be added as a child of the current ToolchainNode. After the node is added the function modifyToolchainNode can be called to edit the atributes of the node.
		*/
		virtual void addToolchainOperation(){}; 

		//! This virutal function is UI dependent. It should handel modifications to the current ToolchainNode.
		/*!
			The function should be able to display/modify all atributes of a ToolchainNode. 
		*/
		virtual void modifyToolchainNode(){};





	protected:


		vector<Category*> categories;
		vector<bool> categoryModified;		// Used to keep track of objects which are modified.
		int currentCategory;
		int currentField;

		vector<Datahandler*> data;
		vector<bool> dataModified;				// Used to keep track of objects which are modified.
		int currentDatahandler;

		vector<Toolchain*> toolchains;		
		vector<bool> toolchainModified;		// Used to keep track of objects which are modified.
		int currentToolchain;
		ToolchainNode* currentToolchainNode;



};

#endif

