################################################################################
#External requirements 
################################################################################
find_package(Threads REQUIRED)

################################################################################
#Add library 
################################################################################
add_library(
  df_base
  INTERFACE  
) 

set(headers_path_public
  ${CMAKE_SOURCE_DIR}/include/base/blocks
  ${CMAKE_SOURCE_DIR}/include/base/channels
  ${CMAKE_SOURCE_DIR}/include/base/executors
  ${CMAKE_SOURCE_DIR}/include/base/tools
)

set(headers_path_private
  ${CMAKE_SOURCE_DIR}/src/base 
)

foreach(header_path ${headers_path_public} ${headers_path_private})
  target_include_directories(
  df_base
  INTERFACE
  $<BUILD_INTERFACE:${header_path}>
  )
endforeach()

target_link_libraries(
  df_base
  INTERFACE
  Threads::Threads	
)

################################################################################
#Install library 
################################################################################
install(
  TARGETS df_base
  EXPORT  dataFlowFramework
  ARCHIVE  DESTINATION ${install_path_archive}
  LIBRARY  DESTINATION ${install_path_library}
  RUNTIME  DESTINATION ${install_path_runtime}
  INCLUDES DESTINATION ${install_path_public_header} 
  INCLUDES DESTINATION ${install_path_private_header} 
  )

list(
  TRANSFORM headers_path_public
  APPEND "/"
  )

install(
  DIRECTORY  ${headers_path_public}
  DESTINATION ${install_path_public_header}
  FILES_MATCHING
  PATTERN "*.h"
  )

list(
  TRANSFORM headers_path_private
  APPEND "/"
  )

install(
  DIRECTORY ${headers_path_private}
  DESTINATION ${install_path_private_header}
  FILES_MATCHING
  PATTERN "*.hpp"
  )

install(
  EXPORT dataFlowFramework
  DESTINATION ${install_path_cmake_config}
  )
