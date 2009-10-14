
# Make sure the compiler can find include files from our library.
#include_directories ( ${CMAKE_BINARY_DIR}/src/Category 
#											${CMAKE_BINARY_DIR}/src/Datahandler
#											${CMAKE_BINARY_DIR}/src/Toolchain
#											${CMAKE_BINARY_DIR}/src/Toolchain/Operations
#											${URIOBJECT_INCLUDE_DIRS}								
#										)


# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )



# Add all source files in a variable
SET (	SRCS_Toolchain
				Toolchain.cpp
				ToolchainNode.cpp
				Operations/ExecuteSystemCommand.cpp
				Operations/TextFileStorage.cpp
		)


# Create a libary named Field
ADD_LIBRARY (Toolchain ${SRCS_Toolchain})

