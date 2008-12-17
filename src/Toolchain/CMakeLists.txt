
# Make sure the compiler can find include files from our library.
include_directories (${CMAKE_BINARY_DIR}/src/Category ${CMAKE_BINARY_DIR}/src/Datahandler)



# Add all source files in a variable
SET (	SRCS_Toolchain
				Toolchain.cpp
				ToolchainNode.cpp
				ToolchainOperation.cpp
				Operations/ExecuteSystemCommand.cpp
				Operations/TextFileStorage.cpp
		)


# Create a libary named Field
ADD_LIBRARY (Toolchain ${SRCS_Toolchain})

