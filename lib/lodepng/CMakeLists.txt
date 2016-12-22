cmake_minimum_required(VERSION 3.5)

set(SOURCES "lodepng.cpp")

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fno-omit-frame-pointer")

add_library(lodepng STATIC ${SOURCES})
