/*
 * algoritmos.h
 * Algoritmos que trabajan sobre el grafo del mundo.
 *
 *  1. DFS (búsqueda en profundidad) .. base de Kosaraju
 *  2. Kosaraju ...................... componentes fuertemente conexas
 *                                     (usa DFS + Pila)
 *  3. Verificación con dos DFS ...... ¿el mundo está bien conectado?
 *  4. Kruskal + Union-Find .......... repara la conectividad con el
 *                                     árbol de expansión mínima
 *  5. Dijkstra ...................... camino más corto, camino y
 *                                     15 más cercanos (usa MinHeap + Pila)
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo.h"

/* ---------- 2. Kosaraju ---------- */
// Llena grupo[i] con el grupo de cada lugar.
// Devuelve cuántos grupos hay.
int kosaraju(const struct Grafo *g, int grupo[]);

/* ---------- 3. Verificación con dos DFS ---------- */
// Devuelve 1 si desde cualquier lugar se llega a cualquier otro.
int es_fuertemente_conexo(const struct Grafo *g);

/* ---------- 4. Kruskal + Union-Find ---------- */
// Une los grupos con los portales más baratos (ida y vuelta).
// Devuelve cuántos portales agregó.
int reparar_conectividad(struct Grafo *g);

/* ---------- 5. Dijkstra (camino más corto) ---------- */
#define INFINITO 1000000

// Calcula la distancia más barata desde "origen" a todos.
// dist[i]     = costo mínimo para llegar a i (INFINITO si no se puede)
// anterior[i] = de qué lugar se llega a i en ese camino (-1 si ninguno)
void dijkstra(const struct Grafo *g, int origen,
              int dist[], int anterior[]);

// Arma el camino origen -> destino en orden, usando la pila.
// Devuelve cuántos lugares tiene el camino (0 si no hay camino).
int dijkstra_camino(const int anterior[], int origen, int destino,
                    int camino[]);

// Llena cercanos[] con los "max" lugares más cercanos al origen,
// ordenados del más cercano al más lejano (sin incluir el origen).
// Devuelve cuántos encontró.
int lugares_mas_cercanos(const struct Grafo *g, const int dist[],
                         int origen, int cercanos[], int max);

#endif
