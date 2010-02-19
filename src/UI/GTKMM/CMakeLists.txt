
#	Author: A.L. Hertog
#	Copyrights Pluton IT B.V. http://www.pluton.nl
#	License: GPL-v2

#MESSAGE ( "gtkmm include: \n ${GTKMM_INCLUDE_DIRS} \n " )
#MESSAGE ( "glademm include: \n ${GLADEMM_INCLUDE_DIRS} \n " )
#MESSAGE ( "poppler include: \n ${POPPLER_INCLUDE_DIRS} \n " )


#MESSAGE ( "gtkmm library: \n ${GTKMM_LIBRARY_DIRS} \n " )
#MESSAGE ( "glademm library: \n ${GLADEMM_LIBRARY_DIRS} \n " )
#MESSAGE ( "poppler library: \n ${POPPLER_LIBRARY_DIRS} \n " )


#MESSAGE ( "Lib output path: ${LIBRARY_OUTPUT_PATH} \n " )


# Make sure the compiler can find include files from our library.
include_directories (	${ALL_INCLUDE_DIRS} )

# Make sure the linker can find the library once it is built.
LINK_DIRECTORIES ( ${ALL_LINK_DIRS} )



# Add all source files in a variable
SET (	SRCS_EngineGTKMM
			EngineGTKMM.cpp
			Data/DataWindowGTKMM.cpp
			Data/DisplayFile.cpp
			Data/DisplayFilePDF.cpp
			Data/DataAssistantGTKMM.cpp
			Category/CategoryWindowGTKMM.cpp
			Category/CategoryGTKMM.cpp
			Category/CategoryTreeGTKMM.cpp
			Category/DialogFieldChooserGTKMM.cpp
			Category/Fields/FieldGTKMM.cpp
			Category/Fields/TextFieldGTKMM.cpp
			Category/Fields/CheckFieldGTKMM.cpp
			Category/Fields/SpinFieldGTKMM.cpp
			Category/Fields/ComboFieldGTKMM.cpp
			Category/Fields/FieldEditWidgetGTKMM.cpp
			Category/Fields/FieldSpinEditWidgetGTKMM.cpp
			Category/Fields/FieldComboEditWidgetGTKMM.cpp
			${CMAKE_BINARY_DIR}/src/Engine/Engine.cpp	
			${CMAKE_BINARY_DIR}/src/Engine/Configuration.cpp
			GeneralGTKMM/YesNoToggleButtonGTKMM.cpp
			Toolchain/ToolchainWindowGTKMM.cpp
			Toolchain/DialogOperationChooserGTKMM.cpp
			Toolchain/EditToolchainNodeGTKMM.cpp
			Toolchain/EditExecuteSystemCommandGTKMM.cpp
			Toolchain/EditTextFileStorageGTKMM.cpp
		)

		

# Create a libary named Field
ADD_LIBRARY ( EngineGTKMM ${SRCS_EngineGTKMM} ) 

