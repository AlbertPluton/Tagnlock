
#

# Make sure the compiler can find include files from our library.
include_directories ( ${CMAKE_BINARY_DIR}/src/Category 
											${CMAKE_BINARY_DIR}/src/Datahandler
											${CMAKE_BINARY_DIR}/src/Engine
											${CMAKE_BINARY_DIR}/src/Toolchain
										)




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
		)

		

# Create a libary named Field
ADD_LIBRARY (Datahandler ${SRCS_Datahandler})

