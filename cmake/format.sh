#!/bin/bash

dirs_to_format=$@

echo "Dirs to format: ${dirs_to_format}"

files_to_format=$(find $dirs_to_format -name '*.cpp' -or -name '*.h' -or -name '*.hpp')

clang-format -i -verbose ${files_to_format} 
