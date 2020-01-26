#!/bin/bash

#          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

dirs_to_format=$@

echo "Dirs to format: ${dirs_to_format}"

files_to_format=$(find $dirs_to_format -name '*.cpp' -or -name '*.h' -or -name '*.hpp')

clang-format -i -verbose ${files_to_format} 
