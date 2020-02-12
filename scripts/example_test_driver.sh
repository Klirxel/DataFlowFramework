#!/bin/bash

path_test_executable=$1
path_output_file=$2
path_reference_output_file=$3

$path_test_executable > ${path_output_file}

(( $? != 0 )) && exit 1
diff $path_output_file $path_reference_output_file
exit $?

