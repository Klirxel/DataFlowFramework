#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

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

set(include_dir ${CMAKE_SOURCE_DIR}/include)

target_include_directories(
  dataflow
  INTERFACE
  $<BUILD_INTERFACE:${include_dir}>
)

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

install(
  DIRECTORY ${include_dir}/ 
  DESTINATION ${install_path_header}
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp"
  )

install(
  EXPORT dataflow
  DESTINATION ${install_path_cmake_config}
  )
