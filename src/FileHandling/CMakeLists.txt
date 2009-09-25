
# Make sure the compiler can find include files from our library.


# Add all source files in a variable
SET (	SRCS_FileHandling
				FileLocation.cpp
		)


# Create a libary named Field
ADD_LIBRARY (FileHandling ${SRCS_FileHandling})

