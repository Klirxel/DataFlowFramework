function (add_unit_test name)

  add_executable(
    ${name}  
    ${name}.cpp
  )

  target_link_libraries(
    ${name}	
    df_base
  )

  set_target_properties(
    ${name} 
    PROPERTIES
    CXX_STANDARD 17
  )

  add_test(${name} ${name})

endfunction()
