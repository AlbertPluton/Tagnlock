

#MESSAGE ( "gtkmm include: \n ${GTKMM_INCLUDE_DIRS} \n " )
#MESSAGE ( "glademm include: \n ${GLADEMM_INCLUDE_DIRS} \n " )
#MESSAGE ( "poppler include: \n ${POPPLER_INCLUDE_DIRS} \n " )


#MESSAGE ( "gtkmm library: \n ${GTKMM_LIBRARY_DIRS} \n " )
#MESSAGE ( "glademm library: \n ${GLADEMM_LIBRARY_DIRS} \n " )
#MESSAGE ( "poppler library: \n ${POPPLER_LIBRARY_DIRS} \n " )


#MESSAGE ( "Lib output path: ${LIBRARY_OUTPUT_PATH} \n " )




# Make sure the compiler can find include files from our library.
include_directories (	${CMAKE_BINARY_DIR}/src/Category
											${CMAKE_BINARY_DIR}/src/Datahandler
											${CMAKE_BINARY_DIR}/src/Toolchain
											${CMAKE_BINARY_DIR}/src/Engine
											${CMAKE_BINARY_DIR}/src/UI/GTKMM/
											${CMAKE_BINARY_DIR}/src/UI/GTKMM/Category
											${CMAKE_BINARY_DIR}/src/UI/GTKMM/Category/Fields
											${CMAKE_BINARY_DIR}/src/UI/GTKMM/Data
											${CMAKE_BINARY_DIR}/src/UI/GTKMM/GeneralGTKMM																		
											${GTKMM_INCLUDE_DIRS}
											${GLADEMM_INCLUDE_DIRS}
											${POPPLER_GLIB_INCLUDE_DIRS}
  										${URIOBJECT_INCLUDE_DIRS}
										)

LINK_DIRECTORIES ( ${LIBRARY_OUTPUT_PATH}
									 ${GTKMM_LIBRARY_DIRS}
									 ${GLADEMM_LIBRARY_DIRS}
									 ${POPPLER_GLIB_LIBRARY_DIRS}
									 ${URIOBJECT_LIBRARY_DIRS}
								 )



# Add all source files in a variable
SET (	SRCS_EngineGTKMM
			EngineGTKMM.cpp
			Data/DataWindowGTKMM.cpp
			Data/DisplayFile.cpp
			Data/DisplayFilePDF.cpp
			Data/DataAssistantGTKMM.cpp
			Category/CategoryWindowGTKMM.cpp
			Category/Fields/FieldGTKMM.cpp
			Category/Fields/TextFieldGTKMM.cpp
			Category/Fields/CheckFieldGTKMM.cpp
			Category/Fields/SpinFieldGTKMM.cpp
			Category/Fields/ComboFieldGTKMM.cpp
			Category/CategoryGTKMM.cpp
			Category/CategoryTreeGTKMM.cpp
			Category/Fields/FieldEditWidgetGTKMM.cpp
			Category/Fields/FieldSpinEditWidgetGTKMM.cpp
			Category/Fields/FieldComboEditWidgetGTKMM.cpp
			${CMAKE_BINARY_DIR}/src/Engine/Engine.cpp	
			GeneralGTKMM/YesNoToggleButtonGTKMM.cpp
		)

		

# Create a libary named Field
ADD_LIBRARY ( EngineGTKMM ${SRCS_EngineGTKMM} ) 

