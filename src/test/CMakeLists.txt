



# Make sure the compiler can find include files from our library.
include_directories (	${CMAKE_BINARY_DIR}/src/Category 
											${CMAKE_BINARY_DIR}/src/Datahandler 
											${CMAKE_BINARY_DIR}/src/Toolchain 
											${CMAKE_BINARY_DIR}/src/Toolchain/Operations
											/usr/include/libglademm-2.4
											/usr/include/glibmm-2.4
										)


# Make sure the linker can find the library once it is built.
#LINK_DIRECTORIES( ${LIBRARY_OUTPUT_PATH} )


# Add executable called FieldTest
ADD_EXECUTABLE (FieldTest FieldTest.cpp)

# Link the executable to the libary Field
TARGET_LINK_LIBRARIES (FieldTest Field Exceptions)



# Add executable called CategoryTest
ADD_EXECUTABLE (CategoryTest CategoryTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (CategoryTest Field Category Exceptions)



# Add executable called CategoryTest
ADD_EXECUTABLE (DatahandlerTest DatahandlerTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (DatahandlerTest Field Category Exceptions Datahandler)




# Add executable called CategoryTest
ADD_EXECUTABLE (ToolchainTest ToolchainTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (ToolchainTest Field Category Exceptions Datahandler Toolchain)




# Add executable called CategoryTest
ADD_EXECUTABLE (GTKMMTest GTKMMTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (GTKMMTest libglademm-2.4 gtkmm )



