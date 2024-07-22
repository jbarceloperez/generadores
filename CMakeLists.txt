cmake_minimum_required(VERSION 3.15)

project(codeGenerator VERSION 0.1.0 
                      DESCRIPTION "SAES Code generator"
                      LANGUAGES CXX)
                      
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Para poder incluir los logs
set ( ENV{SAES_PATH} "lib/log-saes")

set(CMAKE_PREFIX_PATH "/home/javi/Qt/6.7.0/gcc_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()
set(PROJECT_SOURCES
        src/main.cpp
        src/controller/controller.cpp
        src/controller/controller.h
        src/controller/guicontroller.cpp
        src/controller/guicontroller.h
        src/gui/GeneratorPanelImpl.cpp
        src/gui/GeneratorPanelImpl.h
        src/gui/GeneratorPanel.ui
        src/gui/HeaderConfigPanel.ui
        src/gui/HeaderConfigPanel.cpp
        src/gui/HeaderConfigPanel.h
        src/log/logger.h src/log/logger.cpp

        src/model/generador.cpp src/model/gpanel.cpp src/model/panelcollection.cpp src/model/gbutton.cpp src/model/saesheader.cpp
        src/model/generador.h src/model/gpanel.h src/model/panelcollection.h src/model/gbutton.h src/model/saesheader.h
        src/xml/xmlparser.cpp src/xml/xmlparser.h
        src/xml/xmlfile.cpp src/xml/xmlfile.h
        src/xml/xmlattribute.cpp src/xml/xmlattribute.h
        src/xml/xmlelement.cpp src/xml/xmlelement.h
        src/xml/xmlexception.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets logs)

# Properties here
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 23
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

include_directories(
    lib/log-saes/src
)

add_subdirectory(lib)

#include(FetchContent)
#FetchContent_Declare(
#  googletest
#  URL https://github.com/google/googletest/archive/release-1.10.0.zip
#)
#FetchContent_MakeAvailable(googletest)

## Definir el ejecutable de tus tests
#enable_testing()
#add_executable(xml_tests src/xml/xmltests.cpp)
#target_link_libraries(xml_tests PRIVATE Qt6::Widgets gtest_main)
#target_compile_options(xml_tests PRIVATE "-Wall" "-Wextra")

## Incluir Google Test en el testing
#include(GoogleTest)
#gtest_discover_tests(xml_tests)
