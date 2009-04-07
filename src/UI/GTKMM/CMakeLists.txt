

MESSAGE ( "gtkmm include: \n ${GTKMM_INCLUDE_DIRS} \n " )
MESSAGE ( "glademm include: \n ${GLADEMM_INCLUDE_DIRS} \n " )

MESSAGE ( "gtkmm library: \n ${GTKMM_LIBRARY_DIRS} \n " )
MESSAGE ( "glademm library: \n ${GLADEMM_LIBRARY_DIRS} \n " )

MESSAGE ( "Lib output path: ${LIBRARY_OUTPUT_PATH} \n " )

# Make sure the compiler can find include files from our library.
include_directories (	${CMAKE_BINARY_DIR}/src/Category
											${CMAKE_BINARY_DIR}/src/Datahandler
											${CMAKE_BINARY_DIR}/src/Toolchain
											${CMAKE_BINARY_DIR}/src/Engine
											${GTKMM_INCLUDE_DIRS}
											${GLADEMM_INCLUDE_DIRS}
										)

LINK_DIRECTORIES ( ${LIBRARY_OUTPUT_PATH}
									 ${GTKMM_LIBRARY_DIRS}
									 ${GLADEMM_LIBRARY_DIRS}
								 )



# Add all source files in a variable
SET (	SRCS_EngineGTKMM
			EngineGTKMM.cpp
			FieldGTKMM.cpp
			${CMAKE_BINARY_DIR}/src/Engine/Engine.cpp
		)

		

# Create a libary named Field
ADD_LIBRARY ( EngineGTKMM ${SRCS_EngineGTKMM} ) 

