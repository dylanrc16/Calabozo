#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // rand
#include "grafo.h"

#define COSTO_MIN 1
#define COSTO_MAX 10

static int probabilidad_por_mil(enum Densidad d) {
    switch (d) {
        case MUY_ESCASA: return 20;    // p = 0.02
        case ESCASA:     return 50;    // p = 0.05
        case NORMAL:     return 100;   // p = 0.10
        case DENSA:      return 250;   // p = 0.25
        case MUY_DENSA:  return 500;   // p = 0.50
    }
    return 100;
}

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

void grafo_agregar_portal(struct Grafo *g, int origen, int destino, int costo) {
    if (origen < 0 || origen >= g->n) return;
    if (destino < 0 || destino >= g->n) return;
    if (origen == destino) return;
    g->costos[origen][destino] = costo;
}

int grafo_hay_portal(const struct Grafo *g, int origen, int destino) {
    return g->costos[origen][destino] != SIN_PORTAL;
}

void grafo_generar_portales(struct Grafo *g, enum Densidad d) {
    int i, j, costo;
    int p = probabilidad_por_mil(d);

    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            if (i != j && rand() % 1000 < p) {
                costo = COSTO_MIN + rand() % (COSTO_MAX - COSTO_MIN + 1);
                grafo_agregar_portal(g, i, j, costo);
            }
}

int grafo_contar_portales(const struct Grafo *g) {
    int i, j, total = 0;
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            if (grafo_hay_portal(g, i, j)) total++;
    return total;
}
