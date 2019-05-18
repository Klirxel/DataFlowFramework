find_package(Boost REQUIRED unit_test_framework) 

function (add_unit_test name)

  add_executable(
    ${name}  
    ${name}.cpp
  )

  target_link_libraries(
    ${name}	
    df_base
    ${Boost_LIBRARIES} 
  )

  set_target_properties(
    ${name} 
    PROPERTIES
    CXX_STANDARD 17
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  )

  add_test(${name} ${name})

endfunction()
