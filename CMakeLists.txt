cmake_minimum_required(VERSION 3.13)

project(Simple-Banking-System
    VERSION 1.0
    DESCRIPTION "This project is part of an object-oriented programming module of the Bachelor of Science in Electrical Engineering from the Federal University of Espírito Santo."
    LANGUAGES CXX)
    
include_directories(${CMAKE_SOURCE_DIR}/include) # choosing header files folder


# choosing cpp file folders
file(GLOB SRC_SOURCES src/*.cpp)
file(GLOB LIB_SOURCES lib/*.cpp)
add_executable(bank ${SRC_SOURCES} ${LIB_SOURCES})

set_target_properties(bank PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}) # defining the output file directory as the root TP folder


target_include_directories(bank PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(bank PRIVATE cxx_std_20) # selecting the compiler
