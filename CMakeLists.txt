cmake_minimum_required(VERSION 3.27)
project(ue_learning_cpp)

set(CMAKE_CXX_STANDARD 20)

add_library(game_lib STATIC
        lib/character.cpp
        lib/character.h
        lib/constants.h
        lib/input.cpp
        lib/input.h
        lib/selector.cpp
        lib/selector.h
        lib/stats.cpp
        lib/stats.h
        lib/types.cpp
        lib/utils.cpp
        lib/utils.h
)

add_executable(ua_learning_cpp main.cpp)

target_link_libraries(ua_learning_cpp game_lib)
