cmake_minimum_required(VERSION 3.20)
project(lesson24)

set(CMAKE_CXX_STANDARD 20)

add_executable(lesson24 main.cpp parserdata.h token.cpp token.h parser.cpp parser.h
        rwlib.h rwlib.cpp)
