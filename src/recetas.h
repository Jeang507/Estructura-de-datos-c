#ifndef RECETAS_H
#define RECETAS_H

#define MAX_NOMBRE 50
#define MAX_INGREDIENTES 50
#define MAX_RECETAS 100


typedef struct {
    char nombre[MAX_NOMBRE];
    float cantidad;
    char unidad[10];
} Ingrediente;

typedef struct {
    char nombre[MAX_NOMBRE];
    Ingrediente ingredientes[MAX_INGREDIENTES];
    int totalIngredientes;
} Receta;

typedef struct NodoReceta {
    Receta receta;
    struct NodoReceta* sig;
    struct NodoReceta* ant;
} NodoReceta;

extern NodoReceta* inicio;

void capturarReceta();
void mostrarRecetas();
void buscarYModificar();
void eliminarReceta();
void guardarRecetas();
void cargarRecetas();
void liberarMemoria();
void ordenarIngredientes(Receta* r);

#endif
