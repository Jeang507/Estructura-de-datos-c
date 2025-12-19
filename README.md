# Proyecto Final – Programación II  
## Sistema de Gestión de Recetas en Lenguaje C

Este proyecto corresponde al **trabajo final de la asignatura Programación II** y consiste en el desarrollo de un **Sistema de Gestión de Recetas** implementado en lenguaje C, enfocado en la aplicación práctica de **estructuras de datos dinámicas** y programación modular.

El sistema permite administrar un conjunto de recetas culinarias, cada una compuesta por múltiples ingredientes, utilizando **estructuras (`struct`) y listas doblemente enlazadas** para el manejo eficiente de la información en memoria.

## Objetivo del Proyecto

Aplicar los conceptos fundamentales de Programación II mediante el uso correcto de **estructuras de datos**, específicamente:

- Definición y uso de estructuras (`struct`)
- Implementación de una **lista doblemente enlazada**
- Manejo de memoria dinámica con `malloc` y `free`
- Modularización del programa en archivos `.c` y `.h`
- Persistencia de datos mediante archivos de texto
- Control y validación de entradas del usuario

## Descripción del Sistema

El sistema funciona a través de un **menú interactivo en consola** que permite al usuario gestionar recetas de forma dinámica.  
Cada receta se almacena en memoria como un **nodo de una lista doblemente enlazada**, lo que facilita:

- Inserción eficiente de nuevas recetas
- Eliminación segura de registros
- Recorrido ordenado de los datos
- Gestión dinámica sin límites fijos de memoria

Cada receta está compuesta por:
- Un nombre único
- Un conjunto de ingredientes
- Cantidad y unidad de medida por ingrediente

## Estructuras de Datos Implementadas

### 1. Estructuras (`struct`)
- **Ingrediente**: almacena el nombre, cantidad y unidad de medida.
- **Receta**: contiene el nombre de la receta y un arreglo de ingredientes.
- **NodoReceta**: estructura que enlaza cada receta dentro de la lista.

### 2. Lista Doblemente Enlazada
Las recetas se almacenan en una **lista doblemente enlazada**, donde cada nodo mantiene referencias al nodo anterior y al siguiente.  
Esta estructura permite un manejo eficiente de la memoria y facilita las operaciones de búsqueda, inserción y eliminación.

## Persistencia de Datos

El sistema incorpora **lectura y escritura en archivos de texto**, permitiendo guardar las recetas registradas y cargarlas automáticamente al iniciar el programa.  
De esta manera, se garantiza la conservación de la información entre ejecuciones.

## Estructura del Proyecto

Estructura del proyecto:

main.c  
Archivo principal del programa. Contiene la función `main` y el menú interactivo desde el cual se controlan todas las operaciones del sistema.

recetas.c  
Implementa la lógica del sistema de gestión de recetas, incluyendo la manipulación de la **lista doblemente enlazada**, la creación, búsqueda, modificación y eliminación de recetas, así como la lectura y escritura en archivos.

recetas.h  
Define las **estructuras de datos** utilizadas en el proyecto (ingrediente, receta y nodo de la lista) y declara los prototipos de las funciones del módulo de recetas.

util.c  
Contiene funciones auxiliares para el manejo de pantalla, limpieza del buffer de entrada, validaciones y selección de unidades de medida.

util.h  
Declara los prototipos de las funciones utilitarias utilizadas en diferentes módulos del sistema.

run.sh  
Script de ejecución que compila los archivos fuente y ejecuta el programa desde la terminal.

recetas.txt  
Archivo de texto utilizado para la **persistencia de datos**, donde se almacenan las recetas registradas por el usuario.

## Compilación y Ejecución

### Sistemas Linux:

```bash
chmod +x run.sh
./run.sh
```
### Sistemas Windows:

run.bat


Autor

Jean Guillén