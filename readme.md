## Description
  * This framework helps you building programs using  
    dataflow programming 
    (see https://en.wikipedia.org/wiki/Dataflow_programming ).
  * Programs are a composite of functional components called blocks, which are
    connected via channels (similar to description of electric circuits).
  * More information please build documentation with doxygen (see Building).

## Objective
  * Proof of concept of programming dataflow graphs with C++

## Status
  * Basic features implemented
  * Not tested by 3rd party users
  * Only tested on Linux yet
  * No performance optimization yet
  
## Requirements for using this library 
  * Experience in the C++ language
  * Linux build environment
  * Boost library
  * Doxygen library (optional)
  * CMake Version >= 3.13 
  * C++ 17 compatible compiler 

## Building
  * It's a cmake project
  * Open a Linux-Terminal
  * Enter root directory of the dataflow framework (this dir :-))
  * Create a build dir
  * Enter the build dir
  * Execute: cmake <path_project_root_dir (this dir :-)>
  * Optional you can do configuration with: ccmake .
  * Build with make [-j number of threads]
  * Optional build documentation with: make doxygen
    (you can find the documentation under ./html/index.html)

## Documenation
  * Doxygen documentation
  * Unit tests (see test/)
  * Source code

## 3rd party libraries used
  * https://www.boost.org/ 
    * Boost test for (/test) 
  * http://github.com/bilke/cmake-modules
    * for cmake/Coverage.cmake

## Licensing
  * Boost Software License Version 1.0 

## Who can contribute to this library
  * Everybody who is interested 
