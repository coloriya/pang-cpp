cmake_minimum_required(VERSION 3.10)

project(pang)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB pang_srcs src/*.cpp)
add_executable(pang ${pang_srcs})
target_link_libraries(pang png)


