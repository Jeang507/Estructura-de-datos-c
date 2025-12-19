#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recetas.h"
#include "util.h"
#include <ctype.h>

#define TURQUESA  "\033[1;36m"
#define VERDE     "\033[1;32m"
#define ROJO      "\033[1;31m"
#define RESET     "\033[0m"
#define NEGRITA   "\033[1m"

NodoReceta* inicio = NULL;

void capturarReceta() {
    if (contarRecetas() >= MAX_RECETAS) {
        printf(ROJO "\nLímite máximo de recetas alcanzado.\n" RESET);
        return;
    }

    Receta nueva;
    limpiarPantalla();

    printf(TURQUESA "\n╔═══════════════════════════════════════╗\n");
    printf("║       CAPTURAR NUEVA RECETA           ║\n");
    printf("╚═══════════════════════════════════════╝\n" RESET);

    int nombreValido = 0;
    do {
        printf(TURQUESA "\n→ Ingrese el " NEGRITA "nombre de la receta" RESET TURQUESA " (o escriba 'cancelar'): " RESET);
        fgets(nueva.nombre, MAX_NOMBRE, stdin);
        nueva.nombre[strcspn(nueva.nombre, "\n")] = '\0';

        if (strcmp(nueva.nombre, "cancelar") == 0) {
            printf(ROJO "\nOperación cancelada por el usuario.\n" RESET);
            return;
        }

        int soloEspacios = 1, tieneLetra = 0;
        for (int i = 0; nueva.nombre[i]; i++) {
            if (!isspace(nueva.nombre[i])) soloEspacios = 0;
            if (isalpha(nueva.nombre[i])) tieneLetra = 1;
        }

        if (strlen(nueva.nombre) == 0 || soloEspacios || !tieneLetra) {
            printf(ROJO "\nNombre inválido. Intente nuevamente.\n" RESET);
        } else if (existeReceta(nueva.nombre)) {
            printf(ROJO "\nYa existe una receta con ese nombre.\n" RESET);
        } else {
            nombreValido = 1;
        }

    } while (!nombreValido);

    nueva.totalIngredientes = 0;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        Ingrediente ing;

        int nombreIngValido = 0;
        do {
            printf(TURQUESA "\n→ " NEGRITA "Nombre del ingrediente" RESET TURQUESA ": " RESET);
            fgets(ing.nombre, MAX_NOMBRE, stdin);
            ing.nombre[strcspn(ing.nombre, "\n")] = '\0';

            int soloEspacios = 1, tieneLetra = 0;
            for (int i = 0; ing.nombre[i]; i++) {
                if (!isspace(ing.nombre[i])) soloEspacios = 0;
                if (isalpha(ing.nombre[i])) tieneLetra = 1;
            }

            if (strlen(ing.nombre) == 0 || soloEspacios || !tieneLetra) {
                printf(ROJO "\nNombre inválido. Intente nuevamente.\n" RESET);
            } else {
                nombreIngValido = 1;
            }

        } while (!nombreIngValido);

        float cantidad;
        int cantidadValida = 0;
        do {
            printf(TURQUESA "→ " NEGRITA "Cantidad" RESET TURQUESA " (ej: 1.5): " RESET);
            if (scanf("%f", &cantidad) != 1 || cantidad <= 0) {
                printf(ROJO "\nCantidad inválida. Intente de nuevo.\n" RESET);
                limpiarBuffer();
            } else {
                cantidadValida = 1;
                ing.cantidad = cantidad;
                limpiarBuffer();
            }
        } while (!cantidadValida);

        int unidad;
        do {
            printf(TURQUESA "\n→ " NEGRITA "Seleccione la unidad" RESET TURQUESA ":\n" RESET);
            printf("   1. Gramos (g)\n");
            printf("   2. Kilogramos (kg)\n");
            printf("   3. Litros (lt)\n");
            printf("   4. Unidades (u)\n");
            printf(TURQUESA "   Opción: " RESET);

            if (scanf("%d", &unidad) != 1 || unidad < 1 || unidad > 4) {
                printf(ROJO "\nOpción inválida. Intente de nuevo.\n" RESET);
                limpiarBuffer();
            } else {
                limpiarBuffer();
                break;
            }
        } while (1);

        switch (unidad) {
            case 1: strcpy(ing.unidad, "g"); break;
            case 2: strcpy(ing.unidad, "kg"); break;
            case 3: strcpy(ing.unidad, "lt"); break;
            case 4: strcpy(ing.unidad, "u"); break;
        }

        nueva.ingredientes[nueva.totalIngredientes++] = ing;

        if (nueva.totalIngredientes >= MAX_INGREDIENTES) {
            printf(ROJO "\nSe alcanzó el límite de ingredientes.\n" RESET);
            break;
        }

        printf(TURQUESA "\n¿Agregar otro ingrediente? (s/n): " RESET);
        scanf(" %c", &continuar);
        limpiarBuffer();
    }

    // Ordenar los ingredientes alfabéticamente
    ordenarIngredientes(&nueva);

    // Crear nodo
    NodoReceta* nuevoNodo = malloc(sizeof(NodoReceta));
    if (!nuevoNodo) {
        printf(ROJO "\nError al reservar memoria para la receta.\n" RESET);
        return;
    }

    nuevoNodo->receta = nueva;
    nuevoNodo->sig = NULL;
    nuevoNodo->ant = NULL;

    // Insertar receta ordenada alfabéticamente en la lista
    if (!inicio || strcasecmp(nueva.nombre, inicio->receta.nombre) < 0) {
        nuevoNodo->sig = inicio;
        if (inicio) inicio->ant = nuevoNodo;
        inicio = nuevoNodo;
    } else {
        NodoReceta* temp = inicio;
        while (temp->sig && strcasecmp(nueva.nombre, temp->sig->receta.nombre) > 0)
            temp = temp->sig;

        nuevoNodo->sig = temp->sig;
        if (temp->sig) temp->sig->ant = nuevoNodo;
        temp->sig = nuevoNodo;
        nuevoNodo->ant = temp;
    }

    printf(VERDE "\nReceta guardada exitosamente.\n" RESET);
    getchar();
}


void mostrarRecetas() {
    limpiarPantalla();

    printf("\n\033[1;36m╔═══════════════════════════════════════╗\n");
    printf("║            LISTADO DE RECETAS         ║\n");
    printf("╚═══════════════════════════════════════╝\033[0m\n");

    if (!inicio) {
        printf("\n\033[1;31mNo hay recetas guardadas.\033[0m\n\n");
        return;
    }

    NodoReceta* actual = inicio;
    int i = 1;

    while (actual) {
        printf("\n\033[1;33m%d. %s\033[0m\n", i++, actual->receta.nombre);
        printf("   \033[1;36mIngredientes:\033[0m\n");

        for (int j = 0; j < actual->receta.totalIngredientes; j++) {
            Ingrediente ing = actual->receta.ingredientes[j];

            // Validaciones por si algún campo está corrupto
            if (strlen(ing.nombre) == 0 || ing.cantidad <= 0 || strlen(ing.unidad) == 0) {
                printf("   - \033[1;31m[Ingrediente inválido]\033[0m\n");
                continue;
            }

            printf("   - \033[1;37m%s\033[0m (\033[1;32m%.2f %s\033[0m)\n",
                   ing.nombre, ing.cantidad, ing.unidad);
        }

        actual = actual->sig;
    }
    limpiarBuffer();
}

void buscarYModificar() {
    limpiarPantalla();

    printf("\n\033[1;36m╔══════════════════════════════════════════════╗\n");
    printf("║           BUSCAR Y MODIFICAR RECETA          ║\n");
    printf("╚══════════════════════════════════════════════╝\033[0m\n");

    if (!inicio) {
        printf("\n\033[1;31mNo hay recetas para modificar.\033[0m\n");;
        return;
    }

    // Mostrar todas las recetas disponibles
    printf("\n\033[1;36mLista de recetas disponibles:\033[0m\n");
    NodoReceta* temp = inicio;
    int contador = 1;
    while (temp) {
        printf("  \033[1;33m%d.\033[0m \033[1;37m%s\033[0m\n", contador++, temp->receta.nombre);
        temp = temp->sig;
    }

    // Buscar por nombre
    char buscar[MAX_NOMBRE];
    printf("\nIngrese el nombre o parte del nombre de la receta a buscar: ");
    fgets(buscar, MAX_NOMBRE, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    if (strlen(buscar) == 0) {
        printf("\n\033[1;31mEntrada vacía. No se realizará ninguna acción.\033[0m\n");
        printf("\nPresione ENTER para seguir...");
        limpiarBuffer();
        getchar();
        return;
    }

    NodoReceta* actual = inicio;
    NodoReceta* encontrados[100];
    int total = 0;
    int pos = 1;

    printf("\n\033[1;36mCoincidencias encontradas:\033[0m\n");
    while (actual) {
        if (strcasestr(actual->receta.nombre, buscar)) {
            printf("  \033[1;33m%d.\033[0m \033[1;37m%s\033[0m\n", pos, actual->receta.nombre);
            encontrados[total++] = actual;
        }
        actual = actual->sig;
        pos++;
    }

    if (total == 0) {
        printf("\n\033[1;31mNo se encontraron coincidencias.\033[0m\n");
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        return;
    }

    int seleccion;
    do {
        printf("\nSeleccione el número de la receta a modificar (0 para cancelar): ");
        if (scanf("%d", &seleccion) != 1) {
            limpiarBuffer();
            printf("\033[1;31mEntrada inválida.\033[0m\n");
            continue;
        }
        limpiarBuffer();
    } while (seleccion < 0 || seleccion > total);

    if (seleccion == 0) return;

    NodoReceta* nodo = encontrados[seleccion - 1];

    // Confirmación
    printf("\n\033[1;33m¿Está seguro que desea modificar la receta \"%s\"? (s/n): \033[0m", nodo->receta.nombre);
    char confirmacion;
    scanf(" %c", &confirmacion);
    limpiarBuffer();

    if (confirmacion != 's' && confirmacion != 'S') {
        printf("\n\033[1;36mOperación cancelada.\033[0m\n");
        printf("\nPresione ENTER para continuar...");
        getchar();
        return;
    }

    // Modificación
    printf("\nNuevo nombre (ENTER para mantener el actual): ");
    char nuevoNombre[MAX_NOMBRE];
    fgets(nuevoNombre, MAX_NOMBRE, stdin);
    nuevoNombre[strcspn(nuevoNombre, "\n")] = '\0';

    if (strlen(nuevoNombre) > 0) {
        if (existeReceta(nuevoNombre)) {
            printf("\n\033[1;31mYa existe una receta con ese nombre.\033[0m\n");
        } else {
            strcpy(nodo->receta.nombre, nuevoNombre);
        }
    }

    // Mostrar ingredientes actuales
    printf("\n\033[1;36mIngredientes actuales:\033[0m\n");
    for (int i = 0; i < nodo->receta.totalIngredientes; i++) {
        Ingrediente ing = nodo->receta.ingredientes[i];
        printf("  \033[1;33m%d.\033[0m \033[1;37m%s\033[0m (\033[1;32m%.2f %s\033[0m)\n",
               i + 1, ing.nombre, ing.cantidad, ing.unidad);
    }

    printf("\nIngrese el número del ingrediente a modificar (0 para salir): ");
    int ingSel;
    if (scanf("%d", &ingSel) != 1) {
        limpiarBuffer();
        printf("\n\033[1;31mEntrada inválida.\033[0m\n");
        return;
    }
    limpiarBuffer();

    if (ingSel <= 0 || ingSel > nodo->receta.totalIngredientes) return;

    Ingrediente* ing = &nodo->receta.ingredientes[ingSel - 1];

    printf("\nNuevo nombre (ENTER para mantener): ");
    char nuevoIng[MAX_NOMBRE];
    fgets(nuevoIng, MAX_NOMBRE, stdin);
    nuevoIng[strcspn(nuevoIng, "\n")] = '\0';
    if (strlen(nuevoIng) > 0) strcpy(ing->nombre, nuevoIng);

    printf("Nueva cantidad (0 para mantener): ");
    float nuevaCant;
    if (scanf("%f", &nuevaCant) == 1 && nuevaCant > 0) {
        ing->cantidad = nuevaCant;
    }
    limpiarBuffer();

    printf("Nueva unidad (ENTER para mantener): ");
    char nuevaUnidad[10];
    fgets(nuevaUnidad, 10, stdin);
    nuevaUnidad[strcspn(nuevaUnidad, "\n")] = '\0';
    if (strlen(nuevaUnidad) > 0) strcpy(ing->unidad, nuevaUnidad);

    printf("\n\033[1;32mIngrediente modificado correctamente.\033[0m\n");

    guardarRecetas();  // Guardar automáticamente después de modificación

    printf("\nPresione ENTER para continuar...");
    getchar();
}

void eliminarReceta() {
    limpiarPantalla();

    printf("\n\033[1;31m╔════════════════════════════════════════╗\n");
    printf("║             ELIMINAR RECETA            ║\n");
    printf("╚════════════════════════════════════════╝\033[0m\n");

    if (!inicio) {
        printf("\n\033[1;31mNo hay recetas disponibles para eliminar.\033[0m\n");
        return;
    }

    // Mostrar todas las recetas antes de pedir búsqueda
    printf("\n\033[1;36mLista de recetas disponibles:\033[0m\n");

    NodoReceta* actual = inicio;
    int contador = 1;
    while (actual) {
        printf("  \033[1;33m%d.\033[0m \033[1;37m%s\033[0m\n", contador++, actual->receta.nombre);
        actual = actual->sig;
    }

    // Pedir búsqueda
    char buscar[MAX_NOMBRE];
    printf("\nIngrese el nombre o parte del nombre de la receta a buscar para eliminar: ");
    fgets(buscar, MAX_NOMBRE, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    if (strlen(buscar) == 0) {
        printf("\n\033[1;31mEntrada vacía. No se realizará ninguna acción.\033[0m\n");
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        return;
    }

    actual = inicio;
    NodoReceta* encontrados[100];
    int total = 0;
    int pos = 1;

    printf("\n\033[1;36mCoincidencias encontradas:\033[0m\n");

    while (actual) {
        if (strcasestr(actual->receta.nombre, buscar)) {
            printf("  \033[1;33m%d.\033[0m \033[1;37m%s\033[0m\n", total + 1, actual->receta.nombre);
            encontrados[total++] = actual;
        }
        actual = actual->sig;
        pos++;
    }

    if (total == 0) {
        printf("\n\033[1;31mNo se encontraron recetas que coincidan con \"%s\".\033[0m\n", buscar);
        printf("\nPresione ENTER para continuar...");
        limpiarBuffer();
        getchar();
        return;
    }

    int seleccion;
    do {
        printf("\nSeleccione el número de la receta a eliminar (0 para cancelar): ");
        if (scanf("%d", &seleccion) != 1) {
            limpiarBuffer();
            printf("\033[1;31mEntrada inválida. Intente de nuevo.\033[0m\n");
            continue;
        }
        limpiarBuffer();
        if (seleccion < 0 || seleccion > total)
            printf("\033[1;31mNúmero fuera de rango. Intente nuevamente.\033[0m\n");
    } while (seleccion < 0 || seleccion > total);

    if (seleccion == 0) {
        printf("\n\033[1;36mOperación cancelada por el usuario.\033[0m\n");
        printf("\nPresione ENTER para continuar...");
        getchar();
        return;
    }

    NodoReceta* nodo = encontrados[seleccion - 1];

    // Confirmación
    printf("\n\033[1;33m¿Está seguro que desea eliminar la receta \"%s\"? (s/n): \033[0m", nodo->receta.nombre);
    char confirmacion;
    scanf(" %c", &confirmacion);
    limpiarBuffer();

    if (confirmacion != 's' && confirmacion != 'S') {
        printf("\n\033[1;36mOperación cancelada por el usuario.\033[0m\n");
        printf("\nPresione ENTER para continuar...");
        getchar();
        return;
    }

    // Eliminación segura
    if (nodo->ant) nodo->ant->sig = nodo->sig;
    else inicio = nodo->sig;

    if (nodo->sig) nodo->sig->ant = nodo->ant;

    free(nodo);

    printf("\n\033[1;32mReceta eliminada correctamente.\033[0m\n");

    guardarRecetas(); // Guardar cambios automáticamente

    printf("\nPresione ENTER para continuar...");
    getchar();
}

void guardarRecetas() {
    FILE* f = fopen("recetas.txt", "w");
    if (!f) {
        printf("\n\033[1;31mError: No se pudo abrir el archivo para guardar las recetas.\033[0m\n");
        return;
    }

    NodoReceta* actual = inicio;
    int cantidadGuardadas = 0;

    while (actual) {
        if (fprintf(f, "Nombre receta: %s\n", actual->receta.nombre) < 0) break;

        for (int i = 0; i < actual->receta.totalIngredientes; i++) {
            Ingrediente ing = actual->receta.ingredientes[i];
            if (fprintf(f, "Ingrediente: %s,%.2f,%s\n", ing.nombre, ing.cantidad, ing.unidad) < 0) break;
        }

        if (fprintf(f, "----\n") < 0) break;

        actual = actual->sig;
        cantidadGuardadas++;
    }

    fclose(f);

    if (cantidadGuardadas == 0)
        printf("\n\033[1;33mNo se guardaron recetas porque la lista estaba vacía o hubo un error.\033[0m\n");
    else
        printf("\n\033[1;32m %d receta(s) guardadas correctamente en el archivo.\033[0m\n", cantidadGuardadas);
}

void cargarRecetas() {
    FILE* f = fopen("recetas.txt", "r");
    if (!f) {
        printf("\n\033[1;31mNo se encontró el archivo 'recetas.txt'.\033[0m\n");
        printf("Si es la primera vez que usas el programa, crea una receta primero.\n");
        return;
    }

    liberarMemoria(); 

    Receta r;
    char linea[256];
    int recetasCargadas = 0;

    while (fgets(linea, sizeof(linea), f)) {
        if (strncmp(linea, "Nombre receta:", 14) == 0) {
            r.totalIngredientes = 0;
            sscanf(linea, "Nombre receta: %[^\n]", r.nombre);

        } else if (strncmp(linea, "Ingrediente:", 11) == 0) {
            if (r.totalIngredientes >= MAX_INGREDIENTES) {
                printf("\n\033[1;33mSe alcanzó el máximo de ingredientes permitidos para una receta: %s\033[0m\n", r.nombre);
                continue;
            }

            Ingrediente ing;
            if (sscanf(linea, "Ingrediente: %[^,],%f,%s", ing.nombre, &ing.cantidad, ing.unidad) == 3) {
                r.ingredientes[r.totalIngredientes++] = ing;
            } else {
                printf("\n\033[1;31mError al leer un ingrediente. Línea omitida.\033[0m\n");
            }

        } else if (strncmp(linea, "----", 4) == 0) {
            // Validación: nombre no vacío y al menos 1 ingrediente
            if (strlen(r.nombre) == 0 || r.totalIngredientes == 0) {
                printf("\n\033[1;33mReceta inválida ignorada (sin nombre o sin ingredientes).\033[0m\n");
                continue;
            }

            // Ordenar ingredientes alfabéticamente
            ordenarIngredientes(&r);

            // Crear nodo
            NodoReceta* nuevo = malloc(sizeof(NodoReceta));
            if (!nuevo) {
                printf("\n\033[1;31mError de memoria al crear nodo.\033[0m\n");
                continue;
            }

            nuevo->receta = r;
            nuevo->sig = NULL;
            nuevo->ant = NULL;

            // Insertar receta ordenada en la lista
            if (!inicio || strcasecmp(r.nombre, inicio->receta.nombre) < 0) {
                nuevo->sig = inicio;
                if (inicio) inicio->ant = nuevo;
                inicio = nuevo;
            } else {
                NodoReceta* temp = inicio;
                while (temp->sig && strcasecmp(r.nombre, temp->sig->receta.nombre) > 0)
                    temp = temp->sig;

                nuevo->sig = temp->sig;
                if (temp->sig) temp->sig->ant = nuevo;
                temp->sig = nuevo;
                nuevo->ant = temp;
            }

            recetasCargadas++;
        }
    }

    fclose(f);

    if (recetasCargadas == 0)
        printf("\n\033[1;33mEl archivo está vacío o no se encontraron recetas válidas.\033[0m\n");
    else
        printf("\n\033[1;32mSe cargaron %d receta(s) exitosamente desde archivo.\033[0m\n", recetasCargadas);
}

void liberarMemoria() {
    NodoReceta* actual = inicio;
    while (actual) {
        NodoReceta* temp = actual;
        actual = actual->sig;
        free(temp);
    }
    inicio = NULL;
}

void ordenarIngredientes(Receta* r) {
    for (int i = 0; i < r->totalIngredientes - 1; i++) {
        for (int j = i + 1; j < r->totalIngredientes; j++) {
            if (strcasecmp(r->ingredientes[i].nombre, r->ingredientes[j].nombre) > 0) {
                Ingrediente temp = r->ingredientes[i];
                r->ingredientes[i] = r->ingredientes[j];
                r->ingredientes[j] = temp;
            }
        }
    }
}

