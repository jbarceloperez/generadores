#!/bin/bash

# Exportar la variable DISPLAY para WSLg
export DISPLAY=$DISPLAY

# Ejecutar el comando pasado como argumento
exec "$@"