

# Make sure the compiler can find include files from our library.
include_directories (	${CMAKE_BINARY_DIR}/src/Category
											${CMAKE_BINARY_DIR}/src/Datahandler
											${CMAKE_BINARY_DIR}/src/Toolchain
											${CMAKE_BINARY_DIR}/src/FileHandling		
										)




# Add all source files in a variable
SET (	SRCS_Engine
			Engine.cpp
		)

		

# Create a libary named Field
#ADD_LIBRARY (Engine ${SRCS_Engine})

