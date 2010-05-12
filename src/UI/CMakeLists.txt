
#	Author: A.L. Hertog
#	Copyrights Pluton IT B.V. http://www.pluton.nl
#	License: GPL-v2

# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )


# Add all source files in a variable
SET (	SRCS_mainGTKMM
			mainGTKMM.cpp
		)

		

# Add executable called CategoryTest
ADD_EXECUTABLE (mainGTKMM mainGTKMM.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES ( mainGTKMM EngineGTKMM Category Field Exceptions Datahandler Toolchain ${GTKMM_LIBRARIES} ${GLADEMM_LIBRARIES} ${POPPLER_GLIB_LIBRARIES} ${URIOBJECT_LIBRARIES})

# Add executable called CategoryTest
ADD_EXECUTABLE (tagnlock dataGTKMM.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES ( tagnlock EngineGTKMM Category Field Exceptions Datahandler Toolchain ${GTKMM_LIBRARIES} ${GLADEMM_LIBRARIES} ${POPPLER_GLIB_LIBRARIES} ${URIOBJECT_LIBRARIES})

# Add executable called CategoryTest
ADD_EXECUTABLE (toolchainGTKMM toolchainGTKMM.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES ( toolchainGTKMM EngineGTKMM Category Field Exceptions Datahandler Toolchain ${GTKMM_LIBRARIES} ${GLADEMM_LIBRARIES} ${POPPLER_GLIB_LIBRARIES} ${URIOBJECT_LIBRARIES})

# Add executable called CategoryTest
ADD_EXECUTABLE (categoryGTKMM categoryGTKMM.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES ( categoryGTKMM EngineGTKMM Category Field Exceptions Datahandler Toolchain ${GTKMM_LIBRARIES} ${GLADEMM_LIBRARIES} ${POPPLER_GLIB_LIBRARIES} ${URIOBJECT_LIBRARIES})

