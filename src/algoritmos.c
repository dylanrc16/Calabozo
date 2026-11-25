#include <stdlib.h>   // rand
#include "algoritmos.h"
#include "pila.h"
#include "unionfind.h"

/* =====================================================
 * 1. DFS (BÚSQUEDA EN PROFUNDIDAD)
 *    dfs_orden: DFS normal, mete a la pila al terminar.
 *    dfs_invertido: DFS con los portales al revés.
 * ===================================================== */

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

/* =====================================================
 * 2. KOSARAJU
 *    Pasada 1: DFS normal desde todos -> pila de orden.
 *    Pasada 2: DFS invertido en orden de la pila ->
 *              cada DFS encuentra un grupo.
 * ===================================================== */

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

/* =====================================================
 * 3. VERIFICACIÓN CON DOS DFS
 *    DFS normal desde 0: ¿llega a todos?
 *    DFS invertido desde 0: ¿todos llegan a 0?
 * ===================================================== */

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

/* =====================================================
 * 4. KRUSKAL + UNION-FIND (reparar conectividad)
 *    1. Kosaraju para saber los grupos.
 *    2. Un candidato por cada par de grupos.
 *    3. Ordenar por costo (insertion sort).
 *    4. Kruskal: aceptar si Union-Find dice que no
 *       hay ciclo, hasta tener k - 1 conexiones.
 *    5. Cada conexión es un portal de ida y vuelta.
 *    Union-Find está implementado en unionfind.c.
 * ===================================================== */

#define MAX_CANDIDATOS (MAX_LUGARES * (MAX_LUGARES - 1) / 2)

struct Candidato {
    int grupo_a, grupo_b;    // qué grupos une
    int lugar_a, lugar_b;    // entre qué lugares va el portal
    int costo;
};

static int lugar_al_azar_del_grupo(const struct Grafo *g,
                                   const int grupo[], int id) {
    int i, cantidad = 0, elegido;

    for (i = 0; i < g->n; i++)
        if (grupo[i] == id) cantidad++;

    elegido = rand() % cantidad;
    for (i = 0; i < g->n; i++)
        if (grupo[i] == id) {
            if (elegido == 0) return i;
            elegido--;
        }
    return -1;
}

// Insertion sort: de menor a mayor costo
static void ordenar_por_costo(struct Candidato c[], int total) {
    int i, j;
    struct Candidato actual;

    for (i = 1; i < total; i++) {
        actual = c[i];
        j = i - 1;
        while (j >= 0 && c[j].costo > actual.costo) {
            c[j + 1] = c[j];
            j--;
        }
        c[j + 1] = actual;
    }
}

int reparar_conectividad(struct Grafo *g) {
    static struct Candidato candidatos[MAX_CANDIDATOS];
    int grupo[MAX_LUGARES];
    struct UnionFind uf;
    struct Candidato *c;
    int k, a, b, i;
    int total = 0, aceptados = 0, agregados = 0;

    // 1. ¿Cuántos grupos hay? (Kosaraju)
    k = kosaraju(g, grupo);
    if (k <= 1) return 0;

    // 2. Un candidato por cada par de grupos
    for (a = 0; a < k; a++)
        for (b = a + 1; b < k; b++) {
            c = &candidatos[total];
            c->grupo_a = a;
            c->grupo_b = b;
            c->lugar_a = lugar_al_azar_del_grupo(g, grupo, a);
            c->lugar_b = lugar_al_azar_del_grupo(g, grupo, b);
            c->costo = COSTO_MIN + rand() % (COSTO_MAX - COSTO_MIN + 1);
            total++;
        }

    // 3. Del más barato al más caro
    ordenar_por_costo(candidatos, total);

    // 4. Kruskal: aceptar si no forma ciclo (Union-Find)
    uf_inicializar(&uf, k);
    for (i = 0; i < total && aceptados < k - 1; i++) {
        c = &candidatos[i];
        if (uf_unir(&uf, c->grupo_a, c->grupo_b)) {
            aceptados++;
            // 5. Portal de ida y de vuelta
            if (!grafo_hay_portal(g, c->lugar_a, c->lugar_b)) {
                grafo_agregar_portal(g, c->lugar_a, c->lugar_b, c->costo);
                agregados++;
            }
            if (!grafo_hay_portal(g, c->lugar_b, c->lugar_a)) {
                grafo_agregar_portal(g, c->lugar_b, c->lugar_a, c->costo);
                agregados++;
            }
        }
    }

    return agregados;
}

/* =====================================================
 * 5. DIJKSTRA (pendiente)
 * ===================================================== */
