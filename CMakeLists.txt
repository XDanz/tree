cmake_minimum_required(VERSION 3.3)
project(tree)

find_package(Threads REQUIRED)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libtree)
