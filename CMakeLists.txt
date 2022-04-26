cmake_minimum_required(VERSION 3.20)
project(iFlat)

set(CMAKE_CXX_STANDARD 17)

add_executable(iFlat
        main.cpp
        code/utility/Vector.h
        code/utility/ODE_d.h
        code/solver/tracing_d.h code/solver/tracing_d.cpp code/solver/Ray.cpp code/solver/Ray.h code/utility/Solution.h code/utility/ODE.h code/solver/tracing.h code/solver/tracing.cpp code/solver/RaySolver.h code/solver/RaySolver.cpp)

include_directories(code/utility, ../iFlat)

