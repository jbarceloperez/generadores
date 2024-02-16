cmake_minimum_required(VERSION 3.16)
project(codeGenerator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.1\\mingw_64\\")

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_executable(codeGenerator
    src/main.cpp
)

# Add TinyXML-2 library
add_subdirectory(lib/tinyxml2-10.0.0)

# # Define MY_SOURCES to be a list of all the source files for my project
# file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# add_executable(${PROJECT_NAME} ${MY_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core tinyxml2)
