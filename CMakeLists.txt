cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(register
        VERSION 1.0.0
        LANGUAGES CXX)

include(cmake/StandardSettings.cmake)
include(cmake/Tools.cmake)

set(headers
    include/${PROJECT_NAME}/common/type_traits.hpp
    include/${PROJECT_NAME}/register.hpp
)

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

#set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "time -v")
#set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "time -v")

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
        add_subdirectory(tests)
endif()