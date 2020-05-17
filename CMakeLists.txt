cmake_minimum_required(VERSION 3.14)
project(quiz)

set(CMAKE_CXX_STANDARD 17)

add_executable(quiz src/main.cpp src/App.cpp src/MainMenu.cpp)