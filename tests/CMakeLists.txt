cmake_minimum_required(VERSION 3.15)
project(lab4_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)


add_executable(lab4_test
               main.cpp 
               test_Cardinal.cpp
               test_ContGenerator.cpp
               test_RecGenerator.cpp
               test_MapGenerator.cpp
               test_FilterGenerator.cpp
               test_ConcatGenerator.cpp
               test_LazySequence.cpp
               test_Streams.cpp
               test_StreamSorter.cpp)
               
target_link_libraries(lab4_test 
                      gtest_main)

target_include_directories(lab4_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
