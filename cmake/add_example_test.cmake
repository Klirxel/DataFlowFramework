#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

include(add_example_test_target)


function (add_example_test target)

  option(EXAMPLE_TESTING
    "Validate examples on test run. Testing time can be significantly prologned." OFF)

  if(EXAMPLE_TESTING)
    add_example_test_target(${target})
  endif()

endfunction()

