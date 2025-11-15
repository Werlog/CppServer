cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

option(PRODUCTION_BUILD "Make this a production build" OFF)

project(MinecraftServer)

add_subdirectory(thirdparty/asio)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/uuid_v4)

file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

if (PRODUCTION_BUILD)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SERVER_SOURCES})

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE asio glm uuid_v4)