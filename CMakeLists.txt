cmake_minimum_required(VERSION 3.15)
project(Lab_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/Lab_3)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Lab3_lib)