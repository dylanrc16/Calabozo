#include <stdio.h>
#include <string.h>
#include "grafo.h"

void grafo_inicializar(struct Grafo *g, int n) {
    int i, j;
    if (n > MAX_LUGARES) n = MAX_LUGARES;
    g->n = n;
    for (i = 0; i < MAX_LUGARES; i++)
        for (j = 0; j < MAX_LUGARES; j++)
            g->costos[i][j] = SIN_PORTAL;
}

int grafo_cargar_nombres(struct Grafo *g, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    char linea[256];
    int i = 0;

    if (archivo == NULL) return -1;

    while (i < g->n && fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';
        if (linea[0] == '\0') continue;
        lugar_inicializar(&g->lugares[i], linea);
        i++;
    }
    fclose(archivo);
    return i;
}
