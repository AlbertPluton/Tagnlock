

# Make sure the compiler can find include files from our library.
include_directories ( ${URIPARSER_INCLUDE_DIRS}
										)


LINK_DIRECTORIES ( ${URIPARSER_LIBRARY_DIRS}
								 )
								 
# Add all source files in a variable
SET (	SRCS_FileHandling
				URIobject.cpp
		)


# Create a libary named Field
ADD_LIBRARY (FileHandling ${SRCS_FileHandling})

