cmake_minimum_required(VERSION 3.27)

project(game_lib)

add_library(game_lib STATIC
        character.cpp
        character.h
        constants.h
        input.cpp
        input.h
        selector.cpp
        selector.h
        stats.cpp
        stats.h
        types.cpp
        utils.cpp
        utils.h
)

target_compile_features(game_lib PUBLIC cxx_std_20)

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
