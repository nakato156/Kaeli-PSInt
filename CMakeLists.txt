cmake_minimum_required(VERSION 3.13)

project(Kaeli_PSint VERSION 2.0)

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
