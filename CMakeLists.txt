

project (FMS CXX)

# Put all the libaries in the /lib directory
#SET ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Put all the executables in the /bin directory
#SET ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )



ADD_SUBDIRECTORY (src/Category)
ADD_SUBDIRECTORY (src/test)
ADD_SUBDIRECTORY (src/Datahandler)




