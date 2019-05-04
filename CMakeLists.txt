cmake_minimum_required(VERSION 3.12)
project(bigwork)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main
        build_tree.cpp
        build_tree.h
        CG_debug.cpp
        CG_debug.h
        evaluation.cpp
        evaluation.h
        main.cpp
        Node.cpp
        Node.h)
