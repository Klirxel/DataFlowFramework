add_library(
  df_base	
  dummy.cpp	
  ExecutorAsync.cpp
 )


target_include_directories(
  df_base
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include/base
  #for .hpp files.
  ${CMAKE_SOURCE_DIR}/src/base 
)


set_target_properties(
  df_base 
  PROPERTIES
  CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  CXX_STANDARD 17
) 
