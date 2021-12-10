cmake_minimum_required(VERSION 3.20)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp parserdata.cpp parserdata.h token.cpp token.h parser.cpp parser.h
        rwlib.h rwlib.cpp)
