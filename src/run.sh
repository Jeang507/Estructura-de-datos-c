#!/bin/bash

OUTPUT=recetas

echo "Compilando el proyecto..."

gcc main.c recetas.c util.c -Wall -Wextra -o $OUTPUT

if [ $? -ne 0 ]; then
    echo "Error en la compilación."
    exit 1
fi

echo "Ejecutando el programa..."
./$OUTPUT
