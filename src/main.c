/* Arboles binarios
    Autor: 
                Jean Carlos Guillén 8-1019-771
*/
#include <stdio.h>
#include <stdlib.h>
#include "recetas.h"
#include "util.h"

// Códigos ANSI para color
#define CYAN     "\033[1;36m"
#define RESET    "\033[0m"
#define BOLD     "\033[1m"
#define CLEAR    "\033[H\033[J"

void mostrarMenu() {
    printf(CLEAR);
    printf(CYAN);
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║        %sSISTEMA DE GESTIÓN DE RECETAS%s         ║\n", BOLD, CYAN, RESET);
    printf(CYAN);
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║  1. Capturar receta y sus ingredientes       ║\n");
    printf("║  2. Mostrar todas las recetas                ║\n");
    printf("║  3. Buscar y modificar receta                ║\n");
    printf("║  4. Eliminar receta                          ║\n");
    printf("║  5. Guardar recetas                          ║\n");
    printf("║  6. Cargar recetas                           ║\n");
    printf("║  7. Salir                                    ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    printf(RESET);
    printf(BOLD "Seleccione una opción: " RESET);
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);
        limpiarBuffer();
        limpiarPantalla();

        switch (opcion) {
            case 1: capturarReceta(); break;
            case 2: mostrarRecetas(); break;
            case 3: buscarYModificar(); break;
            case 4: eliminarReceta(); break;
            case 5: guardarRecetas(); break;
            case 6: cargarRecetas(); break;
            case 7: liberarMemoria(); printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }

        if (opcion != 7) {
            printf("\nPresione ENTER para continuar...");
            getchar();
        }

    } while (opcion != 7);

    return 0;
}
