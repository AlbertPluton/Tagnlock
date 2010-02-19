
#	Author: A.L. Hertog
#	Copyrights Pluton IT B.V. http://www.pluton.nl
#	License: GPL-v2

# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )



# Add all source files in a variable
SET (	SRCS_Engine
			Engine.cpp
			Configuration.cpp
		)

		

# Create a libary named Field
#ADD_LIBRARY (Engine ${SRCS_Engine})

