#include <stdio.h>
#include <stdlib.h>   // srand
#include <time.h>     // time
#include <string.h>   // strcmp
#include "grafo.h"
#include "algoritmos.h"

#ifdef _WIN32
#include <windows.h>
#endif

struct Grafo mundo;

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    int cargados;
    int grupo[MAX_LUGARES];
    int dist[MAX_LUGARES], anterior[MAX_LUGARES];
    int camino[MAX_LUGARES], cercanos[15];
    int origen = 0, destino = -1;
    int cuantos, largo, i;

    srand(time(NULL));
    grafo_inicializar(&mundo, 100);
    cargados = grafo_cargar_nombres(&mundo, "data/lugares.txt");

    if (cargados == -1) {
        printf("No se encontro data/lugares.txt\n");
        return 1;
    }
    printf("Se cargaron %d lugares\n", cargados);
    printf("Primero: %s\n", mundo.lugares[0].nombre);
    printf("Ultimo:  %s\n", mundo.lugares[cargados - 1].nombre);

    grafo_generar_portales(&mundo, MUY_ESCASA);
    printf("Portales: %d\n", grafo_contar_portales(&mundo));
    printf("Grupos antes: %d\n", kosaraju(&mundo, grupo));
    printf("Portales agregados: %d\n", reparar_conectividad(&mundo));
    printf("Grupos despues: %d\n", kosaraju(&mundo, grupo));
    printf("Bien conectado: %s\n",
           es_fuertemente_conexo(&mundo) ? "si" : "no");

    // Dijkstra desde San José (lugar 0)
    dijkstra(&mundo, origen, dist, anterior);

    printf("\nLos 15 lugares mas cercanos a %s:\n", mundo.lugares[origen].nombre);
    cuantos = lugares_mas_cercanos(&mundo, dist, origen, cercanos, 15);
    for (i = 0; i < cuantos; i++)
        printf("  %2d. %-20s costo %d\n", i + 1,
               mundo.lugares[cercanos[i]].nombre, dist[cercanos[i]]);

    // Buscar La Cangreja por nombre
    for (i = 0; i < mundo.n; i++)
        if (strcmp(mundo.lugares[i].nombre, "La Cangreja") == 0)
            destino = i;

    if (destino != -1) {
        largo = dijkstra_camino(anterior, origen, destino, camino);
        printf("\nCamino a %s (costo %d):\n  ",
               mundo.lugares[destino].nombre, dist[destino]);
        for (i = 0; i < largo; i++) {
            printf("%s", mundo.lugares[camino[i]].nombre);
            if (i < largo - 1) printf(" -> ");
        }
        printf("\n");
    }
    return 0;
}
