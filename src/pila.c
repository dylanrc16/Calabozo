#include "pila.h"

void pila_inicializar(struct Pila *p) {
    p->tope = 0;
}

int pila_vacia(const struct Pila *p) {
    return p->tope == 0;
}

int pila_llena(const struct Pila *p) {
    return p->tope == MAX_PILA;
}

int pila_push(struct Pila *p, int valor) {
    if (pila_llena(p)) return 0;
    p->datos[p->tope] = valor;
    p->tope++;
    return 1;
}

int pila_pop(struct Pila *p, int *valor) {
    if (pila_vacia(p)) return 0;
    p->tope--;
    *valor = p->datos[p->tope];
    return 1;
}
