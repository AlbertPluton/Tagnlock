
#	Author: A.L. Hertog
#	Copyrights Pluton IT B.V. http://www.pluton.nl
#	License: GPL-v2

# Make sure the compiler can find include files from our library.
#INCLUDE_DIRECTORIES (	${CMAKE_BINARY_DIR}/src/Category 
#											${CMAKE_BINARY_DIR}/src/Datahandler 
#											${CMAKE_BINARY_DIR}/src/Toolchain 
#											${CMAKE_BINARY_DIR}/src/Toolchain/Operations
#											${GTKMM_INCLUDE_DIRS}
#											${GLADEMM_INCLUDE_DIRS}
#											${URIOBJECT_INCLUDE_DIRS}
#										)


# Make sure the linker can find the library once it is built.
#LINK_DIRECTORIES ( ${LIBRARY_OUTPUT_PATH}
#									 ${GTKMM_LIBRARY_DIRS}
#									 ${GLADEMM_LIBRARY_DIRS}
#									 ${URIOBJECT_LIBRARY_DIRS}
#								 )

# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )

# Add executable called FieldTest
ADD_EXECUTABLE (FieldTest FieldTest.cpp)

# Link the executable to the libary Field
TARGET_LINK_LIBRARIES (FieldTest Field Exceptions)



# Add executable called CategoryTest
ADD_EXECUTABLE (CategoryTest CategoryTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (CategoryTest Field Category Exceptions ${URIOBJECT_LIBRARIES} )



# Add executable called DatahandlerTest
ADD_EXECUTABLE (DatahandlerTest DatahandlerTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (DatahandlerTest Field Category Exceptions Datahandler ${URIOBJECT_LIBRARIES} )




# Add executable called ToolchainTest
ADD_EXECUTABLE (ToolchainTest ToolchainTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (ToolchainTest Field Category Exceptions Datahandler Toolchain ${URIOBJECT_LIBRARIES})




# Add executable called GTKMMTest
ADD_EXECUTABLE (GTKMMTest GTKMMTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (GTKMMTest ${GTKMM_LIBRARIES} ${GLADEMM_LIBRARIES} )



# Add executable called URIobjectTest
ADD_EXECUTABLE (URIobjectTest URIobjectTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (URIobjectTest ${URIOBJECT_LIBRARIES})


