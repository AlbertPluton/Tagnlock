

project (DMS CXX)


cmake_minimum_required(VERSION 2.4.7)



SET ( CMAKE_BUILD_TYPE Debug )

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


ADD_DEFINITIONS( -DDEBUG_MESSAGES_DEF )
# ADD_DEFINITIONS( -DTODO_DEF )




set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


find_package ( PkgConfig )

pkg_check_modules( GTKMM gtkmm-2.4 )
pkg_check_modules( GLADEMM libglademm-2.4 )




# Put all the libaries in the /lib directory
SET ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/ )

#SET ( CMAKE_LIBRARY_PATH ${PROJECT_BINARY_DIR}/lib )


# Put all the executables in the /bin directory
SET ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/ )


SET ( CMAKE_CXX_FLAGS_DEBUG -gstabs+ )


ADD_SUBDIRECTORY (src/Category)
ADD_SUBDIRECTORY (src/test)
ADD_SUBDIRECTORY (src/Datahandler)
ADD_SUBDIRECTORY (src/Toolchain)
ADD_SUBDIRECTORY (src/Toolchain/Operations)
ADD_SUBDIRECTORY (src/Engine)
ADD_SUBDIRECTORY (src/UI)
ADD_SUBDIRECTORY (src/UI/GTKMM)


