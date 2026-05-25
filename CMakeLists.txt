cmake_minimum_required(VERSION 3.15)
project(Lab_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/Lab_3)

add_subdirectory(generators)
add_subdirectory(lazy_sequence)
add_subdirectory(streams)
add_subdirectory(stream_sort)
add_subdirectory(lab_gui)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp resource.rc)

target_link_libraries(${PROJECT_NAME} PRIVATE Lab3_lib
                                            lazy_sequence
                                            streams
                                            stream_sort
                                            lab4_gui)