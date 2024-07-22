cmake_minimum_required(VERSION 3.0)

project(LOGS)

add_library(logs logs.cpp
    logs.hpp)

set_target_properties(logs PROPERTIES COMPILE_FLAGS "-Wall -O3")


install(FILES logs.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS logs DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
