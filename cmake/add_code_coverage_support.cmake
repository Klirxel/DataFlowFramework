#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

macro(add_code_coverage_support)
  
  include(CodeCoverage)
  include(ProcessorCount)

  ProcessorCount(PROCESSOR_COUNT)

  APPEND_COVERAGE_COMPILER_FLAGS()

  SETUP_TARGET_FOR_COVERAGE_LCOV(
    NAME code_coverage_analysis                 # New target name
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}      # Executable in PROJECT_BINARY_DIR
    #DEPENDENCIES testrunner                    # Dependencies to build first
 )

endmacro()
