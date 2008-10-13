
# Add all source files in a variable
SET (	SRCS_Field
			Field.cpp
			TextField.cpp
			CheckField.cpp
			ComboField.cpp
			SpinField.cpp
		)
		
SET ( SRCS_Category
			Category.cpp
		)
		
SET ( SRCS_Exceptions
			FieldException.cpp
		)


# Create a libary named Field
ADD_LIBRARY (Field ${SRCS_Field})

# Create a libary named Category
ADD_LIBRARY ( Category ${SRCS_Category} )

# Create a libary named Exceptions
ADD_LIBRARY ( Exceptions ${SRCS_Exceptions} )

