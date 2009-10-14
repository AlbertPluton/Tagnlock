

# Make sure the compiler can find include files from our library.
#include_directories (	${CMAKE_BINARY_DIR}/src/Category
#											${CMAKE_BINARY_DIR}/src/Datahandler
#											${CMAKE_BINARY_DIR}/src/Toolchain
#											${CMAKE_BINARY_DIR}/src/Toolchain/Operations
#											${CMAKE_BINARY_DIR}/src/FileHandling		
#										)


# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )



# Add all source files in a variable
SET (	SRCS_Engine
			Engine.cpp
		)

		

# Create a libary named Field
#ADD_LIBRARY (Engine ${SRCS_Engine})

