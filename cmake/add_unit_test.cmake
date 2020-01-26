#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

find_package(Boost REQUIRED unit_test_framework) 

function (add_unit_test name)

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

  add_test(${name} ${name})

endfunction()
