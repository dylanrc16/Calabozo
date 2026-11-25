/*
 * monticulo.h
 * Min-heap (montículo de mínimos): siempre deja arriba
 * el elemento con menor distancia.
 * Lo usa Dijkstra para elegir el lugar pendiente más cercano.
 */

#ifndef MONTICULO_H
#define MONTICULO_H

#define MAX_HEAP 40000

struct ElementoHeap {
    int lugar;
    int distancia;         // se ordena por esto
};

struct MinHeap {
    struct ElementoHeap datos[MAX_HEAP];
    int cantidad;
};

void minheap_inicializar(struct MinHeap *h);
int  minheap_vacio(const struct MinHeap *h);
int  minheap_insertar(struct MinHeap *h, int lugar, int distancia);
int  minheap_extraer_min(struct MinHeap *h, int *lugar, int *distancia);

#endif
