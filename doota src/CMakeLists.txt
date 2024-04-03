cmake_minimum_required(VERSION 3.27)
project(abol)

set(CMAKE_CXX_STANDARD 14)

add_executable(abol
        finnal.cpp
        User.h
        User.cpp
        Assignment.cpp
        Assignment.h
        Admin.cpp
        Admin.h
        Teacher.cpp
        Teacher.h
        Student.cpp
        Student.h
        Class.cpp
        Class.h)
