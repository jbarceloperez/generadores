@echo off
REM Comprueba si hay un argumento
if "%1"=="" (
    echo Error: No se ha proporcionado ningun argumento.
    echo Uso: script.bat [build | run | qtcreator]
    exit /b 1
)

REM Comprueba el argumento y ejecuta el comando correspondiente
if "%1"=="build" (
    echo Construyendo la imagen Docker...
    docker build -t qtcreator6-6 .
) else if "%1"=="run" (
    echo Ejecutando el contenedor Docker...
    set DISPLAY=$DISPLAY
    docker run -it --name qt_container --rm -e DISPLAY=host.docker.internal:0.0 -v /tmp/.X11-unix:/tmp/.X11-unix -v %cd%\Generadores:/workspace/Generadores qtcreator6-6
) else if "%1"=="qtcreator" (
    echo Iniciando el contenedor y ejecutando Qt Creator...
    set DISPLAY=%DISPLAY%
    docker run -it --name qt_container --rm -e DISPLAY=host.docker.internal:0.0 -v /tmp/.X11-unix:/tmp/.X11-unix -v %cd%\Generadores:/workspace/Generadores qtcreator6-6 qtcreator
) else (
    echo Uso: %0 [build | run | qtcreator]
    echo   build      Construir la imagen Docker
    echo   run        Ejecutar el contenedor Docker
    echo   qtcreator  Iniciar el contenedor y ejecutar Qt Creator
    exit /b 1
)

REM Fin del script
exit /b 0