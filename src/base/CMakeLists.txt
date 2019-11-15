find_package(Threads REQUIRED)

set(header_dirs
  ${CMAKE_SOURCE_DIR}/include/base/blocks
  ${CMAKE_SOURCE_DIR}/include/base/channels
  ${CMAKE_SOURCE_DIR}/include/base/executors
  ${CMAKE_SOURCE_DIR}/include/base/tools
  #for .hpp files.
  ${CMAKE_SOURCE_DIR}/src/base 
)

add_library(
  df_base
  INTERFACE  
) 

target_include_directories(
  df_base
  INTERFACE
  ${header_dirs}
)

target_link_libraries(
  df_base
  INTERFACE
  Threads::Threads	
)
