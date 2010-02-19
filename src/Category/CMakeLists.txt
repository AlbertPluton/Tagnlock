
#	Author: A.L. Hertog
#	Copyrights Pluton IT B.V. http://www.pluton.nl
#	License: GPL-v2

# Make sure the compiler can find include files from our library.
#include_directories (	${URIOBJECT_INCLUDE_DIRS}
#										)


# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )
										
										
# Add all source files in a variable
SET (	SRCS_Field
			Field.cpp
			TextField.cpp
			CheckField.cpp
			ComboField.cpp
			SpinField.cpp
		)
		
SET ( SRCS_Category
			Category.cpp
		)
		
SET ( SRCS_Exceptions
			FieldException.cpp
		)


# Create a libary named Field
ADD_LIBRARY (Field ${SRCS_Field})

# Create a libary named Category
ADD_LIBRARY ( Category ${SRCS_Category} )

# Create a libary named Exceptions
ADD_LIBRARY ( Exceptions ${SRCS_Exceptions} )

