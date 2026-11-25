#include "algoritmos.h"
#include "pila.h"

static void dfs_orden(const struct Grafo *g, int actual,
                      int visitado[], struct Pila *orden) {
    int vecino;
    visitado[actual] = 1;

    for (vecino = 0; vecino < g->n; vecino++)
        if (grafo_hay_portal(g, actual, vecino) && !visitado[vecino])
            dfs_orden(g, vecino, visitado, orden);

    pila_push(orden, actual);   // "actual" terminó
}

static void dfs_invertido(const struct Grafo *g, int actual,
                          int visitado[], int grupo[], int id) {
    int vecino;
    visitado[actual] = 1;
    grupo[actual] = id;

    for (vecino = 0; vecino < g->n; vecino++)
        if (grafo_hay_portal(g, vecino, actual) && !visitado[vecino])
            dfs_invertido(g, vecino, visitado, grupo, id);
}

int kosaraju(const struct Grafo *g, int grupo[]) {
    int visitado[MAX_LUGARES];
    struct Pila orden;
    int i, lugar, cantidad = 0;

    // Primera pasada: DFS normal, llenando la pila
    pila_inicializar(&orden);
    for (i = 0; i < g->n; i++) visitado[i] = 0;
    for (i = 0; i < g->n; i++)
        if (!visitado[i])
            dfs_orden(g, i, visitado, &orden);

    // Segunda pasada: DFS invertido en el orden de la pila
    for (i = 0; i < g->n; i++) visitado[i] = 0;
    while (pila_pop(&orden, &lugar))
        if (!visitado[lugar]) {
            dfs_invertido(g, lugar, visitado, grupo, cantidad);
            cantidad++;
        }

    return cantidad;
}

int es_fuertemente_conexo(const struct Grafo *g) {
    int visitado[MAX_LUGARES], grupo[MAX_LUGARES];
    struct Pila descarte;
    int i;

    if (g->n == 0) return 1;

    // ¿Desde 0 se llega a todos?
    pila_inicializar(&descarte);
    for (i = 0; i < g->n; i++) visitado[i] = 0;
    dfs_orden(g, 0, visitado, &descarte);
    for (i = 0; i < g->n; i++)
        if (!visitado[i]) return 0;

    // ¿Todos llegan a 0?
    for (i = 0; i < g->n; i++) visitado[i] = 0;
    dfs_invertido(g, 0, visitado, grupo, 0);
    for (i = 0; i < g->n; i++)
        if (!visitado[i]) return 0;

    return 1;
}
