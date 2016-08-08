cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

include_directories(/opt/X11/include)
include_directories(src)

link_directories(/opt/X11/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -march=native -Wall -Werror")

add_executable(main ${SOURCES})

target_link_libraries(main m)
target_link_libraries(main pthread)
target_link_libraries(main X11)
