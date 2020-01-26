>          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
> Distributed under the Boost Software License, Version 1.0.
>    (See accompanying file LICENSE_1_0.txt or copy at
>          http://www.boost.org/LICENSE_1_0.txt)

#Building
  * mkdir <build_dir>
  * cd    <build_dir>
  * cmake <path_to_df_root_directory>
  * ccmake <path_to_df_root_directory> (optional for configuration) 
  * make [-j number of threads] 

#Documentation
  * goto df root dir
  * doxygen
  * cd ./html
  * <browser> index.html

#3rd party libraries used
  * https://www.boost.org/ 
    * Boost test for (/test) 
  * http://github.com/bilke/cmake-modules
    * for cmake/Coverage.cmake
    * BSD License

  
