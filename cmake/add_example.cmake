include(add_executable_with_dataflow_dependency)

function(add_example name)

  add_executable_with_dataflow_dependency(${name})

endfunction()
