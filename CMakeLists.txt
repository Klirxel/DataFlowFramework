#Version developed on.
CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

PROJECT(DataFlowFramework)


################################################################################
#Options
################################################################################
option(RUN_CMAKE_TIDY_ON_BUILD "Run cmake tidy on build" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON ) 
set(CLANG_TIDY_ADDITIONAL_OPTIONS "-fix" CACHE STRING "Clang tidy additional options. Base configuration see config-file .clang-tidy.")
set(ADDITIONAL_COMPILE_OPTIONS "-Wall -Wpedantic -Wextra" CACHE STRING "Additional compile options." )



################################################################################
#Setup environment
################################################################################
include(add_cmake_tidy_support)
if(RUN_CMAKE_TIDY_ON_BUILD) 
  add_cmake_tidy_support()
endif()

string(REPLACE " " ";" ADDITIONAL_COMPILE_OPTIONS_LIST "${ADDITIONAL_COMPILE_OPTIONS}")
add_compile_options(${ADDITIONAL_COMPILE_OPTIONS_LIST})


enable_testing()
################################################################################
#Target
################################################################################
add_executable(
  main
  src/main.cpp
)

target_include_directories(
  main
  PRIVATE
  include
  src
)

set_target_properties(
  main 
  PROPERTIES
  CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  CXX_STANDARD 17
)

add_custom_command(
	TARGET main 
	POST_BUILD
        COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}   
)


