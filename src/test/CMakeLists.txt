



# Make sure the compiler can find include files from our Hello library.
include_directories (${CMAKE_BINARY_DIR}/src/Category)


# Make sure the linker can find the Hello library once it is built.
link_directories ( ${LIBRARY_OUTPUT_PATH} )



# Add executable called FieldTest
ADD_EXECUTABLE (FieldTest FieldTest.cpp)

# Link the executable to the libary Field
TARGET_LINK_LIBRARIES (FieldTest Field Exceptions)


# Add executable called CategoryTest
ADD_EXECUTABLE (CategoryTest CategoryTest.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES (CategoryTest Field Category Exceptions)

