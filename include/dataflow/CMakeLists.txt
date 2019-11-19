################################################################################
#External requirements 
################################################################################
find_package(Threads REQUIRED)

################################################################################
#Add library 
################################################################################
add_library(
  dataflow
  INTERFACE  
) 

set(header_paths
  ${CMAKE_SOURCE_DIR}/include/dataflow/blocks
  ${CMAKE_SOURCE_DIR}/include/dataflow/channels
  ${CMAKE_SOURCE_DIR}/include/dataflow/executors
  ${CMAKE_SOURCE_DIR}/include/dataflow/tools
)

foreach(header_path ${header_paths})
  target_include_directories(
  dataflow
  INTERFACE
  $<BUILD_INTERFACE:${header_path}>
  )
endforeach()

target_link_libraries(
  dataflow
  INTERFACE
  Threads::Threads	
)

################################################################################
#Install library 
################################################################################
install(
  TARGETS dataflow 
  EXPORT  dataflow
  ARCHIVE  DESTINATION ${install_path_archive}
  LIBRARY  DESTINATION ${install_path_library}
  RUNTIME  DESTINATION ${install_path_runtime}
  INCLUDES DESTINATION ${install_path_header} 
  )

list(
  TRANSFORM header_paths
  APPEND "/"
  )

install(
  DIRECTORY  ${header_paths}
  DESTINATION ${install_path_header}
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp"
  )

install(
  EXPORT dataflow
  DESTINATION ${install_path_cmake_config}
  )
