cmake_minimum_required(VERSION 3.20)
project(techqu)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
MESSAGE("src files = " ${SRC})

add_executable(techqu main.cpp ${SRC})
