function(add_format_target)

 add_custom_target (
       	format
	COMMAND ${CMAKE_SOURCE_DIR}/cmake/format.sh ${ARGV} 
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} 
) 

endfunction()
