cmake_minimum_required(VERSION 3.8)

project(03.homework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(guess_number guess_number.cpp high_score_table.cpp)
