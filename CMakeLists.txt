cmake_minimum_required(VERSION 3.14)
project(quiz)

set(CMAKE_CXX_STANDARD 14)

add_executable(quiz src/main.cpp src/Quiz.cpp src/MainMenu.cpp)