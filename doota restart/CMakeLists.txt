cmake_minimum_required(VERSION 3.28)
project(dooootaaaa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dooootaaaa
        Administrator.cpp
        Administrator.h
        Course.cpp
        Course.h
        main.cpp
        Mark.cpp
        Mark.h
        Professor.cpp
        Professor.h
        Student.cpp
        Student.h
        Tab.cpp
        Tab.h
        UniversityMember.cpp
        UniversityMember.h
        Assignment.cpp)
