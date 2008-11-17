

# Make sure the compiler can find include files from our library.
include_directories (${CMAKE_BINARY_DIR}/src/Category)




# Add all source files in a variable
SET (	SRCS_Datahandler
			Datahandler.cpp
			FieldData.cpp
			FieldDataInt.cpp
			FieldDataFloat.cpp
			FieldDataDouble.cpp
			FieldDataString.cpp
			FieldDataBool.cpp
			ObjectData.cpp
			FileData.cpp
			FolderData.cpp
		)

		

# Create a libary named Field
ADD_LIBRARY (Datahandler ${SRCS_Datahandler})

