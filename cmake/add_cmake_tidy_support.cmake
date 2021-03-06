#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

macro(add_cmake_tidy_support) 
	
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
  )

  if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
  else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY ${CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR} ${CLANG_TIDY_ADDITIONAL_OPTIONS})
    message(STATUS "clang-tidy additional options: ${CLANG_TIDY_ADDITIONAL_OPTIONS}")
  endif()

endmacro()
