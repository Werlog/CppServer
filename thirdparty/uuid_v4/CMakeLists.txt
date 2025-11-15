cmake_minimum_required(VERSION 3.1)

project(uuid_v4)

add_library(uuid_v4 INTERFACE)

target_include_directories(uuid_v4 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")