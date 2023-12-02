cmake_minimum_required(VERSION 3.15)

project(aoc-2013)

add_library(
    ${PROJECT_NAME} INTERFACE
)

target_include_directories(
    ${PROJECT_NAME} INTERFACE
)

add_subdirectory(day_1)