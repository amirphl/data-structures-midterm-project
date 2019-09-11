cmake_minimum_required(VERSION 3.7)
project(project1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Service.cpp Service.h Agency.cpp Agency.h Order.cpp Order.h MyStack.cpp MyStack.h TestCase.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
add_executable(project1 ${SOURCE_FILES})
