function (add_executable_with_dataflow_dependency name)

  add_executable(
    ${name}  
    ${name}.cpp
  )

  target_link_libraries(
    ${name}	
    dataflow
    ${Boost_LIBRARIES} 
  )

  set_target_properties(
    ${name} 
    PROPERTIES
    CXX_STANDARD 17
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  )

endfunction()
