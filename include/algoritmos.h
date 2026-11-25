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
 *  5. Dijkstra ...................... camino más corto (pendiente)
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

/* ---------- 5. Dijkstra (pendiente) ---------- */

#endif
