#include <stdio.h>
#include <stdlib.h>   // srand
#include <time.h>     // time
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
    return 0;
}
