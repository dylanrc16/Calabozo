#include <stdio.h>
#include "grafo.h"

#ifdef _WIN32
#include <windows.h>
#endif

struct Grafo mundo;

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    int cargados;

    grafo_inicializar(&mundo, 100);
    cargados = grafo_cargar_nombres(&mundo, "data/lugares.txt");

    if (cargados == -1) {
        printf("No se encontro data/lugares.txt\n");
        return 1;
    }
    printf("Se cargaron %d lugares\n", cargados);
    printf("Primero: %s\n", mundo.lugares[0].nombre);
    printf("Ultimo:  %s\n", mundo.lugares[cargados - 1].nombre);
    return 0;
}
