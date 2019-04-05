#Version developed on.
CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

PROJECT(DataFlowFramework)

################################################################################
#Options
################################################################################
option(RUN_CMAKE_TIDY_ON_BUILD "Run cmake tidy on build" ON)
option(BUILD_UNIT_TESTS "Build unit tests" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON ) 
set(CLANG_TIDY_ADDITIONAL_OPTIONS "-fix" CACHE STRING "Clang tidy additional options. Base configuration see config-file .clang-tidy.")
set(ADDITIONAL_COMPILE_OPTIONS "-Wall -Wpedantic -Wextra" CACHE STRING "Additional compile options." )

################################################################################
#Packages
################################################################################
if(BUILD_UNIT_TESTS)
  find_package(Boost COMPONENTS REQUIRED unit_test_framework)
endif()

#set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
################################################################################
#Includes
################################################################################
include(add_cmake_tidy_support) 

################################################################################
#Setup environment
################################################################################
if(RUN_CMAKE_TIDY_ON_BUILD) 
  add_cmake_tidy_support()
endif()

string(REPLACE " " ";" ADDITIONAL_COMPILE_OPTIONS_LIST "${ADDITIONAL_COMPILE_OPTIONS}")
add_compile_options(${ADDITIONAL_COMPILE_OPTIONS_LIST})

if(BUILD_UNIT_TESTS)
  enable_testing()
endif()
################################################################################
#Subdirectories
################################################################################
add_subdirectory(src/base)

if(BUILD_UNIT_TESTS)
  add_subdirectory(test)
endif()

################################################################################
#Target main
################################################################################
add_executable(
  main
  src/main.cpp
)

target_link_libraries(
  main
  df_base  
)

set_target_properties(
  main 
  PROPERTIES
  CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  CXX_STANDARD 17
)

################################################################################
#Target copy_compile_commands.json 
################################################################################
add_custom_command(
  TARGET main 
  POST_BUILD
  COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}   
)


