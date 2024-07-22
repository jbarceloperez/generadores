cmake_minimum_required(VERSION 3.0)

project(LOGS)

IF ( UNIX )
        SET ( BUILD_SHARED_LIBS ON )
        if("$ENV{SAES_PATH}" STREQUAL "")
                message(FATAL_ERROR "SAES_PATH environment variable not defined!")
        else()
                set(CMAKE_INSTALL_PREFIX $ENV{SAES_PATH})
        endif()
ENDIF ( )
IF ( WIN32 )
   SET ( BUILD_SHARED_LIBS ON )
   # Verificar si la variable de entorno SAES_PATH está definida
   if("$ENV{SAES_PATH}" STREQUAL "")
       message(FATAL_ERROR "SAES_PATH environment variable not defined! Puede establecerla mediante: set SAES_PATH=C:\\Ruta\\Al\\Directorio")
   else()
       set(CMAKE_INSTALL_PREFIX $ENV{SAES_PATH})
   endif()
ENDIF ( )

add_subdirectory(src)
add_subdirectory(example)
