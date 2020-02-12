#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

include(require_program) 

function (add_example_test_target target)

  require_program(bash)
  require_program(diff)

  set(test_name test_example_${target})
  set(path_example_test_driver ${CMAKE_SOURCE_DIR}/scripts/example_test_driver.sh)
  set(path_test_executable $<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_NAME:${target}>)
  set(path_cout_file $<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_NAME:${target}>_cout.txt)
  set(path_reference_cout_file "${CMAKE_CURRENT_SOURCE_DIR}/referenceOutputFiles/$<TARGET_FILE_NAME:${target}>_cout.txt")

  message(STATUS ${path_output_file})
  
  add_test(
    NAME ${test_name}
    COMMAND
    ${path_example_test_driver}
    ${path_test_executable}
    ${path_cout_file}
    ${path_reference_cout_file}
  )

endfunction()
