cmake_minimum_required(VERSION 3.10)
project(MyProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(json_obj json_obj.h json_obj.cpp json_for_string.cpp check_struct.cpp input_struct.cpp)

link_libraries(json_obj vld)

include_directories("C:/Program Files (x86)/Visual Leak Detector/include")
link_directories("C:/Program Files (x86)/Visual Leak Detector/lib/Win64")

add_executable(main main.cpp)




