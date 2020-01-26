#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

macro(add_doxygen_target)



  find_program(
    DOXYGEN
    NAMES doxygen
    DOC "Documentation system used for the dataFlowFramework."
    
  )

  
  if(DOXYGEN)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc CACHE STRING "Documentation directory.")
    configure_file(Doxyfile.config ${CMAKE_BINARY_DIR}/Doxyfile)

    add_custom_target(
      doxygen
      COMMAND
      doxygen ${CMAKE_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY
      ${CMAKE_BINARY_DIR}
    )
  else()
    message(STATUS "Doxygen not found! Target 'make doxygen' will not be available. "
                    "If you want to generate documentation please install doxygen.")
  endif()

endmacro()
