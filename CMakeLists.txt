cmake_minimum_required(VERSION 3.5)

project(codeGenerator VERSION 0.1.0 
                      DESCRIPTION "SAES Code generator"
                      LANGUAGES CXX)
                      set(CMAKE_AUTOUIC ON)
                      set(CMAKE_AUTOMOC ON)
                      set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.1\\mingw_64\\")
# Para poder incluir los logs
# set ( ENV{SAES_PATH} "C:\\Users\\javib\\Documents\\saes\\Generadores\\lib\\log-saes")
set ( ENV{SAES_PATH} "lib/log-saes")
set(CMAKE_PREFIX_PATH "/home/javi/Qt/6.7.0/gcc_64/lib/cmake")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()
set(PROJECT_SOURCES
        src/main.cpp
        src/controller.cpp
        src/controller.h
        src/gui/GeneratorPanelImpl.cpp
        src/gui/GeneratorPanelImpl.h
        src/gui/GeneratorPanel.ui

        src/model/generador.cpp src/model/panel.cpp src/model/panelcollection.cpp src/model/button.cpp
        src/model/generador.h src/model/panel.h src/model/panelcollection.h src/model/button.h
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
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets logs)

# Properties here
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 23
    MACOSX_BUNDLE TRUE
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
