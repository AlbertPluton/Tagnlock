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

#include <dirent.h>

#include "URIobject.h"

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
		void addNewObject( Category* category, URIobject* name );

		
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

	
		//! Returns the name and directory of the next file to process. This removes the file from the todo vector!!
		/*!
			To be correct, this function does not return item no. 1 of the todo vector but it pops the back.
			\returns A string with the file name and directory. If todo is empty the string will be equel to "" and a error is generated.
		*/
		URIobject* getNextFile();

		//! Returns a vector of strings of all files which still need to be processed. The first string is the string getNextFile returns.
		list<URIobject*> * filesToDo();

		//! Returns a vector of strings containing the names of the already processed files. 
		list<URIobject*> * filesDone();

		//! Updatas the objectDataList from the succes fully processed files. This function should be called when the toolchain has processed this object.
		void fileFinished( ObjectData* object );


		//! Update the todo file list in case new files have been added to the source directories.
		void updateFileList();



		//! Save the datahandler to a file with the name given in Datahandler::name.
		/*!
			\return True will be returned is the save is succesfull.
		*/		
		bool save( );

		//! Save the datahandler to a file.
		/*!
			\param fileName The name of the file. If equele to "" the name given in Datahandler::name
			\return True will be returned is the save is succesfull.
		*/
		bool save( string fileName );


		//! Load the datahandler from a file.
		/*!
			\param fileName the name of the file to load.
			\param catVec is a vector with all currently known categories by the engine.
			\return True is returned when all went well.
		*/
		bool load( string fileName, vector<Category*>* catVec );



		//! Adds a folder to the folder which are used by this datahandler
		/*!
			/pram folder a string with the folder name.
			/pram searchRecursive a boolean indicating if subdirectories of folder should be used.
		*/
		void addFolder( URIobject folder, bool searchRecursive );

		//! Returns a vector with all folders used by this datahandler.
		vector<URIobject> getFolders();

		//! Returns a vector of booleans indicating which folders should be looked at recursively.
		vector<bool> getRecursive();


		//! Adds a file type to the vector with the corresponding category which should be used for this file.
		void addFileType( string type, Category* cat );

		//! Returns the file types this datahandler deals with.
		vector<string> getFileTypes();

		//! Returns the categories vector.
		vector<Category*> getCategories();


		//! Sets the name of this datahandler.
		void setName( string strName );

		//! Returns the name of this datahandler. Name is set by the functions load and save.
		string getName();


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
		

		list<URIobject*> todo; 	
		list<URIobject*> done;	

		vector<URIobject> folders;
		vector<bool> recursive; // The data in the recursive vector corresponds to the data at the same index in the folders vector.
	
		vector<string> fileTypes;
		vector<Category*> categories; // The data in the categories vector corresponds to the data at the same index in the fileType vector.


		string name;


		static bool stringToBool( string input );
		static string boolToString( bool input );
		

		//! Function used by updateFileList to search for files in a dir
		/*!
			\param pdir Pointer to the directory beeing searched.
			\param rec Boolean indicating if the directroy should be search recursively.
			\returns A list of strings with all file names with desired file type(s).
		*/
		list<URIobject*> * searchDirectory( URIobject folder, bool rec );

		//! Check to see if a file has one of the desired types.
		bool correctType( string name );
		
		//! Search for a category matching the type of the given file.
		/*!
			\returns A pointer to the category. NULL if none was found.
		*/
		Category* getCategoryFromType( string fileName );

};

#endif




