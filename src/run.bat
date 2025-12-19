@echo off
set OUTPUT=recetas.exe

echo Compilando el proyecto...

gcc main.c recetas.c util.c -Wall -Wextra -o %OUTPUT%

if errorlevel 1 (
    echo Error en la compilacion.
    exit /b 1
)

echo Ejecutando el programa...
%OUTPUT%
