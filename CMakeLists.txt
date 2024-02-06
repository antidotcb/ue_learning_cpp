cmake_minimum_required(VERSION 3.27)
project(ue_learning_cpp)

add_subdirectory(lib)

add_executable(ua_learning_cpp main.cpp)

target_link_libraries(ua_learning_cpp game_lib)
