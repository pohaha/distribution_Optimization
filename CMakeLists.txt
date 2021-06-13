cmake_minimum_required(VERSION 3.19.7)

project(Try_Cmake)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Distribution)

target_link_directories(${PROJECT_NAME} PRIVATE Distribution/)

target_link_libraries(${PROJECT_NAME} distribution)