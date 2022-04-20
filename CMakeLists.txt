cmake_minimum_required(VERSION 3.20)
project(iFlat)

set(CMAKE_CXX_STANDARD 17)

add_executable(iFlat
        main.cpp
        utility/Vector.h
)

include_directories(utility, ../Arx)

