cmake_minimum_required(VERSION 3.5)
project(CodeGenerator)

set(CMAKE_CXX_STANDARD 17)

# Add TinyXML-2 library
add_subdirectory(lib/tinyxml2-10.0.0)

# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${MY_SOURCES})
target_link_libraries(${PROJECT_NAME} tinyxml2)