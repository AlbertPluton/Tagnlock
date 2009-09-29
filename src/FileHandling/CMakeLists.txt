

# Make sure the compiler can find include files from our library.
include_directories ( /usr/include/uriparser
										)


# Add all source files in a variable
SET (	SRCS_FileHandling
				URIobject.cpp
		)


# Create a libary named Field
ADD_LIBRARY (FileHandling ${SRCS_FileHandling})

