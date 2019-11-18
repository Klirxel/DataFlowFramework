#Version developed on.
CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

PROJECT(DataFlowFramework)

################################################################################
#Versions information
################################################################################
set(DATA_FLOW_FRAMEWORK_MAJOR 0 CACHE STRING "major version" FORCE)
set(DATA_FLOW_FRAMEWORK_MINOR 1 CACHE STRING "minor version" FORCE)
set(DATA_FLOW_FRAMEWORK_VERSION ${DATA_FLOW_FRAMEWORK_MAJOR}.${DATA_FLOW_FRAMEWORK_MINOR} CACHE STRING "version" FORCE)

################################################################################
#Installation 
################################################################################
set(install_path_runtime "bin/dataFlowFramework-${DATA_FLOW_FRAMEWORK_VERSION}")
set(install_path_library "lib/dataFlowFramework-${DATA_FLOW_FRAMEWORK_VERSION}")
set(install_path_archive "lib/dataFlowFramework-${DATA_FLOW_FRAMEWORK_VERSION}")
set(install_path_public_header "include/dataFlowFramework-${DATA_FLOW_FRAMEWORK_VERSION}")
set(install_path_private_header "include/dataFlowFramework-${DATA_FLOW_FRAMEWORK_VERSION}")
set(install_path_cmake_config "lib/dataFlowFramework-${DATA_FLOW_FRAMEWORK_VERSION}/cmake")

################################################################################
#Packaging
################################################################################
include(CPack)

################################################################################
#Options and global variables
################################################################################
option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(RUN_CMAKE_TIDY_ON_BUILD "Run cmake tidy on build" ON)
option(ENABLE_CODE_COVERAGE "Enable code coverage analysis. [Recommend: CMAKE_BUILD_TYPE=Debug]" OFF) 

set(ADDITIONAL_COMPILE_OPTIONS "-Wall -Wpedantic -Wextra" CACHE STRING "Additional compile options." )
set(CLANG_TIDY_ADDITIONAL_OPTIONS "-fix" CACHE STRING "Clang tidy additional options. Base configuration see config-file .clang-tidy.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON ) 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(COMPILE_COMMANDS_JSON_INST_DIR ${CMAKE_SOURCE_DIR} CACHE STRING "Install dir of compile_commands.json.")
################################################################################
#Add additional compile options
################################################################################
string(REPLACE " " ";" ADDITIONAL_COMPILE_OPTIONS_LIST "${ADDITIONAL_COMPILE_OPTIONS}")
add_compile_options(${ADDITIONAL_COMPILE_OPTIONS_LIST})

################################################################################
#Add testing
################################################################################
if(BUILD_UNIT_TESTS)
  find_package(Boost COMPONENTS REQUIRED unit_test_framework)
  enable_testing()
endif()

################################################################################
#Add clang-tidy support
################################################################################
include(add_cmake_tidy_support) 

if(RUN_CMAKE_TIDY_ON_BUILD) 
  add_cmake_tidy_support()
endif()

################################################################################
#Add format target
################################################################################
include(add_format_target) 
set(dirs_to_format "include src")
add_format_target(${dirs_to_format}) 

################################################################################
#Add code coverage support 
################################################################################
include(add_code_coverage_support) 

if(ENABLE_CODE_COVERAGE)
  add_code_coverage_support()
endif()

################################################################################
#Add subdirectories
################################################################################
add_subdirectory(src)

if(BUILD_UNIT_TESTS)
  add_subdirectory(test)
endif()
