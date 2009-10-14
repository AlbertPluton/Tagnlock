

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
pkg_check_modules( POPPLER_GLIB poppler-glib )

# This lib is not found by pkg-config, for now this will do 29092009
SET( URIOBJECT_INCLUDE_DIRS /usr/include/uriparser ${CMAKE_BINARY_DIR}/src/FileHandling )
SET( URIOBJECT_LIBRARY_DIRS /usr/lib/ )
SET( URIOBJECT_LIBRARIES FileHandling uriparser )


# Put all the libaries in the /lib directory
SET ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/ )

#SET ( CMAKE_LIBRARY_PATH ${PROJECT_BINARY_DIR}/lib )


# Put all the executables in the /bin directory
SET ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/ )


SET ( CMAKE_CXX_FLAGS_DEBUG -gstabs+ )



# Make a central variable of all include directories
SET ( ALL_INCLUDE_DIRS
			${CMAKE_BINARY_DIR}/src/Category
			${CMAKE_BINARY_DIR}/src/Datahandler
			${CMAKE_BINARY_DIR}/src/Toolchain
			${CMAKE_BINARY_DIR}/src/Toolchain/Operations
			${CMAKE_BINARY_DIR}/src/Engine
			${CMAKE_BINARY_DIR}/src/UI/GTKMM
			${CMAKE_BINARY_DIR}/src/UI/GTKMM/Category
			${CMAKE_BINARY_DIR}/src/UI/GTKMM/Category/Fields
			${CMAKE_BINARY_DIR}/src/UI/GTKMM/Data						
			${CMAKE_BINARY_DIR}/src/UI/GTKMM/GeneralGTKMM
			${CMAKE_BINARY_DIR}/src/UI/GTKMM/Toolchain
			${GTKMM_INCLUDE_DIRS}
			${GLADEMM_INCLUDE_DIRS}
			${POPPLER_GLIB_INCLUDE_DIRS}
			${URIOBJECT_INCLUDE_DIRS}
		)
		
		
# Make a central variable of all link directories
SET (	ALL_LINK_DIRS
			${LIBRARY_OUTPUT_PATH}
		 	${GTKMM_LIBRARY_DIRS}
		 	${GLADEMM_LIBRARY_DIRS}
		 	${POPPLER_GLIB_LIBRARY_DIRS}
		 	${URIOBJECT_LIBRARY_DIRS}
		)


ADD_SUBDIRECTORY (src/Category)
ADD_SUBDIRECTORY (src/test)
ADD_SUBDIRECTORY (src/Datahandler)
ADD_SUBDIRECTORY (src/Toolchain)
ADD_SUBDIRECTORY (src/Toolchain/Operations)
ADD_SUBDIRECTORY (src/Engine)
ADD_SUBDIRECTORY (src/UI)
ADD_SUBDIRECTORY (src/UI/GTKMM)
ADD_SUBDIRECTORY (src/UI/GTKMM/Category)
ADD_SUBDIRECTORY (src/UI/GTKMM/Category/Fields)
ADD_SUBDIRECTORY (src/UI/GTKMM/Data)
ADD_SUBDIRECTORY (src/UI/GTKMM/GeneralGTKMM)
ADD_SUBDIRECTORY (src/UI/GTKMM/Toolchain)
ADD_SUBDIRECTORY (src/FileHandling)



