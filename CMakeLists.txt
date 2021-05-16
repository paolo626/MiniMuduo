cmake_minimum_required(VERSION 2.6)
project(mymuduo)


# set .so  .a   dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# set debug and c++11   
set(CMAKE_CXX_FLAGS " ${CMAKE_XX_FLAGS} -g -std=c++11")

# define all cpp file to compile 
aux_source_directory(. SRC_LIST)

#  generate  mymuduo.so
add_library(mymuduo SHARED ${SRC_LIST})

