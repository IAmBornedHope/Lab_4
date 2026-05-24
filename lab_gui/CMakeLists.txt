
add_library(lab4_gui STATIC lab.cpp main.cpp)

target_link_libraries(lab4_gui PUBLIC wx::core wx::base)

target_include_directories(lab4_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(lab4_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})