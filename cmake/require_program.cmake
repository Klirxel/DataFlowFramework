#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

function(require_program program)

  find_program(
    REQUIRED_PROGRAM_${program}
    ${program}
  ) 

 
  if(NOT REQUIRED_PROGRAM_${program})
    message(FATAL_ERROR "Example testing not possible. Required program ${program} not found.")
  endif()

endfunction()
