#include "monticulo.h"

static void intercambiar(struct ElementoHeap *a, struct ElementoHeap *b) {
    struct ElementoHeap temp = *a;
    *a = *b;
    *b = temp;
}

// El elemento en "i" sube mientras sea menor que su padre
static void subir(struct MinHeap *h, int i) {
    int padre;
    while (i > 0) {
        padre = (i - 1) / 2;
        if (h->datos[i].distancia >= h->datos[padre].distancia) break;
        intercambiar(&h->datos[i], &h->datos[padre]);
        i = padre;
    }
}

// El elemento en "i" baja mientras algún hijo sea menor
static void bajar(struct MinHeap *h, int i) {
    int izq, der, menor;
    while (1) {
        izq = 2 * i + 1;
        der = 2 * i + 2;
        menor = i;

        if (izq < h->cantidad && h->datos[izq].distancia < h->datos[menor].distancia)
            menor = izq;
        if (der < h->cantidad && h->datos[der].distancia < h->datos[menor].distancia)
            menor = der;

        if (menor == i) break;      // ya está en su lugar
        intercambiar(&h->datos[i], &h->datos[menor]);
        i = menor;
    }
}

void minheap_inicializar(struct MinHeap *h) {
    h->cantidad = 0;
}

int minheap_vacio(const struct MinHeap *h) {
    return h->cantidad == 0;
}

int minheap_insertar(struct MinHeap *h, int lugar, int distancia) {
    if (h->cantidad == MAX_HEAP) return 0;
    h->datos[h->cantidad].lugar = lugar;
    h->datos[h->cantidad].distancia = distancia;
    subir(h, h->cantidad);
    h->cantidad++;
    return 1;
}

int minheap_extraer_min(struct MinHeap *h, int *lugar, int *distancia) {
    if (minheap_vacio(h)) return 0;
    *lugar = h->datos[0].lugar;
    *distancia = h->datos[0].distancia;

    h->cantidad--;
    h->datos[0] = h->datos[h->cantidad];   // el último pasa arriba
    bajar(h, 0);
    return 1;
}
