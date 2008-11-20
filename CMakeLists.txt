

project (DMS CXX)

SET ( CMAKE_BUILD_TYPE Debug )

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)








# Put all the libaries in the /lib directory
SET ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Put all the executables in the /bin directory
SET ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )



ADD_SUBDIRECTORY (src/Category)
ADD_SUBDIRECTORY (src/test)
ADD_SUBDIRECTORY (src/Datahandler)




