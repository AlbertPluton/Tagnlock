//
//	Author: A.L. Hertog
//	Date: 9 October 2008
//	License: GPL
//
//


#ifndef DATAHANDLER_H
#define DATAHANDLER_H


#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "Category.h"

#include "ObjectData.h"

#include "Engine.h"


using namespace std;


//! This class holds all data of the "physical" objects being categorised.
/*!
	Each "physical" object is stored in an object of the class ObjectData. All these objects are added to a list named objectDataList. The iterator it, is used to cycle trough this list.
*/

class Datahandler
{

	public:
	
		//! The default constructor
		Datahandler();

		//! The default destructor
		~Datahandler();
	
	
		//! Add a predefined object to the list after the current position. This functions updates the value of the internal iterator.
		/*!
			All the data in the object is preserved.
		*/
		void addObject( ObjectData* data );
	
	
		//! Create and add a new ObjectData object to the list after the current position. This functions updates the value of the internal iterator.
		/*!
			 	This new object has a data structure according to the given category. There is no data in this object, it is empty.
				\param category the category corresponding to the object under consideration.
				\param name the name and or directory of the file/folder under consideration.

		*/
		void addNewObject( Category* category, string name );

		
		//! Get the first data object in the list. This functions updates the value of the internal iterator.
		ObjectData* getFirstObject();
		//! Get the last data object in the list. This functions updates the value of the internal iterator.
		ObjectData* getLastObject();		
		//! Get the current data object referring to the internal index.
		ObjectData* getCurrentObject();
		//! Get the next data object referring to the internal index. This functions updates the value of the internal iterator.
		ObjectData* getNextObject();
		//! Get the previous data object referring to the internal index. This functions updates the value of the internal iterator.
		ObjectData* getPreviousObject();
		//! Get the data object at a certain position in the list. This functions updates the value of the internal iterator.
		ObjectData* getObjectAt( int index );
		//! Get the size of the list.
		int getListSize();
		//! Returns the current position in the list
		int getPosition();

	
		//! Returns the name and directory of the next file to process
		string getNextFile();

		//! Returns a vector of strings of all files which still need to be processed. The first string is the string getNextFile returns.
		vector<string> filesToDo();

		//! Retruns a vector of all the file names currently being edited.
		vector<ObjectData*> filesBeingProcessed();

		//! Returns a vector of strings containing the names of the already processed files. 
		vector<string> filesDone();

		//! Updatas the done vector from the succes fully processed files. This function should be called when the toolchain has processed this object.
		void fileFinished( ObjectData* object );


		//! Update the todo file list in case new files have been added to the source directories.
		void updateFileList();



		//! Save the datahandler to a file.
		/*!
			\return True will be returned is the save is succesfull.
		*/
		bool save( string fileName );


		//! Load the datahandler from a file.
		/*!
			\param fileName the name of the file to load.
			\param engine is a pointer to the current engine. This is required to generate the categories vector.
			\return True is returned when all went well.
		*/
		bool load( string fileName, Engine* engine );



		//! Adds a folder to the folder which are used by this datahandler
		/*!
			/pram folder a string with the folder name.
			/pram searchRecursive a boolean indicating if subdirectories of folder should be used.
		*/
		void addFolder( string folder, bool searchRecursive );

		//! Returns a vector with all folders used by this datahandler.
		vector<string> getFolders();

		//! Returns a vector of booleans indicating which folders should be looked at recursively.
		vector<bool> getRecursive();


		//! Adds a file type to the vector with the corresponding category which should be used for this file.
		void addFileType( string type, Category* cat );

		//! Returns the file types this datahandler deals with.
		vector<string> getFileTypes();

		//! Returns the categories vector.
		vector<categories*> getCategories();


	private:
	
		//! A list with all data of every object which is being categorized. 
		/*!
			This list holds objects from the class ObjectData. This class holds the data of each individual object which is being categorized.
		*/
		list<ObjectData*> objectDataList;
		
		//! An iterator to loop trough the list.
		list<ObjectData*>::iterator it;
		
		//! An integer representation of the list iterator it. Starts from 1.
		int position;
		
		//! Increments the iterator and position. The function also checks that no invalid iterators (greater or smaller than the list) are tried to be made.
		void incrementIT();
		//! Decrements the iterator and position. The function also checks that no invalid iterators (greater or smaller than the list) are tried to be made.
		void decrementIT();
		

		vector<string> todo;
		vector<ObjectData*> processing;
		vector<string> done;

		vector<string> folders;
		vector<bool> recursive; // The data in the recursive vector corresponds to the data at the same index in the folders vector.
	
		vector<string> fileType;
		vector<Category*> categories; // The data in the categories vector corresponds to the data at the same index in the fileType vector.





		static bool stringToBool( string input );
		static string boolToString( bool input );
		

};

#endif




