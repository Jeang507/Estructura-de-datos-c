#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "util.h"
#include "recetas.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarUnidades() {
    printf("Seleccione unidad:\n");
    printf("1. Gramos (g)\n");
    printf("2. Kilogramos (kg)\n");
    printf("3. Litros (lt)\n");
    printf("4. Unidades (u)\n");
}

const char* unidadPorOpcion(int op) {
    switch (op) {
        case 1: return "g";
        case 2: return "kg";
        case 3: return "lt";
        case 4: return "u";
        default: return "";
    }
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int contarRecetas() {
    int contador = 0;
    NodoReceta* actual = inicio;
    while (actual != NULL) {
        contador++;
        actual = actual->sig;
    }
    return contador;
}

int existeReceta(const char* nombre) {
    NodoReceta* actual = inicio;
    while (actual != NULL) {
        if (strcasecmp(actual->receta.nombre, nombre) == 0) {
            return 1;
        }
        actual = actual->sig;
    }
    return 0;
}
