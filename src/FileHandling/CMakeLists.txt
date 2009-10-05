

# Make sure the compiler can find include files from our library.
include_directories ( ${URIOBJECT_INCLUDE_DIRS}
										)


LINK_DIRECTORIES ( ${URIOBJECT_LIBRARY_DIRS}
								 )
								 
# Add all source files in a variable
SET (	SRCS_FileHandling
				URIobject.cpp
		)


# Create a libary named Field
ADD_LIBRARY (FileHandling ${SRCS_FileHandling})

