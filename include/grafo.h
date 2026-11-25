#ifndef GRAFO_H
#define GRAFO_H

#include "lugar.h"

#define MAX_LUGARES 200
#define SIN_PORTAL 0

enum Densidad {
    MUY_ESCASA, ESCASA, NORMAL, DENSA, MUY_DENSA
};

struct Grafo {
    int n;                                   // lugares reales
    struct Lugar lugares[MAX_LUGARES];
    int costos[MAX_LUGARES][MAX_LUGARES];     // matriz de adyacencia
};

void grafo_inicializar(struct Grafo *g, int n);
int  grafo_cargar_nombres(struct Grafo *g, const char *ruta);
void grafo_generar_portales(struct Grafo *g, enum Densidad d);
void grafo_agregar_portal(struct Grafo *g, int origen, int destino, int costo);
int  grafo_hay_portal(const struct Grafo *g, int origen, int destino);
int  grafo_contar_portales(const struct Grafo *g);
void grafo_imprimir(const struct Grafo *g);

#endif
