

# Make sure the compiler can find include files from our library.
include_directories (	${CMAKE_BINARY_DIR}/src/Category
											${CMAKE_BINARY_DIR}/src/Datahandler
											${CMAKE_BINARY_DIR}/src/Toolchain
											${CMAKE_BINARY_DIR}/src/Engine
											${CMAKE_BINARY_DIR}/src/UI/GTKMM
											${GTKMM_INCLUDE_DIRS}
											${GLADEMM_INCLUDE_DIRS}
										)

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${LIBRARY_OUTPUT_PATH}
									 ${GTKMM_LIBRARY_DIRS}
									 ${GLADEMM_LIBRARY_DIRS}
								 )



# Add all source files in a variable
SET (	SRCS_mainGTKMM
			mainGTKMM.cpp
		)

		

# Add executable called CategoryTest
ADD_EXECUTABLE (mainGTKMM mainGTKMM.cpp)

# Link the executable to the libaries Field and Category
TARGET_LINK_LIBRARIES ( mainGTKMM EngineGTKMM Category Field Exceptions Datahandler Toolchain ${GTKMM_LIBRARIES} ${GLADEMM_LIBRARIES})


