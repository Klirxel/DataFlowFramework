include(add_executable_with_dataflow_dependency)
include(add_example_test)

function(add_example name)

  add_executable_with_dataflow_dependency(${name})
  add_example_test(${name})

endfunction()
