cmake_minimum_required(VERSION 3.27)
project(ue_learning_cpp)

add_subdirectory(lib)

add_executable(ua_learning_cpp src/main.cpp
        src/lesson_15.cpp
        src/lesson_15.h
        src/lesson_16.cpp
        src/lesson_16.h
)

target_link_libraries(ua_learning_cpp game_lib)
