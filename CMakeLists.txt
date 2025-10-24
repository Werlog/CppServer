cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(MinecraftServer)

add_subdirectory(thirdparty/asio)

file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SERVER_SOURCES})

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE asio)