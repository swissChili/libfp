cmake_minimum_required(VERSION 3.14)
project(libfp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main main.cc fp/fp.hh fp/math.hh fp/io.hh)
