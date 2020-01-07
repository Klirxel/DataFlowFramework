macro(add_deploy_compile_time_json_target) 

  add_custom_target(
    deploy_compile_time_json
    cmake -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}
  ) 

endmacro()
