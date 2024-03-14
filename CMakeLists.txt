cmake_minimum_required(VERSION 3.16)

project(codeGenerator VERSION 0.1.0 
                      DESCRIPTION "SAES Code generator"
                      LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.1\\mingw_64\\")
# Para poder incluir los logs
set ( ENV{SAES_PATH} "C:\\Users\\javib\\Documents\\saes\\Generadores\\lib\\log-saes")

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_executable(codeGenerator
    src/main.cpp
    # src/xmlparser.cpp
)

add_subdirectory(lib)

# Properties here
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 23 
    # COMPILE_FLAGS "-Wall -O3"
)

include_directories(
    lib/log-saes/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core tinyxml2 logs)
