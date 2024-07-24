#!/bin/bash

# Nombre de la imagen y el contenedor
IMAGE_NAME="qtcreator6-6"
CONTAINER_NAME="qt_container"

# Función para mostrar el uso del script
function show_usage() {
    echo "Uso: $0 [build|run|qtcreator]"
    echo "  build      Construir la imagen Docker"
    echo "  run        Ejecutar el contenedor Docker"
    echo "  qtcreator  Iniciar el contenedor y ejecutar Qt Creator"
}

# Función para construir la imagen Docker
function build_image() {
    echo "Construyendo la imagen Docker..."
    docker build -t $IMAGE_NAME .
}

# Función para ejecutar el contenedor Docker
function run_container() {
    echo "Ejecutando el contenedor Docker..."
    export DISPLAY=$DISPLAY
    docker run -it --name $CONTAINER_NAME --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ./Generadores:/workspace/Generadores -v ./out:/workspace/out $IMAGE_NAME
}

# Función para iniciar el contenedor y ejecutar Qt Creator
function run_qtcreator() {
    echo "Iniciando el contenedor y ejecutando Qt Creator..."
    export DISPLAY=$DISPLAY
    docker run -it --name $CONTAINER_NAME --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ./Generadores:/workspace/Generadores -v ./out:/workspace/out $IMAGE_NAME qtcreator
}

# Verificar si se proporcionaron argumentos
if [ $# -eq 0 ]; then
    show_usage
    exit 1
fi

# Procesar los argumentos
while [[ $# -gt 0 ]]; do
    case "$1" in
        build)
            build_image
            shift
            ;;
        run)
            run_container
            shift
            ;;
        qtcreator)
            run_qtcreator
            shift
            ;;
        *)
            show_usage
            exit 1
            ;;
    esac
done
