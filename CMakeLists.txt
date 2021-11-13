cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(register
        VERSION 1.0.0
        LANGUAGES CXX)

set(headers
include/${PROJECT_NAME}/register.hpp)

set(sources
src/register.cpp)

add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)
