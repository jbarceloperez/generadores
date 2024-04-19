cmake_minimum_required(VERSION 3.5)

project(codeGenerator VERSION 0.1.0 
                      DESCRIPTION "SAES Code generator"
                      LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.1\\mingw_64\\")
# Para poder incluir los logs
set ( ENV{SAES_PATH} "C:\\Users\\javib\\Documents\\saes\\Generadores\\lib\\log-saes")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(codeGenerator
    src/main.cpp

    src/gui/GeneratorPanelImpl.cpp
    src/gui/GeneratorPanelImpl.h
    src/gui/MainPanel.h
    src/gui/MainPanel.cpp
    
    # src/controller.cpp src/controller.h
    # src/model/generador.cpp src/model/generador.h src/model/panel.cpp src/model/panel.h src/model/panelbuilder.cpp src/model/panelbuilder.h
    # src/xml/xmlparser.cpp src/xml/xmlparser.h
)

add_subdirectory(lib)

# Properties here
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 23
)

include_directories(
    lib/log-saes/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets tinyxml2 logs)
