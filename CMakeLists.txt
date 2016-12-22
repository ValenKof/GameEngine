cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(/opt/X11/include)
include_directories(include)
include_directories(lib)

add_subdirectory(lib/lodepng)

link_directories(/opt/X11/lib)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fno-omit-frame-pointer")

add_executable(main ${SOURCES})

target_link_libraries(main m)
target_link_libraries(main pthread)
target_link_libraries(main X11)
target_link_libraries(main lodepng)
