#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

function(add_format_target)

 add_custom_target (
       	format
	COMMAND ${CMAKE_SOURCE_DIR}/cmake/format.sh ${ARGV} 
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} 
) 

endfunction()
